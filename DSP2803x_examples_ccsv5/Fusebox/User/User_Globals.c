/*
 * User_Globals.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */
#include "User_Globals.h"
/////////////////////////////////////////////
volatile int CANcounter = 0;
volatile long Fusebox_Current = 0;
volatile long Fusebox_Temperature = 0;
volatile Uint16 counter_2Hz;

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


volatile Uint16 FuseError = 0;     //SDO Location: 0x0904 ---->FUSE ERROR STATUS FLAGS
volatile Uint16 FuseErrorCount = 0;    //SDO Location: 0x090C ---->Error Counter
volatile Uint16 RelayMOSFETStatus = 0;  //SDO Location: 0x0906     Bit 0 - 4 = Relays      Bit 5 - 13 MOSFETs
volatile Uint16 RelayMOSFETError = 0;            //SDO Location: 0x0908
volatile Uint16 RelayMOSFETErrorCounter = 0;     //SDO Location: 0x090C
volatile Uint16 VehicleStatus = 0;    //SDO Location: 0x090A
volatile Uint16 ErrorCounter = 0;
volatile Uint16 OperationalCounter = 0;
volatile Uint32 HourTimer = 0;
volatile Uint16 ResetIgnitionFlag = 0;
volatile Uint32 IgnitionCounter = 0;

volatile float Current_Prev = 0;
volatile Uint16 HeadLightBlown = 0;
volatile Uint16 HighBeamBlown = 0;
volatile Uint16 counter1 = 0;        //timeout counter for head light to switch on after command is received
volatile Uint16 counter2 = 0;        //timeout counter for high beam to switch on after command is received
volatile Uint16 HeadSwitched = 0;
volatile Uint16 HighSwitched = 0;
volatile Uint16 CheckAgain1 = 1;
volatile Uint16 CheckAgain2 = 1;

volatile Uint16 Operational_State = 0;     //as demanded by NMT
volatile Uint16 LowPowerMode = 0;          //as set by master PDO message


