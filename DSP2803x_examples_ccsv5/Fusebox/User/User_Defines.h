/*
 * User_Defines.h
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#ifndef USER_DEFINES_H_
#define USER_DEFINES_H_

#include "User_Prototypes.h"

// Local definitions
#define I2C_SLAVE_ADDR        0x08
#define I2C_NUMBYTES          3                 //ekstra 1 vir crc byte
#define I2C_EEPROM_HIGH_ADDR  0x09
#define I2C_EEPROM_LOW_ADDR   0x91


#define Mfet_Ctrl_8 GpioDataRegs.GPADAT.bit.GPIO0
#define Mfet_Ctrl_9 GpioDataRegs.GPADAT.bit.GPIO1
#define Mfet_Ctrl_6 GpioDataRegs.GPADAT.bit.GPIO2
#define Mfet_Ctrl_7 GpioDataRegs.GPADAT.bit.GPIO3
#define Mfet_Ctrl_3 GpioDataRegs.GPADAT.bit.GPIO4
#define Mfet_Ctrl_4 GpioDataRegs.GPADAT.bit.GPIO5
#define Mfet_Ctrl_2 GpioDataRegs.GPADAT.bit.GPIO6

#define Mfet_Sense_6 GpioDataRegs.GPADAT.bit.GPIO7                //MCU_input
#define Mfet_Sense_3 GpioDataRegs.GPADAT.bit.GPIO8                //MCU_input
#define Fuse_Sense_6 GpioDataRegs.GPADAT.bit.GPIO9                //MCU_input

#define Mfet_Ctrl_0 GpioDataRegs.GPADAT.bit.GPIO10
#define Mfet_Ctrl_1 GpioDataRegs.GPADAT.bit.GPIO11

#define Fuse_Sense_9 GpioDataRegs.GPADAT.bit.GPIO12               //MCU_input
#define Main_Beam_Out_Sense GpioDataRegs.GPADAT.bit.GPIO13        //MCU_input     -   Relay1 out
#define Heated_Seats_Sense GpioDataRegs.GPADAT.bit.GPIO14         //MCU_input     -   Relay3 out
#define Wiper_Sense GpioDataRegs.GPADAT.bit.GPIO15                //MCU_input     -   Fuse3 out

#define Mfet_Sense_5 GpioDataRegs.GPADAT.bit.GPIO16               //MCU_input
#define Mfet_Sense_2 GpioDataRegs.GPADAT.bit.GPIO17               //MCU_input
#define Mfet_Sense_0 GpioDataRegs.GPADAT.bit.GPIO18               //MCU_input

#define Reverse_Sense GpioDataRegs.GPADAT.bit.GPIO19              //MCU_input
#define High_Beam_Out_Sense GpioDataRegs.GPADAT.bit.GPIO20        //MCU_input
#define High_Beam_Ctrl_Sense GpioDataRegs.GPADAT.bit.GPIO21       //MCU_input
#define Horn_Out_Sense GpioDataRegs.GPADAT.bit.GPIO22       //MCU_input
#define Flasher_R_Out_Sense GpioDataRegs.GPADAT.bit.GPIO23       //MCU_input


#define BQEnable GpioDataRegs.GPADAT.bit.GPIO3
#define led2 GpioDataRegs.GPADAT.bit.GPIO4
#define led1 GpioDataRegs.GPADAT.bit.GPIO5
#define BTReset GpioDataRegs.GPADAT.bit.GPIO6
#define Aux_Control GpioDataRegs.GPADAT.bit.GPIO15
#define KeyDrive GpioDataRegs.GPADAT.bit.GPIO19
#define ContactorOut GpioDataRegs.GPADAT.bit.GPIO20
#define Fan_Control GpioDataRegs.GPADAT.bit.GPIO19
#define PreCharge GpioDataRegs.GPADAT.bit.GPIO21
#define KeySwitch GpioDataRegs.GPADAT.bit.GPIO24
#define BQOn GpioDataRegs.GPADAT.bit.GPIO26
#define CANEnable GpioDataRegs.GPADAT.bit.GPIO27
#define led3 GpioDataRegs.GPBDAT.bit.GPIO40
#define CSControl GpioDataRegs.GPBDAT.bit.GPIO44

#endif /* USER_DEFINES_H_ */
