/*
 * User_Globals.h
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#ifndef USER_GLOBALS_H_
#define USER_GLOBALS_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "User_Defines.h"
extern volatile long Fusebox_Current;
extern volatile long Fusebox_Temperature;
extern volatile Uint16 counter_2Hz;
extern Uint16 NodeID;
extern volatile float ADCgain;
extern volatile float ADCoffset;

//Henry's Variables start here
extern struct Master_Variable_Table SdoMessage;

//extern volatile StateFlag;  //0=Stopped State   1=pre-operational State    2=operational state



#endif /* USER_GLOBALS_H_ */
