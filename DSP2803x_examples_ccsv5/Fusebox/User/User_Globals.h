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

//Henry's Variables start here *********************************************************************************
extern struct Master_Variable_Table SdoMessage;
extern volatile Uint16 LowPowerMode;

extern volatile Uint16 OperationalCounter;
extern volatile Uint32 HourTimer;
extern volatile Uint16 ResetIgnitionFlag;
extern volatile Uint32 IgnitionCounter;

extern volatile Uint16 HeadLightBlown;
extern volatile Uint16 HighBeamBlown;

extern volatile Uint16 Operational_State;       //as demanded by NMT
extern volatile Uint16 LowPowerMode;            //as set by PDO


#endif /* USER_GLOBALS_H_ */
