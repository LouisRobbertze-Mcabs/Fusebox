//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V127 $
// $Release Date: March 30, 2013 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "User_Defines.h"
#include "User_Prototypes.h"
#include "User_Globals.h"

void main(void)
{
    flagCurrent = 0;

    InitSysCtrl();
    InitI2CGpio();
    Init_Gpio();
    InitAdc();
    InitSpiaGpio();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EALLOW;	// This is needed to write to EALLOW protected registers
    PieVectTable.I2CINT1A = &i2c_int1a_isr;
    PieVectTable.TINT0 = &cpu_timer0_isr;
    PieVectTable.TINT1 = &cpu_timer1_isr;
    PieVectTable.TINT2 = &cpu_timer2_isr;
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    I2CA_Init();
    InitCpuTimers();

    ConfigCpuTimer(&CpuTimer0, 60, 500000);	//2 hz
    ConfigCpuTimer(&CpuTimer1, 60, 20000);	//50 hz
    ConfigCpuTimer(&CpuTimer2, 60, 500);	//2 Khz			//500

    CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
    CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
    CpuTimer2Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

    // Enable interrupts required for this example

    // Enable ADC interrupt 10 in the PIE: Group 10 interrupt 1
    PieCtrlRegs.PIEIER10.bit.INTx1 = 1;
    IER |= M_INT10;

    // Enable CPU interrupt 1 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;			//clock
    IER |= M_INT1;
    IER |= M_INT13;
    IER |= M_INT14;

    // Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    // Enable I2C INT8 which is connected to PIE group 8
    IER |= M_INT8;

    ////////////////////////////B. Horn
    EnableInterrupts();
    ////////////////////////////B. Horn

    EINT;
    ERTM;   // Enable Global realtime interrupt DBGM

    CANSetup();
    CANMailboxConfig();
    CANInterruptConfig();

    configADC();

    //Turn on and initialise Bq76940
    Bq76940_Init();

    //	Shut_D_BQ();
    // Application loop
    for(;;)
    {
        if(count == 2)
        {
            Read_CellVol();
            //calculate current										//maak miskien funksie
            current = (test_current-2085)* 0.125;					//2035    maal, moenie deel nie!!!!     0.0982--200/2048
            //Ah = Ah + current*0.00027778;
            //ContactorOut = 1;
            Read_Temp();

            GpioDataRegs.GPATOGGLE.bit.GPIO5 = 1;		//toggle led
            //Balance(5,3.31);

            system_status = I2CA_ReadData(&I2cMsgIn1,0x00, 1);
            if(system_status != 00)
            {
                I2CA_WriteData(0x00, 0x3F);
            }

            count1= count1+2;
            count = 0;

            I2CA_WriteData(0x04,0x8);											//reset adc
            I2CA_WriteData(0x04,0x18);
        }
    }
}
