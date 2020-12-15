/*
 * User_Functions.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#include "User_Defines.h"

void Initialise_FuseBox(void)
{

    InitSysCtrl();
    //    InitI2CGpio();
    Init_Gpio();
    InitAdc();
    //	InitSpiaGpio();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EALLOW; // This is needed to write to EALLOW protected registers
    //PieVectTable.I2CINT1A = &i2c_int1a_isr;
    PieVectTable.TINT0 = &cpu_timer0_isr;
    PieVectTable.TINT1 = &cpu_timer1_isr;
    PieVectTable.TINT2 = &cpu_timer2_isr;
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //    I2CA_Init();
    InitCpuTimers();

    ConfigCpuTimer(&CpuTimer0, 60, 500000); //2 hz
    ConfigCpuTimer(&CpuTimer1, 60, 20000);  //50 hz
    ConfigCpuTimer(&CpuTimer2, 60, 500);    //2 Khz         //500

    CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
    CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
    CpuTimer2Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

    // Enable ADC interrupt 10 in the PIE: Group 10 interrupt 1
    PieCtrlRegs.PIEIER10.bit.INTx1 = 1;
    IER |= M_INT10;

    // Enable CPU interrupt 1 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;          //clock
    IER |= M_INT1;
    IER |= M_INT13;
    IER |= M_INT14;

    // Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    // Enable I2C INT8 which is connected to PIE group 8
    IER |= M_INT8;

    EnableInterrupts();

    EINT;
    ERTM;   // Enable Global realtime interrupt DBGM

    CAN_Init();
    configADC();

    // Reset the watchdog counter
    ServiceDog();

    // Enable the watchdog
    EALLOW;
    SysCtrlRegs.WDCR = 0x002F;
    EDIS;

    //DisableDog();
}

void Init_Gpio(void)
{
    EALLOW;

    //GPADIR: 0 - input
    //GPADIR: 1 - output
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;     //Mfet_Ctrl_8
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      //Mfet_Ctrl_8

    /*GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     //Mfet_Ctrl_9
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;      //Mfet_Ctrl_9
    MOSFET 9 REMOVED*/

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;     //Mfet_Ctrl_6
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;      //Mfet_Ctrl_6

    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     //Mfet_Ctrl_7
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;      //Mfet_Ctrl_7

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;     //Mfet_Ctrl_3
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;      //Mfet_Ctrl_3

    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     //Mfet_Ctrl_4
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;      //Mfet_Ctrl_4

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     //Mfet_Ctrl_2
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;      //Mfet_Ctrl_2

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     //Mfet_Out_Sense_6
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      //Mfet_Out_Sense_6

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     //Mfet_Out_Sense_3
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;      //Mfet_Out_Sense_3

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     //Mfet_Out_Sense_6
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;      //Mfet_Out_Sense_6

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;     //Mfet_Ctrl_0
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;      //Mfet_Ctrl_0

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;     //Mfet_Ctrl_1
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;      //Mfet_Ctrl_1

    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;     //Fuse_Out_Sense_9
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;      //Fuse_Out_Sense_9

    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;     //Main_Beam_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;      //Main_Beam_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;     //Heated_Seats_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;      //Heated_Seats_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;     //Wiper_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;      //Wiper_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;     //Mfet_Out_Sense_5
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;      //Mfet_Out_Sense_5

    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;     //Mfet_Out_Sense_2
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;      //Mfet_Out_Sense_2

    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;     //Mfet_Out_Sense_0
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;      //Mfet_Out_Sense_0

    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;     //Reverse_In_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;      //Reverse_In_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;     //High_Beam_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;      //High_Beam_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;     //High_Beam_Ctrl_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;      //High_Beam_Ctrl_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;     //Horn_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;      //Horn_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;     //Flasher_R_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;      //Flasher_R_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;     //Mfet_Out_Sense_4
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;      //Mfet_Out_Sense_4

    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;     //Fuse_Out_Sense_5
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;      //Fuse_Out_Sense_5

    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;     //Fuse_Out_Sense_3
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;      //Fuse_Out_Sense_3

    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;     //LED_Out
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;      //LED_Out

    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;     //Main_Beam_Ctrl_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;      //Main_Beam_Ctrl_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;     //Flasher_L_Out_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;      //Flasher_L_Out_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO39 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;     //Mfet_Out_Sense_8
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;      //Mfet_Out_Sense_8

    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;     //Mfet_Ctrl_5
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;      //Mfet_Ctrl_5

    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;     //Mfet_Out_Sense_7
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 0;      //Mfet_Out_Sense_7

    GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;     //Handbrake_In_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;      //Handbrake_In_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;     //Radio_Out_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;      //Radio_Out_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;     //Mfet_Out_Sense_1
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;      //Mfet_Out_Sense_1

    EDIS;
}

void Toggle_LED(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO27 = 1;
}

//Henry's Functions *******************************************************************************************************
void ClearErrorFlags(Uint16 Flag_Selection)
{
    /*Sets selected error flags and counters that appear in Annex A and B of the fusebox documentation
     * to the default state (0x0)
     * Uint16 Flag_Selection:
     * 0 - Reset all
     * 1 - Reset Fuse Errors and counter only
     * 2 - Reset Relay errors and counter only
     **/

    //Fuse Errors ----------------------
    if(!Flag_Selection || Flag_Selection == 1)
    {
        SdoMessage.FuseErrors = 0;
        SdoMessage.FuseErrorCounter = 0;
    }

    if(!Flag_Selection || Flag_Selection == 2)
    {
        //Relay and Mosfet Errors -----------
        SdoMessage.RelayErrors = 0;
        SdoMessage.RelayErrorCounter = 0;
    }
}

void EnableLowPower(void)
{
    /*If the master PDO asserts low power mode, all nonessential features will be shut down
     * Currently classified as nonessential:
     * All MOSFETS
     * */

    Mfet_Ctrl_0 = 0;
    Mfet_Ctrl_1 = 0;
    Mfet_Ctrl_2 = 0;
    Mfet_Ctrl_3 = 0;
    Mfet_Ctrl_4 = 0;
    Mfet_Ctrl_5 = 0;
    Mfet_Ctrl_6 = 0;
    Mfet_Ctrl_7 = 0;
    Mfet_Ctrl_8 = 0;
}

void SetFlags(void)
{
    //A given fuse is checked to make sure that it is functional (IF). If it is functional, the devices supplied by it are then checked for error (ELSE).
    //If a fuse is blown, then the slaved devices are assumed to be functional.

    //Fuse Error ------------> 0=Fuse Operational         1=Fuse Blown
    //MOSFET/Relay Error ----> 0=Component Operational    1=Component Inoperable
    //MOSFET/Relay Status ---> 0=Component Offline        1=Component Online
    //Vehicle Status --------> 0=Component Offline        1=Component Online

    //The bits in each SdoMessage member are assigned according to the bit layout given in Annex A of
    //the fuse box documentation.

    //The mapping which indicates what MOSFETs and Relays are connected to each fuse is taken from the KiCAD schematic (UpperBoard) of the PCB

    if(Fuse_Out_Sense_1) //Fuse Blown
    {
        SdoMessage.FuseErrors |= 0x0001; //sets the correct bit to acknowledge error
        SdoMessage.FuseErrorCounter++;
    }
    else //Fuse Functional
    {
        if(Main_Beam_Out_Sense) SdoMessage.RelayStatus |= 0x0001;

        if(Main_Beam_Out_Sense != Main_Beam_Ctrl_Sense)
        {
            SdoMessage.RelayErrors |= 0x0001;
            SdoMessage.RelayErrorCounter++;
        }
    }
    if(Fuse_Out_Sense_2)
    {
        SdoMessage.FuseErrors |= 0x0002;
        SdoMessage.FuseErrorCounter++;
    }
    else
    {
        if(High_Beam_Out_Sense) SdoMessage.RelayStatus |= 0x0002;

        if(High_Beam_Out_Sense != High_Beam_Ctrl_Sense)
        {
            SdoMessage.RelayErrors |= 0x0002;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(!Fuse_Out_Sense_3)
    {
        SdoMessage.FuseErrors |= 0x0004;
        SdoMessage.FuseErrorCounter++;
    }
    else
    {
        if(Mfet_Out_Sense_0) SdoMessage.RelayStatus |= 0x0020;
        if(Mfet_Out_Sense_4) SdoMessage.RelayStatus |= 0x0200;

        if(Mfet_Out_Sense_0 != Mfet_Ctrl_0)
        {
            SdoMessage.RelayErrors |= 0x0020;
            SdoMessage.RelayErrorCounter++;
        }

        if(Mfet_Out_Sense_4 != Mfet_Ctrl_4)
        {
            SdoMessage.RelayErrors |= 0x0200;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(Fuse_Out_Sense_4)
    {
        SdoMessage.FuseErrors |= 0x0008;
        SdoMessage.FuseErrorCounter +=1;
    }
    else
    {
        //Fuse 4 doesn't output to any device at the moment as far as I can tell
    }

    if(!Fuse_Out_Sense_5)
    {
        SdoMessage.FuseErrors |= 0x0010;
        SdoMessage.FuseErrorCounter++;
    }
    else
    {
        if(Mfet_Out_Sense_1) SdoMessage.RelayStatus |= 0x0040;
        if(Mfet_Out_Sense_2) SdoMessage.RelayStatus |= 0x0080;
        if(Mfet_Out_Sense_3) SdoMessage.RelayStatus |= 0x0100;

        if(Mfet_Out_Sense_1 != Mfet_Ctrl_1)
        {
            SdoMessage.RelayErrors |= 0x0040;
            SdoMessage.RelayErrorCounter++;
        }

        if(Mfet_Out_Sense_2 != Mfet_Ctrl_2)
        {
            SdoMessage.RelayErrors |= 0x0080;
            SdoMessage.RelayErrorCounter++;
        }

        if(Mfet_Out_Sense_3 != Mfet_Ctrl_3)
        {
            SdoMessage.RelayErrors |= 0x0100;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(!Fuse_Out_Sense_6)
    {
        SdoMessage.FuseErrors |= 0x0020;
        SdoMessage.FuseErrorCounter++;
    }
    else
    {
        if(Horn_Out_Sense) SdoMessage.RelayStatus |= 0x0010;

        if(Horn_Out_Sense != Relay_Ctrl_3)
        {
            SdoMessage.RelayErrors |= 0x0010;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(!Fuse_Out_Sense_7)
    {
        SdoMessage.RelayErrors |= 0x0040;
        SdoMessage.RelayErrorCounter++;
    }
    else
    {
        if(Heated_Seats_Out_Sense) SdoMessage.RelayStatus |= 0x0004;

        if(Heated_Seats_Out_Sense != Relay_Ctrl_3)
        {
            SdoMessage.RelayErrors |= 0x0004;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(Fuse_Out_Sense_8)
    {
        SdoMessage.FuseErrors |= 0x0080;
        SdoMessage.FuseErrorCounter++;
    }
    else
    {
        if(Radio_Out_Sense) SdoMessage.RelayStatus |= 0x0008;

        if(Radio_Out_Sense != Relay_Ctrl_4)
        {
            SdoMessage.RelayErrors |= 0x0008;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(!Fuse_Out_Sense_9)
    {
        SdoMessage.FuseErrors |= 0x0100;
        SdoMessage.FuseErrorCounter++;
    }
    else
    {
        if(Mfet_Out_Sense_5) SdoMessage.RelayStatus |= 0x0400;
        if(Mfet_Out_Sense_6) SdoMessage.RelayStatus |= 0x0800;
        if(Mfet_Out_Sense_7) SdoMessage.RelayStatus |= 0x1000;
        if(Mfet_Out_Sense_8) SdoMessage.RelayStatus |= 0x2000;

        if(Mfet_Out_Sense_5 != Mfet_Ctrl_5)
        {
            SdoMessage.RelayErrors |= 0x0400;
            SdoMessage.RelayErrorCounter++;
        }

        if(Mfet_Out_Sense_6 != Mfet_Ctrl_6)
        {
            SdoMessage.RelayErrors |= 0x0800;
            SdoMessage.RelayErrorCounter++;
        }

        if(Mfet_Out_Sense_7 != Mfet_Ctrl_7)
        {
            SdoMessage.RelayErrors |= 0x1000;
            SdoMessage.RelayErrorCounter++;
        }

        if(Mfet_Out_Sense_8 != Mfet_Ctrl_8)
        {
            SdoMessage.RelayErrors |= 0x2000;
            SdoMessage.RelayErrorCounter++;
        }
    }

    if(SdoMessage.FuseErrorCounter == 9)
    {
        //If all the fuses have registered as blown then it is assumed that the master fuse has blown and that all slave fuses are in fact operational
        ClearErrorFlags(1); //Clear only fuse flags and counter --->see function definition in User_Functions.c for argument definitions
        SdoMessage.FuseErrors |= 0x0200;
        SdoMessage.FuseErrorCounter = 1;
    }

    //VEHICLE STATUS FLAGS ***********************************************************************************************************************************************************************
    if(Brake_In_Sense) SdoMessage.VehicleStatus |= 0x0001;

    if(!Handbrake_In_Sense) SdoMessage.VehicleStatus |= 0x0002;

    if(Key_In_Sense) SdoMessage.VehicleStatus |= 0x0004;

    if(E_Stop_In_Sense) SdoMessage.VehicleStatus |= 0x0008;

    if(Forward_In_Sense) SdoMessage.VehicleStatus |= 0x0010;

    if(Reverse_In_Sense) SdoMessage.VehicleStatus |= 0x0020;

    if(Flasher_L_Out_Sense) SdoMessage.VehicleStatus |= 0x0040;

    if(Flasher_R_Out_Sense) SdoMessage.VehicleStatus |= 0x0080;

    if(V_Reg_In_Sense) SdoMessage.VehicleStatus |= 0x0100;

}

void ADCtoGPIO(void)
{
    static float Temp_Floats[2];
    static long Temp_Values[14];
    long Fuse_1_Signal;
    long Fuse_4_Signal;
    long Vts;
    long Rts;
    long Forward_Signal;
    long Brake_Signal;
    long Key_Sense_Signal;
    long Horn_Signal;
    long E_stop_Signal;
    long Position_Signal;
    long Relay_3_Signal;
    long Relay_4_Signal;
    long V_Reg_Signal;
    long Fuse_7_Signal;
    long Fuse_2_Signal;
    long Fuse_8_Signal;

    //ADC result multiplied by 1e12 to avoid gorra round off errors when using int instead of float
    //ServiceDog();

    /*float Fc = 10;     //clock frequency [Hz]
    float Ts = 1/50;   //sample period [s]*/

    //Fuse box Current
    //channel A0 - SOC0
    Fusebox_Current = Temp_Floats[0] + (0.72*((0.02*(AdcResult.ADCRESULT0))-Temp_Floats[0]));                  //Test gain (3.3/4096 *1/39.6mV)
    Temp_Floats[0] = Fusebox_Current;

    //Fuse_Out_1
    //channel B2 - SOC1
    Fuse_1_Signal = (Temp_Values[0] + (72*((1E6*AdcResult.ADCRESULT1))-Temp_Values[0]))/100;                          //add in proper gain
    Temp_Values[0] = Fuse_1_Signal;
    if(Fuse_1_Signal>1E6*2048)
        Fuse_Out_Sense_1 = 0;   //active when voltage is low
    else
        Fuse_Out_Sense_1 = 1;

    //Fuse_Out_4
    //channel B4  - SOC2
    Fuse_4_Signal = (Temp_Values[1] + (72*((1E6*AdcResult.ADCRESULT2))-Temp_Values[1]))/100;                          //add in proper gain
    Temp_Values[1] = Fuse_4_Signal;
    if(Fuse_4_Signal>1E6*2048)
        Fuse_Out_Sense_4 = 0;                           //active when voltage is low
    else
        Fuse_Out_Sense_4 = 1;

    //Fuse box Temperature
    //channel A1 - SOC3
    Vts = Temp_Floats[1] + (0.72*((0.00080566*(AdcResult.ADCRESULT3))-Temp_Floats[1]));                     //add in proper gain
    Temp_Floats[1] = Vts;
    Rts = (33000/Vts) - 10000;
    Fusebox_Temperature = (1/((log(Rts/10000))/4000+0.003356))-273;

    //Forward input
    //channel A2 - SOC4
    Forward_Signal = (Temp_Values[2] + (72*((1E6*AdcResult.ADCRESULT4))-Temp_Values[2]))/100;                           //add in proper gain
    Temp_Values[2] = Forward_Signal;
    if(Forward_Signal>1E6*2048)
        Forward_In_Sense = 1;                           //active high
    else
        Forward_In_Sense = 0;
    //Brake light output
    //channel A3 - SOC5
    Brake_Signal = (Temp_Values[3] + (72*((1E6*AdcResult.ADCRESULT5))-Temp_Values[3]))/100;                           //add in proper gain
    Temp_Values[3] = Brake_Signal;
    if(Brake_Signal>1E6*2048)
        Brake_In_Sense = 1;                           //active high
    else
        Brake_In_Sense = 0;

    //Key switch input
    //channel A4 - SOC6
    Key_Sense_Signal = (Temp_Values[4] + (72*((1E6*AdcResult.ADCRESULT6))-Temp_Values[4]))/100;                           //add in proper gain
    Temp_Values[4] = Key_Sense_Signal;
    if(Key_Sense_Signal>1E6*2048)
        Key_In_Sense = 1;                           //active high
    else
        Key_In_Sense = 0;

    //Horn output
    //channel A5 - SOC7
    Horn_Signal = (Temp_Values[5] + (72*((1E6*AdcResult.ADCRESULT7))-Temp_Values[5]))/100;                           //add in proper gain
    Temp_Values[5] = Horn_Signal;
    if(Horn_Signal>1E6*2048)
        Horn_Ctrl_Sense = 0;                           //active high ------>>> LOW
    else
        Horn_Ctrl_Sense = 1;

    //E-stop
    //channel A6 - SOC8
    E_stop_Signal = (Temp_Values[6] + (72*((1E6*AdcResult.ADCRESULT8))-Temp_Values[6]))/100;                           //add in proper gain
    Temp_Values[6] = E_stop_Signal;
    if(E_stop_Signal>1E6*2048)
        E_Stop_In_Sense = 1;                           //active high
    else
        E_Stop_In_Sense = 0;

    //Position Switch
    //channel A7 - SOC9
    Position_Signal = (Temp_Values[7] + (72*((1E6*AdcResult.ADCRESULT9))-Temp_Values[7]))/100;                           //add in proper gain
    Temp_Values[7] = Position_Signal;
    if(Position_Signal>1E6*2048)
        Position_Out_Sense = 1;                           //active high
    else
        Position_Out_Sense = 0;

    //Relay 3                           -- needs to swop with relay 3 output (Heated seats)
    //channel B0 - SOC10
    Relay_3_Signal = (Temp_Values[8] + (72*((1E6*AdcResult.ADCRESULT10))-Temp_Values[8]))/100;                           //add in proper gain
    Temp_Values[8] = Relay_3_Signal;
    if(Relay_3_Signal>1E6*2048)
        Heated_Seats_Out_Sense = 1;                           //active high
    else
        Heated_Seats_Out_Sense = 0;

    //Relay 4                            -- needs to swop to relay 4 output (Radio out)
    //channel B1 - SOC11
    Relay_4_Signal = (Temp_Values[9] + (72*((1E6*AdcResult.ADCRESULT11))-Temp_Values[9]))/100;                           //add in proper gain
    Temp_Values[9] = Relay_4_Signal;
    if(Relay_4_Signal>1E6*2048)
        Radio_Out_Sense = 1;                           //active high
    else
        Radio_Out_Sense = 0;

    //12V Regulator - secondary
    //channel B3- SOC12
    V_Reg_Signal = (Temp_Values[10] + (72*((1E6*AdcResult.ADCRESULT12))-Temp_Values[10]))/100;                           //add in proper gain
    Temp_Values[10] = V_Reg_Signal;
    if(V_Reg_Signal>1E6*2048)
        V_Reg_In_Sense = 1;                           //active high
    else
        V_Reg_In_Sense = 0;

    //Fuse_Out_7
    //channel B5 - SOC13
    Fuse_7_Signal = (Temp_Values[11] + (72*((1E6*AdcResult.ADCRESULT13))-Temp_Values[11]))/100;                           //add in proper gain
    Temp_Values[11] = Fuse_7_Signal;
    if(Fuse_7_Signal>1E6*2048)
        Fuse_Out_Sense_7 = 0;                           //active low
    else
        Fuse_Out_Sense_7 = 1;

    //Fuse_Out_2
    //channel B6 - SOC14
    Fuse_2_Signal = (Temp_Values[12] + (72*((1E6*AdcResult.ADCRESULT14))-Temp_Values[12]))/100;                           //add in proper gain
    Temp_Values[12] = Fuse_2_Signal;
    if(Fuse_2_Signal>1E6*2048)
        Fuse_Out_Sense_2 = 0;                           //active low
    else
        Fuse_Out_Sense_2 = 1;

    //Fuse_Out_8
    //channel B7 - SOC15
    Fuse_8_Signal = (Temp_Values[13] + (72*((1E6*AdcResult.ADCRESULT15))-Temp_Values[13]))/100;                           //add in proper gain
    Temp_Values[13] = Fuse_8_Signal;
    if(Fuse_8_Signal>1E6*2048)
        Fuse_Out_Sense_8 = 0;                           //active low
    else
        Fuse_Out_Sense_8 = 1;
}


void HeadlightBulbCheck(void)
{
    static float Current_Prev = 0;
    Uint16 counter1 = 0;        //timeout counter for main light to switch on after command is received
    Uint16 counter2 = 0;        //timeout counter for high beam to switch on after command is received
    Uint16 HeadSwitched = 0;
    Uint16 HighSwitched = 0;
    Uint16 CheckAgain1 = 1;
    Uint16 CheckAgain2 = 1;

    if(Main_Beam_Ctrl_Sense && !(SdoMessage.FuseErrors && 0x0001)) //checks that fuse is not blown
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
            CheckAgain1 = 0; //if bulb is blown don't bother checking again
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
             * Currently set to (1/50)*3000 = 1 minute - Based on 50 Hz timer*/
            CheckAgain1 = 0;
            counter1 = 0;
        }
        counter1++;
    }
    if(High_Beam_Ctrl_Sense && !(SdoMessage.FuseErrors && 0x0002))
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
        if(counter2 > 3000)
        {
            CheckAgain2 = 0;
            counter2 = 0;
        }
        counter2++;
    }
    Current_Prev = Fusebox_Current; //sets a static value for historic reference
}
