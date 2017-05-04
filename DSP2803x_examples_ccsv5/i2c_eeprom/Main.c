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
    initialise_BMS();
    // Application loop
    for(;;)
    {
        if(counter_2Hz == 2)
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
            counter_2Hz = 0;

            I2CA_WriteData(0x04,0x8);											//reset adc
            I2CA_WriteData(0x04,0x18);
        }
    }
}
