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

extern volatile Uint16 counter_2Hz;

extern float Ireference;

extern volatile Uint16 Charger_status;
extern volatile int system_status;

extern volatile float toets;
extern volatile float toets2;
extern volatile float Current;
extern volatile int current_int;

extern volatile float Voltages[15];

extern volatile float Voltage_high;
extern volatile float Voltage_low;
extern volatile float Temperatures[16];
extern volatile float Temperature_avg;
extern volatile float Temperatures_resistance[14];
extern volatile float Temperature_high;
extern volatile float Temperature_low;

extern volatile float ADCgain;
extern volatile float ADCoffset;
extern volatile float I;
extern volatile float Voltage_total;
extern volatile float Ah;
extern volatile int rus;

extern Uint32 ref;

extern volatile int CANcounter;

extern volatile float test_current;

extern volatile float test_blah[3];

extern int Cell_B1;
extern int Cell_B2;
extern int Cell_B3;

extern Uint16 NodeID;
extern volatile Uint16 counter_50Hz;

extern volatile float Auxilliary_Voltage;
extern volatile Uint16 Auxilliary_counter;


//defines:
extern volatile float Vmax;
extern volatile float Vmin;
extern volatile float Vcritical;
extern volatile float Vcharge;
extern volatile float Vbalance;

extern volatile float Imin;
extern volatile float Imax;
extern volatile float Ifilter;

extern volatile float Tmax;
extern volatile float Tmin;

extern volatile float Vauxmin;
extern volatile float AuxChargeTime;

extern volatile float Vchargedflagreset;
extern volatile float Vdischargedflagreset;

extern volatile float kp_constant;
extern volatile float kp_multiplier;
extern volatile float balancing_upper_level;
extern volatile float balancing_bottom_level;

extern volatile long Fusebox_Current;
extern volatile long Fusebox_Temperature;



//extern volatile StateFlag;  //0=Stopped State   1=pre-operational State    2=operational state



#endif /* USER_GLOBALS_H_ */
