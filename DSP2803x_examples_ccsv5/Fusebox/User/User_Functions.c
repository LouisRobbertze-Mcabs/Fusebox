/*
 * User_Functions.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#include "User_Defines.h"

void Initialise_BMS(void)
{
    //flagCurrent = 0;

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
    PieVectTable.I2CINT1A = &i2c_int1a_isr;
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
     * Flag_Selection:
     * 0 - Reset all
     * 1 - Reset Fuse Errors and counter only
     * 2 - Reset Relay errors and counter only
     **/

    //Fuse Errors ----------------------
    if(!Flag_Selection || Flag_Selection == 1)
    {
        SdoMessage.FuseErrors.Flag1 = 0;
        SdoMessage.FuseErrors.Flag2 = 0;
        SdoMessage.FuseErrors.Flag3 = 0;
        SdoMessage.FuseErrors.Flag4 = 0;
        SdoMessage.FuseErrors.Flag5 = 0;
        SdoMessage.FuseErrors.Flag6 = 0;
        SdoMessage.FuseErrors.Flag7 = 0;
        SdoMessage.FuseErrors.Flag8 = 0;
        SdoMessage.FuseErrors.Flag9 = 0;
        SdoMessage.FuseErrors.Flag10 = 0;
        SdoMessage.FuseErrors.Flag11 = 0;
        SdoMessage.FuseErrors.Flag12 = 0;
        SdoMessage.FuseErrors.Flag13 = 0;
        SdoMessage.FuseErrors.Flag14 = 0;
        SdoMessage.FuseErrors.Flag15 = 0;
        SdoMessage.FuseErrors.Flag16 = 0;

        SdoMessage.ErrorCounter.FuseCounter = 0;
    }

    if(!Flag_Selection || Flag_Selection == 2)
    {
        //Relay and Mosfet Errors -----------
        SdoMessage.RelayErrors.Flag1 = 0;
        SdoMessage.RelayErrors.Flag2 = 0;
        SdoMessage.RelayErrors.Flag3 = 0;
        SdoMessage.RelayErrors.Flag4 = 0;
        SdoMessage.RelayErrors.Flag5 = 0;
        SdoMessage.RelayErrors.Flag6 = 0;
        SdoMessage.RelayErrors.Flag7 = 0;
        SdoMessage.RelayErrors.Flag8 = 0;
        SdoMessage.RelayErrors.Flag9 = 0;
        SdoMessage.RelayErrors.Flag10 = 0;
        SdoMessage.RelayErrors.Flag11 = 0;
        SdoMessage.RelayErrors.Flag12 = 0;
        SdoMessage.RelayErrors.Flag13 = 0;
        SdoMessage.RelayErrors.Flag14 = 0;
        SdoMessage.RelayErrors.Flag15 = 0;
        SdoMessage.RelayErrors.Flag16 = 0;

        SdoMessage.ErrorCounter.RelayCounter = 0;
    }
}



