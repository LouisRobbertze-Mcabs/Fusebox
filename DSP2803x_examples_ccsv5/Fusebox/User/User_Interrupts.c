/*
 * User_Interrupts.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */
//**********************************Fusebox
#include "User_Interrupts.h"
#define PI 3.14159265358979323846
static long Temp_Values[16];
volatile long Fuse_1_Signal;
volatile long Fuse_4_Signal;
volatile long Vts;
volatile long Rts;
volatile long Forward_Signal;
volatile long Brake_Signal;
volatile long Key_Sense_Signal;
volatile long Horn_Signal;
volatile long E_stop_Signal;
volatile long Position_Signal;
volatile long Relay_3_Signal;
volatile long Relay_4_Signal;
volatile long V_Reg_Signal;
volatile long Fuse_7_Signal;
volatile long Fuse_2_Signal;
volatile long Fuse_8_Signal;

extern volatile Uint16 Fuse_Out_Sense_1;
extern volatile Uint16 Fuse_Out_Sense_4;
extern volatile Uint16 Forward_In_Sense;
extern volatile Uint16 Brake_In_Sense;
extern volatile Uint16 Key_In_Sense;
extern volatile Uint16 Horn_Ctrl_Sense;                            //relay input
extern volatile Uint16 E_Stop_In_Sense;                            //define logic
extern volatile Uint16 Position_Out_Sense;
extern volatile Uint16 Heated_Seats_Out_Sense;                     //Relay 3 needs swopping
extern volatile Uint16 Radio_Out_Sense;                            //Relay 4 needs swopping
extern volatile Uint16 V_Reg_In_Sense;                             //secondary regulator
extern volatile Uint16 Fuse_Out_Sense_7;
extern volatile Uint16 Fuse_Out_Sense_2;
extern volatile Uint16 Fuse_Out_Sense_8;

extern volatile Uint16 FuseError;     //SDO Location: 0x0904 ---->FUSE ERROR STATUS FLAGS
extern volatile Uint16 FuseErrorCount;    //SDO Location: 0x090C ---->Error Counter
extern volatile Uint16 RelayMOSFETStatus;  //SDO Location: 0x0906     Bit 0 - 4 = Relays          Bit 5 - 13 MOSFETs
extern volatile Uint16 RelayMOSFETError;            //SDO Location: 0x0908
extern volatile Uint16 RelayMOSFETErrorCounter;     //SDO Location: 0x090C
extern volatile Uint16 VehicleStatus;    //SDO Location: 0x090A
extern volatile Uint16 ErrorCounter;
extern volatile Uint16 OperationalCounter;
extern volatile Uint32 HourTimer;
extern volatile Uint16 ResetIgnitionFlag;
extern volatile Uint32 IgnitionCounter;


extern volatile float Current_Prev;
extern volatile Uint16 HeadLightBlown;
extern volatile Uint16 HighBeamBlown;
extern volatile Uint16 counter1; //timeout counter for head light to switch on after command is received
extern volatile Uint16 counter2; //timeout counter for high beam to switch on after command is received
extern volatile Uint16 HeadSwitched;
extern volatile Uint16 HighSwitched;
extern volatile Uint16 CheckAgain1;
extern volatile Uint16 CheckAgain2;

extern volatile Uint16 Operational_State;       //as demanded by NMT
extern volatile Uint16 LowPowerMode;

MasterVariableTable SdoMessage;
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
    //maybe run in a function that is triggered by this counter?
    //also, make more efficent by using Uint16 instead of floats
    //ADC result multiplied by 1e12 to avoid gorra round off errors when using int instead of float
    //ServiceDog();

    /*float Fc = 10;     //clock frequency [Hz]
    float Ts = 1/50;   //sample period [s]*/

    //Fuse box Current
    //channel A0 - SOC0
    Fusebox_Current = Temp_Values[0] + (0.72*((0.02*(AdcResult.ADCRESULT0))-Temp_Values[0]));                  //Test gain (3.3/4096 *1/39.6mV)
    Temp_Values[0] = Fusebox_Current;

    //Fuse_Out_1
    //channel B2 - SOC1
    Fuse_1_Signal = (Temp_Values[1] + (0.72*(((1E6*AdcResult.ADCRESULT1))-Temp_Values[1])));                          //add in proper gain
    Temp_Values[1] = Fuse_1_Signal;
    if(Fuse_1_Signal>1E6*2048)
        Fuse_Out_Sense_1 = 0;   //active when voltage is low
    else
        Fuse_Out_Sense_1 = 1;

    //Fuse_Out_4
    //channel B4  - SOC2
    Fuse_4_Signal = (Temp_Values[2] + (0.72*(((1E6*AdcResult.ADCRESULT2))-Temp_Values[2])));                          //add in proper gain
    Temp_Values[2] = Fuse_4_Signal;
    if(Fuse_4_Signal>1E6*2048)
        Fuse_Out_Sense_4 = 0;                           //active when voltage is low
    else
        Fuse_Out_Sense_4 = 1;

    //Fuse box Temperature
    //channel A1 - SOC3
    Vts = Temp_Values[3] + (0.72*((0.00080566*(AdcResult.ADCRESULT3))-Temp_Values[3]));                     //add in proper gain
    Temp_Values[3] = Vts;
    Rts = (33000/Vts) - 10000;
    Fusebox_Temperature = (1/((log(Rts/10000))/4000+0.003356))-273;

    //Forward input
    //channel A2 - SOC4
    Forward_Signal = (Temp_Values[4] + (0.72*(((1E6*AdcResult.ADCRESULT4))-Temp_Values[4])));                           //add in proper gain
    Temp_Values[4] = Forward_Signal;
    if(Forward_Signal>1E6*2048)
        Forward_In_Sense = 1;                           //active high
    else
        Forward_In_Sense = 0;
    //Brake light output
    //channel A3 - SOC5
    Brake_Signal = (Temp_Values[5] + (0.72*(((1E6*AdcResult.ADCRESULT5))-Temp_Values[5])));                           //add in proper gain
    Temp_Values[5] = Brake_Signal;
    if(Brake_Signal>1E6*2048)
        Brake_In_Sense = 1;                           //active high
    else
        Brake_In_Sense = 0;

    //Key switch input
    //channel A4 - SOC6
    Key_Sense_Signal = (Temp_Values[6] + (0.72*(((1E6*AdcResult.ADCRESULT6))-Temp_Values[6])));                           //add in proper gain
    Temp_Values[6] = Key_Sense_Signal;
    if(Key_Sense_Signal>1E6*2048)
        Key_In_Sense = 1;                           //active high
    else
        Key_In_Sense = 0;

    //Horn output
    //channel A5 - SOC7
    Horn_Signal = (Temp_Values[7] + (0.72*(((1E6*AdcResult.ADCRESULT7))-Temp_Values[7])));                           //add in proper gain
    Temp_Values[7] = Horn_Signal;
    if(Horn_Signal>1E6*2048)
        Horn_Ctrl_Sense = 0;                           //active high ------>>> LOW
    else
        Horn_Ctrl_Sense = 1;

    //E-stop
    //channel A6 - SOC8
    E_stop_Signal = (Temp_Values[8] + (0.72*(((1E6*AdcResult.ADCRESULT8))-Temp_Values[8])));                           //add in proper gain
    Temp_Values[8] = E_stop_Signal;
    if(E_stop_Signal>1E6*2048)
        E_Stop_In_Sense = 1;                           //active high
    else
        E_Stop_In_Sense = 0;

    //Position Switch
    //channel A7 - SOC9
    Position_Signal = (Temp_Values[9] + (0.72*(((1E6*AdcResult.ADCRESULT9))-Temp_Values[9])));                           //add in proper gain
    Temp_Values[9] = Position_Signal;
    if(Position_Signal>1E6*2048)
        Position_Out_Sense = 1;                           //active high
    else
        Position_Out_Sense = 0;

    //Relay 3                           -- needs to swop with relay 3 output (Heated seats)
    //channel B0 - SOC10
    Relay_3_Signal = (Temp_Values[10] + (0.72*(((1E6*AdcResult.ADCRESULT10))-Temp_Values[10])));                           //add in proper gain
    Temp_Values[10] = Relay_3_Signal;
    if(Relay_3_Signal>1E6*2048)
        Heated_Seats_Out_Sense = 1;                           //active high
    else
        Heated_Seats_Out_Sense = 0;

    //Relay 4                            -- needs to swop to relay 4 output (Radio out)
    //channel B1 - SOC11
    Relay_4_Signal = (Temp_Values[11] + (0.72*(((1E6*AdcResult.ADCRESULT11))-Temp_Values[11])));                           //add in proper gain
    Temp_Values[11] = Relay_4_Signal;
    if(Relay_4_Signal>1E6*2048)
        Radio_Out_Sense = 1;                           //active high
    else
        Radio_Out_Sense = 0;

    //12V Regulator - secondary
    //channel B3- SOC12
    V_Reg_Signal = (Temp_Values[12] + (0.72*(((1E6*AdcResult.ADCRESULT12))-Temp_Values[12])));                           //add in proper gain
    Temp_Values[12] = V_Reg_Signal;
    if(V_Reg_Signal>1E6*2048)
        V_Reg_In_Sense = 1;                           //active high
    else
        V_Reg_In_Sense = 0;

    //Fuse_Out_7
    //channel B5 - SOC13
    Fuse_7_Signal = (Temp_Values[13] + (0.72*(((1E6*AdcResult.ADCRESULT13))-Temp_Values[13])));                           //add in proper gain
    Temp_Values[13] = Fuse_7_Signal;
    if(Fuse_7_Signal>1E6*2048)
        Fuse_Out_Sense_7 = 0;                           //active low
    else
        Fuse_Out_Sense_7 = 1;

    //Fuse_Out_2
    //channel B6 - SOC14
    Fuse_2_Signal = (Temp_Values[14] + (0.72*(((1E6*AdcResult.ADCRESULT14))-Temp_Values[14])));                           //add in proper gain
    Temp_Values[14] = Fuse_2_Signal;
    if(Fuse_2_Signal>1E6*2048)
        Fuse_Out_Sense_2 = 0;                           //active low
    else
        Fuse_Out_Sense_2 = 1;

    //Fuse_Out_8
    //channel B7 - SOC15
    Fuse_8_Signal = (Temp_Values[15] + (0.72*(((1E6*AdcResult.ADCRESULT15))-Temp_Values[15])));                           //add in proper gain
    Temp_Values[15] = Fuse_8_Signal;
    if(Fuse_8_Signal>1E6*2048)
        Fuse_Out_Sense_8 = 0;                           //active low
    else
        Fuse_Out_Sense_8 = 1;

    //A given fuse is checked to make sure that it is functional (IF). If it is functional, the devices supplied by it are then checked for error (ELSE).
    //If a fuse is blown, then the slaved devices are assumed to be functional.

    //Fuse Error ------------> 0=Fuse Operational         1=Fuse Blown
    //MOSFET/Relay Error ----> 0=Component Operational    1=Component Inoperable
    //MOSFET/Relay Status ---> 0=Component Offline        1=Component Online
    //Vehicle Status --------> 0=Component Offline        1=Component Online
    FuseErrorCount = 0;
    RelayMOSFETErrorCounter = 0;

    if(Fuse_Out_Sense_1) //Fuse Blown
    {
        SdoMessage.FuseErrors.Flag1 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else //Fuse Functional
    {
        if(Main_Beam_Out_Sense) SdoMessage.RelayStatus.Flag1 = 1;

        if(Main_Beam_Out_Sense != Main_Beam_Ctrl_Sense)
        {
            SdoMessage.RelayErrors.Flag1 = 1; //Active High
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }
    if(Fuse_Out_Sense_2)
    {
        SdoMessage.FuseErrors.Flag2 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(High_Beam_Out_Sense) SdoMessage.RelayStatus.Flag2 = 1;

        if(High_Beam_Out_Sense != High_Beam_Ctrl_Sense)
        {
            SdoMessage.RelayErrors.Flag2 = 1; //Active High
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }

    if(!Fuse_Out_Sense_3)
    {
        SdoMessage.FuseErrors.Flag3 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(Mfet_Out_Sense_0) SdoMessage.RelayStatus.Flag6 = 1;    //Flag 6 (Not flag 3) - see User_Defines.h > struct Error_Status_Flags for Relay flag definitions
        if(Mfet_Out_Sense_4) SdoMessage.RelayStatus.Flag10 = 1;

        if(Mfet_Out_Sense_0 != Mfet_Ctrl_0)
        {
            SdoMessage.RelayErrors.Flag6 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }

        if(Mfet_Out_Sense_4 != Mfet_Ctrl_4)
        {
            SdoMessage.RelayErrors.Flag10 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }

    if(Fuse_Out_Sense_4)
    {
        SdoMessage.FuseErrors.Flag4 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {

    }

    if(!Fuse_Out_Sense_5)
    {
        SdoMessage.FuseErrors.Flag5 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(Mfet_Out_Sense_1) SdoMessage.RelayStatus.Flag7 = 1;
        if(Mfet_Out_Sense_2) SdoMessage.RelayStatus.Flag8 = 1;
        if(Mfet_Out_Sense_3) SdoMessage.RelayStatus.Flag9 = 1;

        if(Mfet_Out_Sense_1 != Mfet_Ctrl_1)
        {
            SdoMessage.RelayErrors.Flag7 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }

        if(Mfet_Out_Sense_2 != Mfet_Ctrl_2)
        {
            SdoMessage.RelayErrors.Flag8 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }

        if(Mfet_Out_Sense_3 != Mfet_Ctrl_3)
        {
            SdoMessage.RelayErrors.Flag9 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }

    if(!Fuse_Out_Sense_6)
    {
        SdoMessage.FuseErrors.Flag6 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(Horn_Out_Sense) SdoMessage.RelayStatus.Flag5 = 1;//Relay 5 ----->>> Bartho said this might change

        if(Horn_Out_Sense != Relay_Ctrl_3)
        {
            SdoMessage.RelayErrors.Flag5 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }

    if(Fuse_Out_Sense_7)
    {
        SdoMessage.FuseErrors.Flag7 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(Heated_Seats_Out_Sense) SdoMessage.RelayStatus.Flag3 = 1; //Relay 3 ----->>> Requires fixing

        if(Heated_Seats_Out_Sense != Relay_Ctrl_3)
        {
            SdoMessage.RelayErrors.Flag3 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }

    if(Fuse_Out_Sense_8)
    {
        SdoMessage.FuseErrors.Flag8 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(Radio_Out_Sense) SdoMessage.RelayStatus.Flag4 = 1; //Relay 4 ----->>> Requires Fixing

        if(Radio_Out_Sense != Relay_Ctrl_4)
        {
            SdoMessage.RelayErrors.Flag4 = 1; //Active High ----->>> Requires Fixing
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }
    if(!Fuse_Out_Sense_9)
    {
        SdoMessage.FuseErrors.Flag9 = 1;
        SdoMessage.ErrorCounter.FuseCounter++;
    }
    else
    {
        if(Mfet_Out_Sense_5) SdoMessage.RelayStatus.Flag11 = 1;
        if(Mfet_Out_Sense_6) SdoMessage.RelayStatus.Flag12 = 1;
        if(Mfet_Out_Sense_7) SdoMessage.RelayStatus.Flag13 = 1;
        if(Mfet_Out_Sense_8) SdoMessage.RelayStatus.Flag14 = 1;

        if(Mfet_Out_Sense_5 != Mfet_Ctrl_5)
        {
            SdoMessage.RelayErrors.Flag11 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }

        if(Mfet_Out_Sense_6 != Mfet_Ctrl_6)
        {
            SdoMessage.RelayErrors.Flag12 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }

        if(Mfet_Out_Sense_7 != Mfet_Ctrl_7)
        {
            SdoMessage.RelayErrors.Flag13 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }

        if(Mfet_Out_Sense_8 != Mfet_Ctrl_8)
        {
            SdoMessage.RelayErrors.Flag14 = 1;
            SdoMessage.ErrorCounter.RelayCounter++;
        }
    }
    if(SdoMessage.ErrorCounter.FuseCounter == 9)
    {
        //If all the fuses have registered as blown then it is assumed that the master fuse has blown and that all slave fuses are in fact operational
        ClearErrorFlags(1); //Clear only fuse flags and counter --->see function definition in User_Functions.c for argument definitions
        SdoMessage.FuseErrors.Flag10 = 1;
        SdoMessage.ErrorCounter.FuseCounter = 1;
    }

    //VEHICLE STATUS FLAGS ***********************************************************************************************************************************************************************
    if(Brake_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(!Handbrake_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(Key_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(E_Stop_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(Forward_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(Reverse_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(Flasher_L_Out_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(Flasher_R_Out_Sense) SdoMessage.VehicleStatus.Flag1 = 1;

    if(V_Reg_In_Sense) SdoMessage.VehicleStatus.Flag1 = 1;


    if(Main_Beam_Ctrl_Sense && !(SdoMessage.FuseErrors.Flag1)) //checks that fuse is not blown
    {
        if(counter1 < 10 && !HeadSwitched) //timeout (currently set to (1/50)*10 = 200ms) to allow for fuses to switch and head light to respond to command before registering an error
        {
            if(Fusebox_Current - Current_Prev >= 10000) //checks if the head light switches on after commanded to do so (current steps up as expected)
            {
                HeadLightBlown = 0; //Sets to 'not blown' in the event that the bulb is fixed after a breakage (prevents need to reset value manually after repairs)
                HeadSwitched = 1; //code skips this block if a successful on state was reached
            }
        }
        else if(CheckAgain1)//bulb has blown
        {
            HeadLightBlown = 1; //Expected current step has not occurred, head light assumed blown
            CheckAgain1 = 0; //if bulb is blown don't bother checking
        }

        if(HeadSwitched && (Current_Prev - Fusebox_Current >= 0)) //head light switched correctly initially but then blew during operation (unexpected current drop without a switch off command)
        {
            HeadLightBlown = 1;
            CheckAgain1 = 0;
            HeadSwitched = 0;
        }
        if(counter1 > 3000)
        {
            /*This 'if' periodically resets the CheckAgain flag to force a re-check on the bulb (even if it is blown).
             * Although it makes the program less efficient,
             * it will allow the program to self detect that a blown bulb has been
             * replaced rather than the technician having to manually reset the flag.
             * Currently set to (1/50)*3000 = 1 minute
                CheckAgain1 = 0;
                counter1 = 0;*/
        }
        counter1++;
    }
    if(High_Beam_Ctrl_Sense && !(SdoMessage.FuseErrors.Flag2))
    {
        if(counter2 < 10 && !HighSwitched) //the HighSwitched Variable prevents this 'if' block from running again if a successful switch was detected
        {
            if(Fusebox_Current - Current_Prev > 5) // the value must still be ascertained
            {
                HighBeamBlown = 0;
                HighSwitched = 1;
            }
        }
        else if(CheckAgain2)
        {
            HighBeamBlown = 0;
            CheckAgain2 = 0; //if bulb is blown dont bother checking again
        }

        if(HighSwitched && (Current_Prev - Fusebox_Current >= 0))
        {
            HighBeamBlown = 1;
            CheckAgain2 = 0;
            HighSwitched = 0;
        }
        counter2++;
    } //need to add functionality for when high and main beam are switched on in close proximity to one another (temporally)
    Current_Prev = Fusebox_Current;

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

__interrupt void i2c_int1a_isr(void)     // I2C-A
{
   /* Uint16 IntSource;

    // Read interrupt source
    IntSource = I2caRegs.I2CISRC.all;

    // Interrupt source = stop condition detected
    if(IntSource == I2C_SCD_ISRC)
    {
        // If completed message was writing data, reset msg to inactive state
        if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY)
        {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
            //I2cMsgIn1.MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;
        }
        else
        {
            // If a message receives a NACK during the address setup portion of the
            // EEPROM read, the code further below included in the register access ready
            // interrupt source code will generate a stop condition. After the stop
            // condition is received (here), set the message status to try again.
            // User may want to limit the number of retries before generating an error.
            if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
            {
                CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART;
            }
            // If completed message was reading EEPROM data, reset msg to inactive state
            // and read data from FIFO.
            else if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY)
            {
                CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;

                DataOut = I2caRegs.I2CDRR;
                DataOut2 = I2caRegs.I2CDRR;
            }
        }
    }  // end of stop condition detected
    else if(IntSource == 2)												//no acknowledge condition
    {
        // Generate some error due to invalid interrupt source
        CurrentMsgPtr->MsgStatus = 0xFF;
    }
    else
    {
        // Generate some error due to invalid interrupt source
        //__asm("   ESTOP0");
        CurrentMsgPtr->MsgStatus = 0xFF;
    }*/
    // Enable future I2C (PIE Group 8) interrupts
    PieCtrlRegs.PIEACK.bit.ACK8 = 1;
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
                else if(PDO_Instruction == 0xFF00 && LowPowerMode)   //Low power mode disabled
                {
                    LowPowerMode = 1;
                }
                else ; //Invalid instruction ----> must still decide what to do

                PDO_Data_Low += RelayMOSFETError; //PDO response includes Fuse and Relay/Mosfet error flags as well as Vehcile and Relay/Mosfet status flags
                PDO_Data_Low = (PDO_Data_Low<<16) + FuseError;
                PDO_Data_High += VehicleStatus;
                PDO_Data_High = (PDO_Data_High<<16) + RelayMOSFETStatus;
                CANTransmit(0x1BC, PDO_Data_High, PDO_Data_Low, 8, 7); //PDO_MISO
            }
        }

        if(SDO_MOSI_Ctrl == 0x42)
        {
            SDO_MOSI_Ctrl = ECanaMboxes.MBOX6.MDL.all & 0xFF;
            SDO_MOSI_Request = (ECanaMboxes.MBOX6.MDL.all>>8) & 0xFFFF;

            SDO_MISO_Ctrl = ((Uint32)SDO_MOSI_Request)<<8 | 0x40;

            SDO_MISO_Data[0] = Fusebox_Current;             //SDO 0x0900
            SDO_MISO_Data[1] = Fusebox_Temperature;         //SDO 0x0902
            SDO_MISO_Data[2] = FuseError;                   //SDO 0x0904
            SDO_MISO_Data[3] = RelayMOSFETStatus;           //SDO 0x0906
            SDO_MISO_Data[4] = RelayMOSFETError;            //SDO 0x0908
            SDO_MISO_Data[5] = VehicleStatus;               //SDO 0x090A
            SDO_MISO_Data[6] = ErrorCounter;                //SDO 0x090C
            SDO_MISO_Data[7] = IgnitionCounter;             //SDO 0x0912
            SDO_MISO_Data[8] = OperationalCounter;          //SDO 0x0914

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

