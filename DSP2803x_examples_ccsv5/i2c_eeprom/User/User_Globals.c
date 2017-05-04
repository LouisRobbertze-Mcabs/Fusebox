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
volatile float Temperatures[3];

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
