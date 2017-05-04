//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V127 $
// $Release Date: March 30, 2013 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "User\User_Defines.h"
#include "User\User_Prototypes.h"
#include "User\User_Globals.h"

void main(void)
{
    Initialise_BMS();

    for(;;)
    {
        if(counter_2Hz == 2)
        {
            Toggle_LED();

            Read_Cell_Voltages();
            Process_Voltages();
            Calculate_Current();
            //Ah = Ah + Current*0.00027778;
            //ContactorOut = 1;
            Read_Temperatures();

            //Balance(5,3.31);

            Read_System_Status();
            Process_System_Status();

            counter_2Hz = 0;
            Reset_ADC();
        }
    }
}
