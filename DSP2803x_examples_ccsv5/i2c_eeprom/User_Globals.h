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

extern struct I2CMSG I2cMsgOut1;
extern struct I2CMSG I2cMsgIn1;

extern struct I2CMSG *CurrentMsgPtr;               // Used in interrupts

extern volatile Uint16 DataOut;
extern volatile Uint16 DataOut2;
extern volatile Uint16 Received;

/////////////////////////////////////////////
extern volatile Uint16 flagTemp;
extern volatile Uint16 flagCurrent;
extern volatile Uint16 flagVoltage;

extern volatile Uint16 flagCharged;
extern volatile Uint16 flagDischarged;
extern volatile Uint16 balance;
/////////////////////////////////////////////

extern volatile Uint16 count;
extern volatile Uint16 count1;

extern float Ireference;

extern volatile Uint16 Charger_status;

extern volatile float toets;
extern volatile float toets2;
extern volatile float current;
extern volatile int current_int;

extern volatile float V[15];
extern volatile float Vhigh;
extern volatile float Vlow;
extern volatile float T[3];

extern volatile float ADCgain;
extern volatile float ADCoffset;
extern volatile float I;
extern volatile float Vt;
extern volatile float Ah;
extern volatile int rus;

extern Uint32 ref;

extern volatile int CANcounter;

extern volatile float test_current;

extern volatile float test_blah[3];

extern int Cell_B1;
extern int Cell_B2;
extern int Cell_B3;

extern volatile int system_status;

extern Uint16 NodeID;
extern volatile Uint16 counter_50Hz;

#endif /* USER_GLOBALS_H_ */
