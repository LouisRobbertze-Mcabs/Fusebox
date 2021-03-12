//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V127 $
// $Release Date: March 30, 2013 $
//###########################################################################

#include "User\User_Defines.h"

void main(void)
{
    Operational_State = 127; //pre op state
    ClearErrorFlags(0);     //Clear all error flags and counters --->see function definition in User_Functions.c for argument definitions
	Initialise_FuseBox();
	Operational_State = 5; //operational state
	EnableUSBcharger(); //switches on USB charger
	while(1)
	{
		if(counter_2Hz == 1)
		{
		    ServiceDog();
		}
		if(counter_2Hz == 2)
		{
			Toggle_LED();
			//SwitchReverseSensor();
            if(LowPowerMode) EnableLowPower();
            else if(!LowPowerMode) DisableLowPower();
			ServiceDog();
			counter_2Hz = 0;
		}

	}
}
