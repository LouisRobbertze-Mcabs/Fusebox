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
    ADCtoGPIO();  //Use ADCs as an ad hoc GPIO
    SetFlags();   //sets error and status flags for use in PDO/SDO MISOs
    HeadlightBulbCheck(); //experimental check to determine whether the head/high light has blown

    //OPERATING TIME *********************************************
    //defined as the amount of time spent in the NMT Operational State (0x01). Will increment counter after an operational hour has elapsed
    if(Operational_State != 4)    //ensures system is not in the halt state
    {
        HourTimer++;
        if(HourTimer >= 180000)         //60*60*50=180000    Based on a timer of 50Hz
        {
            OperationalCounter++;  //VALUE NEEDS TO BE MOVED TO EEPROM before CPU shuts down and value is lost
            HourTimer = 0;
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
    EALLOW;

    CpuTimer2.InterruptCount++;
    EDIS;
}



__interrupt void can_rx_isr(void)
{
    //Mailbox 7 - Master: VCU
    //Mailbox 9 - Slave: Control Box
    //RMP4 = NMT_MOSI
    //RMP5 = PDO_MOSI
    //RMP6 = SDO_MOSI
    Uint16 SDO_MISO_Data[9] = {0};
    Uint32 SDO_MISO_Ctrl = 0;
    Uint16 SDO_MOSI_Request = 0;
    Uint16 SDO_MOSI_Ctrl = 0;
    Uint16 SDO_ArrayIndex = 0;
    Uint16 PDO_Instruction = 0;
    Uint32 PDO_Data_Low = 0;
    Uint32 PDO_Data_High = 0;
    Uint16 NMT_Instruction = 0;
    Uint16 NMT_Location = 0;
    Uint16 ErrorCounter = 0;

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
        CANSlaveConfig();
    }*/
    if (ECanaRegs.CANRMP.bit.RMP4 == 1) //State set from NMT (MOSI)
    {
        NMT_Instruction = ECanaMboxes.MBOX4.MDL.all & 0xFF;
        NMT_Location = ECanaMboxes.MBOX4.MDL.all & 0xFF00;

        if(NMT_Location == 0x1D00 || NMT_Location == 0)
        {
            switch(NMT_Instruction)
            {
            case 1:
                Operational_State = 0x5;           //Operational State
                break;
            case 2:
                Operational_State = 0x4;           //Halt state
                break;
            case 0x80 :
                Operational_State = 0x7F;          //Pre-Op state
                break;
            case 0x81 :                    //Device Reset
                Operational_State = 0x0;
                while(Operational_State<0x100){;}  //Reset governed by Watchdog timer
                break;
            case 0x82 :                    //CAN Bus reset
                Operational_State = 0x0;
                //add reset function
                break;
            }
            CANTransmit(0x73C, 0, Operational_State, 8, 7); //heart beat response    Double check mailbox
        }
        else if (ECanaRegs.CANRMP.bit.RMP5 == 1)    //PDO_MOSI
        {
            PDO_Instruction = ECanaMboxes.MBOX5.MDL.all & 0xFF;

            if(Operational_State == 5)
            {
                if(PDO_Instruction == 0xFF01 && !LowPowerMode)   //Enter Low power mode
                {
                    LowPowerMode = 1;
                }
                else if(PDO_Instruction == 0xFF00 && LowPowerMode)   //Disable Low power mode
                {
                    LowPowerMode = 0;
                }
                else ; //Code space for Invalid instruction ----> must still decide what to do

                PDO_Data_Low += SdoMessage.RelayErrors; //PDO response includes Fuse and Relay/Mosfet error flags as well as Vehcile and Relay/Mosfet status flags
                PDO_Data_Low = (PDO_Data_Low<<16) + SdoMessage.FuseErrors;
                PDO_Data_High += SdoMessage.VehicleStatus;
                PDO_Data_High = (PDO_Data_High<<16) + SdoMessage.RelayStatus;
                CANTransmit(0x1BC, PDO_Data_High, PDO_Data_Low, 8, 7); //PDO_MISO
            }
        }

        if(SDO_MOSI_Ctrl == 0x42)
        {
            SDO_MOSI_Ctrl = ECanaMboxes.MBOX6.MDL.all & 0xFF;
            SDO_MOSI_Request = (ECanaMboxes.MBOX6.MDL.all>>8) & 0xFFFF;

            SDO_MISO_Ctrl = ((Uint32)SDO_MOSI_Request)<<8 | 0x40;

            ErrorCounter += SdoMessage.RelayErrorCounter;
            ErrorCounter = (ErrorCounter << 8) + SdoMessage.FuseErrorCounter;

            SDO_MISO_Data[0] = SdoMessage.Current;             //SDO 0x0900
            SDO_MISO_Data[1] = SdoMessage.Temperature;         //SDO 0x0902
            SDO_MISO_Data[2] = SdoMessage.FuseErrors;          //SDO 0x0904
            SDO_MISO_Data[3] = SdoMessage.RelayStatus;         //SDO 0x0906
            SDO_MISO_Data[4] = SdoMessage.RelayErrors;         //SDO 0x0908
            SDO_MISO_Data[5] = SdoMessage.VehicleStatus;       //SDO 0x090A
            SDO_MISO_Data[6] = ErrorCounter;                   //SDO 0x090C
            SDO_MISO_Data[7] = IgnitionCounter;                //SDO 0x0912
            SDO_MISO_Data[8] = OperationalCounter;             //SDO 0x0914

            SDO_ArrayIndex = (SDO_MOSI_Request - 0x900)/2;
            if(SDO_ArrayIndex >= 0 && SDO_ArrayIndex <= 9) CANTransmit(0x59C, SDO_MISO_Data[SDO_ArrayIndex], SDO_MISO_Ctrl, 8, 9);
            else CANTransmit(0xE, 0x06020000, SDO_MISO_Ctrl, 8, 9); //Invalid object reference-object does not exist
        }

        ECanaRegs.CANRMP.all = 0xFFFFFFFF;              // Reset receive mailbox flags
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;         // Acknowledge this interrupt to receive more interrupts from group 9
    }
}
__interrupt void can_tx_isr(void)
{
    /*if (ECanaRegs.CANTA.all == 0x00000001)
    {
        ECanaRegs.CANTA.all = 0xFFFFFFFF;           // Reset tranmission flags
    }*/


    ECanaRegs.CANTA.all = 0xFFFFFFFF;

    // Reset tranmission flags
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;         // Acknowledge this interrupt to receive more interrupts from group 9
}

