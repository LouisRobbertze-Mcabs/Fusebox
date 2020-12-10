/*
 * User_Globals.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */
#include "User_Globals.h"

// Two bytes will be used for the outgoing address,
// thus only setup 2 bytes maximum
struct I2CMSG I2cMsgOut1={I2C_MSGSTAT_SEND_WITHSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_EEPROM_HIGH_ADDR,
                          I2C_EEPROM_LOW_ADDR,
                          0x00,                   // Msg Byte 1
                          0x00};                  // Msg Byte 2


struct I2CMSG I2cMsgIn1={ I2C_MSGSTAT_SEND_NOSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_EEPROM_HIGH_ADDR,
                          I2C_EEPROM_LOW_ADDR};

struct I2CMSG *CurrentMsgPtr;               // Used in interrupts

volatile Uint16 DataOut;
volatile Uint16 DataOut2;
volatile Uint16 Received;

/////////////////////////////////////////////
volatile Uint16 flagTemp=0;
volatile Uint16 flagCurrent=0;
volatile Uint16 flagVoltage=0;

volatile Uint16 flagCharged=0;
volatile Uint16 flagDischarged=0;
volatile Uint16 balance = 0;
/////////////////////////////////////////////

volatile Uint16 counter_2Hz = 0;

float current_reference;

volatile Uint16 Charger_status = 0;
volatile int system_status= 0;

volatile float toets=0;
volatile float toets2=0;
volatile float Current;
volatile int current_int;

volatile float Voltages[15];

volatile float Voltage_high=0;
volatile float Voltage_low=10;
volatile float Temperatures[16];
volatile float Temperature_avg;
volatile float Temperatures_resistance[14];
volatile float Temperature_high=0;
volatile float Temperature_low=50;

volatile float ADCgain;
volatile float ADCoffset;
volatile float I;
volatile float Voltage_total;
volatile float Ah= 0;
volatile int rus = 0;

Uint32 ref = 0;

volatile int CANcounter = 0;

volatile float test_current= 0;

volatile float test_blah[3];

int Cell_B1 = 0;
int Cell_B2 = 0;
int Cell_B3 = 0;

Uint16 NodeID = 1;
volatile Uint16 counter_50Hz = 0;

volatile float Auxilliary_Voltage = 0;
volatile Uint16 Auxilliary_counter = 0;


//defines:
volatile float Vmax = 3.65;
volatile float Vmin = 2.9;
volatile float Vcritical = 2.8;
volatile float Vcharge = 3.5;
volatile float Vbalance = 3.48;

volatile float Imin = 500;
volatile float Imax = 3800;
volatile float Ifilter = 0.27;

volatile float Tmax = 60;
volatile float Tmin = 0;

volatile float Vauxmin = 12.3;
volatile float AuxChargeTime = 1800;

volatile float Vchargedflagreset = 3.35;
volatile float Vdischargedflagreset = 2.7;

volatile float kp_constant = 3.5;								//charger
volatile float kp_multiplier = 30;								//charger
volatile float balancing_upper_level = 3.49;
volatile float balancing_bottom_level = 3.475;


volatile long Fusebox_Current = 0;
volatile long Fusebox_Temperature = 0;

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
volatile Uint16 FuseError = 0;     //SDO Location: 0x0904 ---->FUSE ERROR STATUS FLAGS
volatile Uint16 FuseErrorCount = 0;    //SDO Location: 0x090C ---->Error Counter
volatile Uint16 RelayMOSFETStatus = 0;  //SDO Location: 0x0906     Bit 0 - 4 = Relays          Bit 5 - 13 MOSFETs
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


