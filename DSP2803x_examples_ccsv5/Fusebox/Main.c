//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V127 $
// $Release Date: March 30, 2013 $
//###########################################################################

#include "User\User_Defines.h"
extern volatile Uint16 LowPowerMode;

void main(void)
{
    //set all error/status flags and counters to zero
    ClearErrorFlags(0); //Clear all error flags and counters --->see function definition in User_Functions.c for argument definitions
	Initialise_BMS();
	while(1)
	{
		if(counter_2Hz == 1)
		{
		    ServiceDog();
	        if(LowPowerMode)
	        {
	            /*If the master PDO asserts low power mode, all nonessential features will be shut down
	             * Currently classified as nonessential:
	             * All MOSFETS
	             * Relays*/

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
		}
		if(counter_2Hz == 2)
		{
			Toggle_LED();
			ServiceDog();
			/*Read_Cell_Voltages();
			Process_Voltages();
			Calculate_Current();*/


			//Read_Temperatures();
			/*Read_System_Status();
			Process_System_Status();*/

			counter_2Hz = 0;
		}

	}
}
