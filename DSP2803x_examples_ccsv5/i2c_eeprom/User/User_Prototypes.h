/*
 * User_Prototypes.h
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#ifndef USER_PROTOTYPES_H_
#define USER_PROTOTYPES_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "User_Defines.h"

union bits32
{
    Uint32 asUint;
    float32 asFloat;
};

void Initialise_BMS(void);
void Toggle_LED(void);
void Calculate_Current(void);
void Read_System_Status(void);
void Process_System_Status(void);

void Init_Gpio(void);
void I2CA_Init(void);
Uint16 I2CA_WriteData(unsigned char Register, unsigned char Data);
Uint16 I2CA_ReadData(struct I2CMSG *msg, unsigned char Register, Uint16 amount);

void Bq76940_Init(void);
void Shut_D_BQ(void);

void configADC(void);
void Reset_ADC(void);

Uint32 ChgCalculator(float Voltage, float Current);
void  Read_Cell_Voltages(void);
void Process_Voltages(void);

void Read_Temperatures(void);
void Balance(int period, float reference);
unsigned char CRC8(unsigned char *ptr, unsigned char len,unsigned char key);

//#pragma CODE_SECTION(DELAY_US, "ramfuncs");


#endif /* USER_PROTOTYPES_H_ */
