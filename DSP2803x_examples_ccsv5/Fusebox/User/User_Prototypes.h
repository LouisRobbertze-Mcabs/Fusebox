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
#include "User_CAN.h"
#include "User_ADC.h"
#include "User_Interrupts.h"

union bits32
{
    Uint32 asUint;
    float32 asFloat;
};

void Initialise_FuseBox(void);
void Init_Gpio(void);
void Toggle_LED(void);

 //Henry's Prototypes**************************************************************
void ClearErrorFlags(Uint16 Flag_Selection);
void EnableLowPower(void);
void SetFlags(void);
void ADCtoGPIO(void);
void HeadlightBulbCheck(void);


//#pragma CODE_SECTION(DELAY_US, "ramfuncs");


#endif /* USER_PROTOTYPES_H_ */