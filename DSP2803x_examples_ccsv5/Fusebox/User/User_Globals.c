/*
 * User_Globals.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */
#include "User_Globals.h"
/////////////////////////////////////////////
volatile Uint16 counter_2Hz = 0;

volatile Uint16 Fuse_Out_Sense_1 = 0;
volatile Uint16 Fuse_Out_Sense_4 = 0;
volatile Uint16 Forward_In_Sense = 0;
volatile Uint16 Brake_In_Sense = 0;
volatile Uint16 Key_In_Sense = 0;
volatile Uint16 Horn_Ctrl_Sense = 0;                            //relay input
volatile Uint16 E_Stop_In_Sense = 0;                            //define logic
volatile Uint16 Position_Out_Sense = 0;
volatile Uint16 Heated_Seats_Out_Sense = 0;                     //Relay 3 needs swopping
volatile Uint16 Radio_Out_Sense = 0;                            //Relay 4 needs swopping
volatile Uint16 V_Reg_In_Sense = 0;                             //secondary regulator
volatile Uint16 Fuse_Out_Sense_7 = 0;
volatile Uint16 Fuse_Out_Sense_2 = 0;
volatile Uint16 Fuse_Out_Sense_8 = 0;

//Henry's Globals   ************************************************************************************************
MasterVariableTable SdoMessage;

volatile Uint16 OperationalCounter = 0;
volatile Uint32 HourTimer = 0;
volatile Uint16 ResetIgnitionFlag = 0;
volatile Uint32 IgnitionCounter = 0;

volatile Uint16 HeadLightBlown = 0;
volatile Uint16 HighBeamBlown = 0;

volatile Uint16 Operational_State = 0;     //as demanded by NMT
volatile Uint16 LowPowerMode = 0;          //as set by master NMT message
volatile Uint32 ErrorCounter = 0;
Uint16 CAN_Initialised = 0;




