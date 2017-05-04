/*
 * User_Functions.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#include "User_Prototypes.h"

void   Init_Gpio(void)
{
    EALLOW;

    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     //BQenable
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;      //Bq enable

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;     //led2
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;      //led2

    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     //led1
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;      //led1

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     //BT reset
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;      //BT reset
    BTReset = 0;                            //keep BT in reset

    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    //12 Aux drive
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;     // 12 Aux drive (verander miskien)
    Aux_Control = 1;

    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    //KeyDrive
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     //(input) key drive (verander miskien)

    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;    //contactor output
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;     // contactor output
    ContactorOut = 0;                       //turn off contactor

    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;    //precharge resistor
    GpioCtrlRegs.GPADIR.bit.GPIO21 = 1;     // precharge resistor
    PreCharge = 1;                          //turn on precharge resistor

    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;    //key switch
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     //key switch

    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;    //BQ on
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     //BQ on (input)

    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;    //CANenable
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;     //CANenable (output)

    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;    //led3
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;     //led3

    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    //CScontrol
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;     //CSControl

    EDIS;

    //turn on contactor
    ContactorOut = 1;

    CSControl = 0;  //turn CScontrol on for current measurement
}

void I2CA_Init(void)
{
    // Initialize I2C
    I2caRegs.I2CSAR = 0x08;         // Slave address - EEPROM control code              0x08
    I2caRegs.I2CPSC.all = 6;        // Prescaler - need 7-12 Mhz on module clk          8Mhz
    I2caRegs.I2CCLKL = 40;          // NOTE: must be non zero                           40
    I2caRegs.I2CCLKH = 40;          // NOTE: must be non zero                           40  Moet 95.238kHz tot gevolg hê..
    I2caRegs.I2CIER.all = 0x24;     // Enable SCD & ARDY interrupts     0x24
    I2caRegs.I2CMDR.all = 0x0020;   // Take I2C out of reset
    I2caRegs.I2CFFTX.all = 0x6000;  // Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040;  // Enable RXFIFO, clear RXFFINT,
}



void CANTransmit(Uint16 Destination, Uint32 TxDataH, Uint32 TxDataL, Uint16 Bytes)      //destination, txdataH, txdataL,  bytes
{
    ECanaRegs.CANME.all = 0x00000006;                   // Disable Tx Mailbox

    ECanaMboxes.MBOX0.MSGCTRL.all = Bytes;              // Transmit 4 bytes of data

    ECanaMboxes.MBOX0.MSGID.all = 0;                    // Standard ID length, acceptance masks used, no remote frames
    ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = Destination; // Load destination address

    ECanaMboxes.MBOX0.MDL.all = TxDataL;
    ECanaMboxes.MBOX0.MDH.all = TxDataH;

    ECanaRegs.CANME.all = 0x00000007;                   // Enable Tx Mailbox

    ECanaRegs.CANTRS.all = 0x00000001;                  // Set transmit request
}

