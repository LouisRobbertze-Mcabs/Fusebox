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

void Init_Gpio(void);
void I2CA_Init(void);
void CANSetup(void);
void CANTransmit(Uint16 Destination, Uint32 TxDataH, Uint32 TxDataL, Uint16 Bytes);
Uint16 I2CA_WriteData(unsigned char Register, unsigned char Data);
Uint16 I2CA_ReadData(struct I2CMSG *msg, unsigned char Register, Uint16 amount);
void Shut_D_BQ(void);

// Prototype statements for functions found within this file.
void Bq76940_Init(void);
void configADC(void);
void CANMailboxConfig(void);
void CANInterruptConfig(void);
void CANSlaveReception(void);
void CANChargerReception(void);
Uint32 ChgCalculator(float Voltage, float Current);
void  Read_CellVol(void);
void Read_Temp(void);
void Balance(int period, float reference);
unsigned char CRC8(unsigned char *ptr, unsigned char len,unsigned char key);

//#pragma CODE_SECTION(DELAY_US, "ramfuncs");
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);
__interrupt void i2c_int1a_isr(void);
__interrupt void adc_isr(void);
__interrupt void spiRxFifoIsr(void);
__interrupt void can_rx_isr(void);
__interrupt void can_tx_isr(void);

#endif /* USER_PROTOTYPES_H_ */
