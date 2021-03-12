/*
 * User_Interrupts.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */
//**********************************Fusebox
#include "User_Interrupts.h"

__interrupt void adc_isr(void)
{
    //gee aandag hieraan. doen 'n stroom meting conversion teen 1 Hz soos spanning
    //Sit dit dalk deur 'n laag deurlaat filter y(k) = y(k - 1) + a[x(k) - y(k - 1)] met a = 1 - e^-WcTs

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.bit.ACK10 = 1;           // Acknowledge interrupt to PIE
}

__interrupt void cpu_timer0_isr(void)
{
    counter_2Hz++;
    CpuTimer0.InterruptCount++;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1/* PIEACK_GROUP1*/;
}

__interrupt void cpu_timer1_isr(void)                           //50Hz loop
{
    if(Operational_State == 5)    //ensures system is not in the halt state
    {

        ADCtoGPIO();  //Use ADCs as a defacto GPIO
        SetFlags();   //sets error and status flags for use in PDO/SDO MISOs
        HeadlightControl();
        HeadlightBulbCheck(); //experimental check to determine whether the head/high light has blown

        //OPERATING TIME *********************************************
        //defined as the amount of time spent in the NMT Operational State (0x01) and Low Power Mode (0x03). Will increment counter after an operational hour has elapsed
        HourTimer++;
        if(HourTimer >= 180000)         //60*60*50=180000    Based on a timer of 50Hz for a period of 1 hour
        {
            OperationalCounter++;  //VALUE NEEDS TO BE MOVED TO EEPROM before CPU shuts down and value is lost     !!!!!!!!!!!!!!!!!!!!
            HourTimer = 0;
            /*currently, this feature will suffer a time 'loss' when the vehicle is powered down: if the counter reaches a value of, say, 52 minutes
             *and the vehicle is switched off, the counter will be reset to zero (it is initialised to zero in globals.c) and the 52 minutes
             *will be lost.
             */
        }
    }

    //IGNITION CYCLE COUNTER *************************************
    //counter increments every time the vehicle is started
    if(Key_In_Sense && !ResetIgnitionFlag) //if key is on and the counter has not yet been incremented
    {
        IgnitionCounter++;
        ResetIgnitionFlag = 1; //prevents counter from counting more than once per ignition
    }
    else if(!Key_In_Sense) ResetIgnitionFlag = 0; //resets flag when vehicle is switched off



    CpuTimer1.InterruptCount++;
    EDIS;
}

__interrupt void cpu_timer2_isr(void)
{
    // This CPU timer interrupt is typically reserved for DSP/BIOS use
    // It is currently being used to time the Heartbeat_2 message for the CANopen network


    EALLOW;
    Uint32 Heartbeat_2_Low = 0;
    Uint32 Heartbeat_2_High = 0;

    Heartbeat_2_Low += SdoMessage.RelayErrors; //Heartbeat_2 response includes Fuse and Relay/Mosfet error flags as well as Vehicle and Relay/Mosfet status flags
    Heartbeat_2_Low = (Heartbeat_2_Low<<16) + SdoMessage.FuseErrors;
    Heartbeat_2_High += SdoMessage.VehicleStatus;
    Heartbeat_2_High = (Heartbeat_2_High<<16) + SdoMessage.RelayStatus;
    CANTransmit(0x63D, Heartbeat_2_High, Heartbeat_2_Low, 8, 4); //Heartbeat_2 Message

    CpuTimer2.InterruptCount++;
    EDIS;
}


__interrupt void can_rx_isr(void)
{
    //Mailbox 7 - Master: VCU
    //Mailbox 9 - Slave: Control Box
    //Mailbox ? - Acewell Speedometer
    //RMP4 = NMT_MOSI
    //RMP6 = SDO_MOSI
    // RMP7????? = Acewell Speedometer
    Uint32 SDO_MISO_Data[9] = {0};
    union bits32 SDO_Message;

    Uint16 SDO_MOSI_Ctrl = 0;
    Uint16 SDO_ArrayIndex = 0;
    Uint16 NMT_Instruction = 0;
    Uint16 NMT_Location = 0;
    Uint16 SDO_MOSI_Request = 0;
    Uint16 SDO_MOSI_Data = 0;


    /*if (ECanaRegs.CANRMP.bit.RMP1 == 1)
    {
        //CANSlaveReception();                //handle the receive message
        ECanaRegs.CANRMP.bit.RMP1 = 1;
    }
    else if (ECanaRegs.CANRMP.bit.RMP2 == 1)
    {
        //CANChargerReception();
    }
    else if(ECanaRegs.CANRMP.bit.RMP3 == 1)
    {
        //CANSlaveConfig();
    }*/
    if (ECanaRegs.CANRMP.bit.RMP0 == 1) //State set from NMT (MOSI)
    {
        NMT_Instruction = ECanaMboxes.MBOX0.MDL.all & 0xFF;
        NMT_Location = ECanaMboxes.MBOX0.MDL.all & 0xFF00;

        if(NMT_Location == 0x3C00 || NMT_Location == 0)                 //make sure this is in line
        {
            switch(NMT_Instruction)
            {
            case 1:
                Operational_State = 5;           //Operational State
                LowPowerMode = 0;
                break;
            case 2:
                Operational_State = 4;           //Halt state
                LowPowerMode = 0;
                break;
            case 3:
                Operational_State = 6;            //Operational State in low power mode
                LowPowerMode = 1;
                break;
            case 0x80 :
                Operational_State = 0x7F;          //Pre-Op state
                LowPowerMode = 0;
                break;
            case 0x81 :                             //Device Reset
                Operational_State = 0x0;
                while(Operational_State != 100){;}  //Reset governed by Watchdog timer
                break;
            case 0x82 :                             //CAN Bus reset
                Operational_State = 0x0;
                CAN_Initialised = 0;
                CAN_Init();
                if(!CAN_Initialised) // if CAN_Initialised is still zero then CAN_Init failed and entire device must reset
                {
                    while(Operational_State != 100){;}  //Reset governed by Watchdog timer
                }
                break;
            }
            CANTransmit(0x5BD, 0, Operational_State, 8, 3); //heartbeat_1 response    Double check mailbox
        }
    }

    else if(ECanaRegs.CANRMP.bit.RMP1 == 1)
    {
        SDO_MOSI_Ctrl = ECanaMboxes.MBOX1.MDL.all & 0xFF;
        SDO_MOSI_Request = (ECanaMboxes.MBOX1.MDL.all>>8) & 0xFFFF;
        SDO_MOSI_Data = ECanaMboxes.MBOX1.MDH.all & 0xFF;

        //SDO_MISO_Ctrl = ((Uint32)SDO_MOSI_Request)<<8 | 0x40;

        //sets up the error counter word for CAN transmission
        if(Operational_State != 4 && SDO_MOSI_Ctrl == 0x42)
        {

            //This array acts a holder for all the potential SDO requests.
            //Note only the requested array element is transmitted - not the entire array
            SDO_MISO_Data[0] = SdoMessage.Current;             //SDO 0x0900
            SDO_MISO_Data[1] = SdoMessage.Temperature;         //SDO 0x0902
            SDO_MISO_Data[2] = SdoMessage.FuseErrors;          //SDO 0x0904
            SDO_MISO_Data[3] = SdoMessage.RelayStatus;         //SDO 0x0906
            SDO_MISO_Data[4] = SdoMessage.RelayErrors;         //SDO 0x0908
            SDO_MISO_Data[5] = SdoMessage.VehicleStatus;       //SDO 0x090A
            SDO_MISO_Data[6] = ErrorCounter;                   //SDO 0x090C
            SDO_MISO_Data[7] = IgnitionCounter;                //SDO 0x0912
            SDO_MISO_Data[8] = OperationalCounter;             //SDO 0x0914

            if(SDO_MOSI_Request == 0x0912) SDO_MOSI_Request = 0x090E;
            if(SDO_MOSI_Request == 0x0914) SDO_MOSI_Request = 0x0910;
            //Refering to annex A of the control box doc, the SDO Location index went up in 2s but these two indices
            //break that pattern which will cause issues with the array indexing below. These two ifs simply adjust the SDO indices
            //to follow the 2s pattern

            SDO_ArrayIndex = (SDO_MOSI_Request - 0x900)/2; //converts the SDO request into a value which is used to make a selection from the array above
            SDO_Message.yourSplitInterger.var1 = 0x40;
            SDO_Message.yourSplitInterger.var2 = SDO_ArrayIndex&0xFF;
            SDO_Message.yourSplitInterger.var2 = (SDO_ArrayIndex>>8)&0xFF;
            if(SDO_ArrayIndex <= 9) CANTransmit(0x1BD, SDO_MISO_Data[SDO_ArrayIndex], SDO_Message.asUint, 8, 5); //Transmits the requested information via CAN
            else CANTransmit(0x1BD, 0x06020000, SDO_Message.asUint, 8, 5); //Invalid object reference-object does not exist
        }
        else if(Operational_State != 4 && SDO_MOSI_Ctrl == 0x22)                //Write data
        {
            if(SDO_MOSI_Request == 0x0906)
            {
                Mfet_Ctrl_0 = (SDO_MOSI_Data>>5)&0x1;//set mosfet0 = 1;
                Mfet_Ctrl_1 = (SDO_MOSI_Data>>6)&0x1;//set mosfet1 = 1;
                Mfet_Ctrl_2 = (SDO_MOSI_Data>>7)&0x1;//set mosfet2 = 1;

                SDO_Message.yourSplitInterger.var1 = 0x60;
                SDO_Message.yourSplitInterger.var2 = 0x0906&0xFF;
                SDO_Message.yourSplitInterger.var2 = (0x0906>>8)&0xFF;

                //CAN transmit write acknowledge ID = 0x60
                CANTransmit(0x23C, 0x0, SDO_Message.asUint, 8, 5); //Invalid object reference-object does not exist
            }
        }
    }
    else if(ECanaRegs.CANRMP.bit.RMP2 == 1) //Acewell Speedometer
    {
        //can be removed for future work...
        if(ECanaMboxes.MBOX2.MDH.all == 0x88) //Acewell LED indicator
        {
            if(ECanaMboxes.MBOX2.MDL.all & 0x20 == 0x20) Acewell_Drive_Ready = 1;  //Drive_ready bit of LED indicator
            else if(ECanaMboxes.MBOX2.MDL.all & 0x20 == 0) Acewell_Drive_Ready = 0;
        }
        SwitchReverseSensor();
    }

    ECanaRegs.CANRMP.all = 0xFFFFFFFF;              // Reset receive mailbox flags
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;         // Acknowledge this interrupt to receive more interrupts from group 9
}

__interrupt void can_tx_isr(void)
{
    if(ECanaRegs.CANTA.bit.TA3 == 1)                //Transmit Acknowledge: Heartbeat_1_MISO
    {
        ECanaRegs.CANTA.bit.TA3 = 1;
    }
    else if(ECanaRegs.CANTA.bit.TA4 == 1)            //Transmit Acknowledge: Heartbeat_2_MISO
    {
        ECanaRegs.CANTA.bit.TA4 = 1;
    }
    else if(ECanaRegs.CANTA.bit.TA5 == 1)            //Transmit Acknowledge: SDO_MISO
    {
        ECanaRegs.CANTA.bit.TA5 = 1;
    }

    PieCtrlRegs.PIEACK.bit.ACK9 = 1;                // Acknowledge this interrupt to receive more interrupts from group 9
}
