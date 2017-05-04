/*
 * User_I2C.h
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#ifndef USER_USER_I2C_H_
#define USER_USER_I2C_H_

#include "User_Defines.h"

void I2CA_Init(void);
Uint16 I2CA_WriteData(unsigned char Register, unsigned char Data);
Uint16 I2CA_ReadData(struct I2CMSG *msg, unsigned char Register, Uint16 amount);

#endif /* USER_USER_I2C_H_ */
