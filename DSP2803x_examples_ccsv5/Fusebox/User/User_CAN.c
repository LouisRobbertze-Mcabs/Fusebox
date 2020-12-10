/*
 * User_CAN.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */
//******************FUSEBOX

#include "User_CAN.h"

void CAN_Init(void)
{
	CANSetup();
	CANMailboxConfig();
	CANInterruptConfig();
}

void CANSetup(void)
{
	EALLOW;

	// Configure CAN GPIO pins
	GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;             // Enable pull-up for GPIO30 (CANRXA)
	GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;             // Enable pull-up for GPIO31 (CANTXA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3;           // Asynch qual for GPIO30 (CANRXA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;            // Configure GPIO30 for CANRXA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;            // Configure GPIO31 for CANTXA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;            // Set the enable signal to the CAN transciever as GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;             // Set the enable signal to the CAN transciever as output
	GpioDataRegs.GPADAT.bit.GPIO27 = 1;             // Set the enable signal to the CAN transciever high

	// Configure eCAN RX and TX pins
	struct ECAN_REGS ECanaShadow;
	ECanaShadow.CANTIOC.all = ECanaRegs.CANTIOC.all;
	ECanaShadow.CANTIOC.bit.TXFUNC = 1;
	ECanaRegs.CANTIOC.all = ECanaShadow.CANTIOC.all;
	ECanaShadow.CANRIOC.all = ECanaRegs.CANRIOC.all;
	ECanaShadow.CANRIOC.bit.RXFUNC = 1;
	ECanaRegs.CANRIOC.all = ECanaShadow.CANRIOC.all;

	// Configure Master Control register
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.SCB = 0;                  //  Martin Rademeyer //
	ECanaShadow.CANMC.bit.DBO = 1;                  //  Martin Rademeyer //     1 bartho
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	// Initialise Message Control registers
	ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX4.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX5.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX6.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX7.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX8.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX9.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX10.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX11.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX12.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX13.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX14.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX15.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX16.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX17.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX18.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX19.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX20.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX21.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX22.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX23.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX24.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX25.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX26.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX27.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX28.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX29.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX30.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX31.MSGCTRL.all = 0x00000000;

	// Clear flag registers
	ECanaRegs.CANTA.all = 0xFFFFFFFF;
	ECanaRegs.CANRMP.all = 0xFFFFFFFF;
	ECanaRegs.CANGIF0.all = 0xFFFFFFFF;
	ECanaRegs.CANGIF1.all = 0xFFFFFFFF;

	// Configure bit-timing
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.CCR = 1 ;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	do {ECanaShadow.CANES.all = ECanaRegs.CANES.all;}   // Wait until the CPU has been granted permission to change the configuration registers
	while (ECanaShadow.CANES.bit.CCE != 1 );            // Wait for CCE bit to be set..
	ECanaShadow.CANBTC.all = 0;
	ECanaShadow.CANBTC.bit.BRPREG = 3;
	//  ECanaShadow.CANBTC.bit.BRPREG = 15;                 //  Martin Rademeyer //
	//  ECanaShadow.CANBTC.bit.BRPREG = 1;                  //  Martin Rademeyer //
	ECanaShadow.CANBTC.bit.TSEG2REG = 2;                //  Martin Rademeyer //
	ECanaShadow.CANBTC.bit.TSEG1REG = 10;               //  Martin Rademeyer //
	ECanaShadow.CANBTC.bit.SAM = 0;                     //1
	ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;

	// Finalise CAN configuration
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.CCR = 0 ;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	do {ECanaShadow.CANES.all = ECanaRegs.CANES.all;}   // Wait until the CPU no longer has permission to change the configuration registers
	while(ECanaShadow.CANES.bit.CCE != 0 );             // Wait for CCE bit to be  cleared..
	ECanaRegs.CANME.all = 0;                            // Disable all Mailboxes - Required before writing the MSGIDs

	EDIS;
}

void CANMailboxConfig(void)
{
	ECanaRegs.CANGAM.all = 0x00000000;              // Global All-Pass Mask (Don't care: 1, Match: 0)

	ECanaRegs.CANMD.all = 0x0000000E;               // Message Direction (Rx: 1, Tx: 0)                                 //bartho    0x00000006

	// Tx Mailbox (0x00000001)
	ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000004; // Transmit 4 bytes of data

	// Rx Mailbox (0x00000002)
	ECanaMboxes.MBOX1.MSGID.all = 0;                // Standard ID length, acceptance masks used, no remote frames
	ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = NodeID;  // Current address loaded
	ECanaLAMRegs.LAM1.all = 0x00000000;             // Accept standard IDs with matching address

	ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000005; // Receive 4 bytes of data

	// Rx Mailbox (0x00000003)
	ECanaMboxes.MBOX2.MSGID.all = 0;                // Standard ID length, acceptance masks used, no remote frames      //bartho
	ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = 0x0611;  // Current address loaded                                           //bartho
	ECanaLAMRegs.LAM2.all = 0x00000000;             // Accept standard IDs with matching address                        //bartho
	ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000008; // Receive 8 bytes of data                                              //bartho


	// Rx Mailbox (0x00000004)
	ECanaMboxes.MBOX3.MSGID.all = 0;                // Standard ID length, acceptance masks used, no remote frames      //bartho
	ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = 0x011;  // Current address loaded                                           //bartho
	ECanaLAMRegs.LAM3.all = 0x00000000;             // Accept standard IDs with matching address                        //bartho
	ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000005; // Receive 5 bytes of data                                              //bartho

	ECanaRegs.CANME.all = 0x0000000E;               // Enable Rx Mailbox                                                //bartho    0x00000006

	// The Tx Mailbox MSGID has to be set as required and then enabled
}

void CANInterruptConfig(void)
{
	DINT;                                           // Global interrupt disable

	EALLOW;
	ECanaRegs.CANGIM.all = 0x00000003;              // Enable ECAN0INT and ECAN0INT interrupt lines
	ECanaRegs.CANMIM.all = 0x0000000F;              // Allow interrupts for Mailbox 0 and 1 , 2,3
	ECanaRegs.CANMIL.all = 0x00000001;              // Mailbox 0 triggers ECAN1INT line, Mailbox 1 triggers ECAN0INT line       //1 bartho
	PieVectTable.ECAN0INTA = &can_rx_isr;           // Link Rx ISR function
	PieVectTable.ECAN1INTA = &can_tx_isr;           // Link Tx ISR function
	EDIS;

	PieCtrlRegs.PIEIER9.bit.INTx5 = 1;              // Enable Rx interrupt in PIE group 9
	PieCtrlRegs.PIEIER9.bit.INTx6 = 1;              // Enable Tx interrupt in PIE group 9

	IER |= M_INT9;                                  // Enable group 9 interrupts

	EINT;                                           // Global interrupt enable
}

void CANChargerReception(void)
{
	Uint32 RxDataL = 0;
	Uint32 RxDataH = 0;
	float ChgVoltage = 0;
	float ChgCurrent = 0;
	Uint16 ChgStatus = 0;
	Uint16 temp = 0;
	Uint16 temp2 = 0;
	//	float error = 0;

	static volatile float Current_max = 25;
	//  float Vreference = 52;

	static volatile int delay = 0;  // miskien >> count 1 cycle from contactor closes till charger starts
	//   >> count 1 cycle from charger stops till contactor opens

	RxDataL = ECanaMboxes.MBOX2.MDL.all;                // Data taken out of direct mailbox
	RxDataH = ECanaMboxes.MBOX2.MDH.all;                // Data taken out of direct mailbox

	//Read Charger Voltage
	temp = RxDataL;
	temp2 = (temp & 0xFF) << 8;
	temp2 = ((temp &0xFF00)>>8) | temp2;
	ChgVoltage = (float)temp2*0.1;

	//Read Charger Current
	temp = (RxDataL& 0xFFFF0000)>>16;
	temp2    = (temp & 0xFF) << 8;
	temp2 = ((temp &0xFF00)>>8) | temp2;
	ChgCurrent = (float)temp2*0.1;

	//Read Charger Status
	ChgStatus = RxDataH & 0xFF;
}

void CANSlaveReception(void)
{
	/*Uint32 RxData = 0;
	union bits32 TxData;

	RxData = ECanaMboxes.MBOX1.MDH.all;             // Data taken out of direct mailbox

	switch (RxData)
	{
    case 1: {TxData.asFloat=Voltages[0]; CANTransmit(0, 1, TxData.asUint,5); break;}
    case 2: {TxData.asFloat=Voltages[1]; CANTransmit(0, 2, TxData.asUint,5); break;}
    case 3: {TxData.asFloat=Voltages[2]; CANTransmit(0, 3, TxData.asUint,5); break;}
    case 4: {TxData.asFloat=Voltages[3]; CANTransmit(0, 4, TxData.asUint,5); break;}
    case 5: {TxData.asFloat=Voltages[4]; CANTransmit(0, 5, TxData.asUint,5); break;}
    case 6: {TxData.asFloat=Voltages[5]; CANTransmit(0, 6, TxData.asUint,5); break;}
    case 7: {TxData.asFloat=Voltages[6]; CANTransmit(0, 7, TxData.asUint,5); break;}
    case 8: {TxData.asFloat=Voltages[7]; CANTransmit(0, 8, TxData.asUint,5); break;}
    case 9: {TxData.asFloat=Voltages[8]; CANTransmit(0, 9, TxData.asUint,5); break;}
    case 10: {TxData.asFloat=Voltages[9]; CANTransmit(0, 10, TxData.asUint,5); break;}
    case 11: {TxData.asFloat=Voltages[10]; CANTransmit(0, 11, TxData.asUint,5); break;}
    case 12: {TxData.asFloat=Voltages[11]; CANTransmit(0, 12, TxData.asUint,5); break;}
    case 13: {TxData.asFloat=Voltages[12]; CANTransmit(0, 13, TxData.asUint,5); break;}
    case 14: {TxData.asFloat=Voltages[13]; CANTransmit(0, 14, TxData.asUint,5); break;}
    case 15: {TxData.asFloat=Voltages[14]; CANTransmit(0, 15, TxData.asUint,5); break;}

    case 16: {TxData.asFloat=Current; CANTransmit(0, 16, TxData.asUint,5); break;}

    case 17: {TxData.asFloat=Temperatures[4]; CANTransmit(0, 17, TxData.asUint,5); break;}
    case 18: {TxData.asFloat=Temperatures[9]; CANTransmit(0, 18, TxData.asUint,5); break;}
    case 19: {TxData.asFloat=Temperature_avg; CANTransmit(0, 19, TxData.asUint, 5); break;}

    case 20: {TxData.asFloat=Auxilliary_Voltage; CANTransmit(0, 20, TxData.asUint, 5); break;}
	}*/
}

void CANSlaveConfig(void)
{
	Uint32 RxDataNumber = 0;
	float RxDataValue = 0;
	union bits32 TxData;

	RxDataNumber = ECanaMboxes.MBOX3.MDH.all;             // Data taken out of direct mailbox
	TxData.asUint = ECanaMboxes.MBOX3.MDL.all;

	switch (RxDataNumber)
	{
	case 101: {if(TxData.asFloat<3.7 && TxData.asFloat>3.55){Vmax = TxData.asFloat;}break;}					//Vmax
	case 102: {if(RxDataValue<2.8 && RxDataValue>2.55){Vmin = RxDataValue;}break;}					//
	case 103: {if(RxDataValue<2.55 && RxDataValue>2.5){Vcritical = RxDataValue;}break;}
	case 104: {if(RxDataValue<3.65 && RxDataValue>3.4){Vcharge = RxDataValue;}break;}
	case 105: {if(RxDataValue<3.7 && RxDataValue>3.4){Vbalance = RxDataValue;}break;}

	case 106: {if(RxDataValue<4000 && RxDataValue>3000){Imax = RxDataValue;}break;}
	case 107: {if(RxDataValue<1000 && RxDataValue>100){Imin = RxDataValue;}break;}
	case 108: {if(RxDataValue<0.05 && RxDataValue>0.001){Ifilter = RxDataValue;}break;}			//   0.00314-1Hz     //  0.01249

	case 109: {if(RxDataValue<70 && RxDataValue>45){Tmax = RxDataValue;}break;}
	case 110: {if(RxDataValue<5&& RxDataValue>-5){Tmin = RxDataValue;}break;}

	case 111: {if(RxDataValue<12.8 && RxDataValue>12){Vauxmin = RxDataValue;}break;}
	case 112: {if(RxDataValue<5000 && RxDataValue>600){AuxChargeTime = RxDataValue;}break;}

	case 113: {if(RxDataValue<3.5 && RxDataValue>3.2){Vchargedflagreset = RxDataValue;}break;}
	case 114: {if(RxDataValue<3 && RxDataValue>2.6){Vdischargedflagreset = RxDataValue;}break;}

	//aux filter waarde

	//stroom meting offset waarde
	//stroom meting multiplier/skaal
	}
}

void CANTransmit(Uint16 Destination, Uint32 TxDataH, Uint32 TxDataL, Uint16 Bytes, Uint16 Mailbox)      //destination, txdataH, txdataL, bytes, Mailbox
{
    switch(Mailbox)
    {
    case 0 :
        if(ECanaRegs.CANTRS.bit.TRS0 == 0)                          // Check to see if previous transmit has completed
        {
            ECanaRegs.CANME.bit.ME0 = 0;                            // Disable Tx Mailbox
            ECanaMboxes.MBOX0.MSGCTRL.all = Bytes;                  // Transmit x bytes of data
            ECanaMboxes.MBOX0.MSGID.all = 0;                        // Standard ID length, acceptance masks used, no remote frames
            ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = Destination;     // Load destination address
            ECanaMboxes.MBOX0.MDL.all = TxDataL;
            ECanaMboxes.MBOX0.MDH.all = TxDataH;

            ECanaRegs.CANME.bit.ME0 = 1;                            // Enable Tx Mailbox
            ECanaRegs.CANTRS.bit.TRS0 = 1;                          // Set transmit request
        }
        break;
    case 7 :
        if(ECanaRegs.CANTRS.bit.TRS7 == 0)                          // Check to see if previous transmit has completed
        {
            ECanaRegs.CANME.bit.ME7 = 0;                            // Disable Tx Mailbox
            ECanaMboxes.MBOX7.MSGCTRL.all = Bytes;                  // Transmit x bytes of data
            ECanaMboxes.MBOX7.MSGID.all = 0;                        // Standard ID length, acceptance masks used, no remote frames
            ECanaMboxes.MBOX7.MSGID.bit.STDMSGID = Destination;     // Load destination address
            ECanaMboxes.MBOX7.MDL.all = TxDataL;
            ECanaMboxes.MBOX7.MDH.all = TxDataH;

            ECanaRegs.CANME.bit.ME7 = 1;                            // Enable Tx Mailbox
            ECanaRegs.CANTRS.bit.TRS7 = 1;                          // Set transmit request
        }
        break;
    case 8 :
        if(ECanaRegs.CANTRS.bit.TRS8 == 0)                          // Check to see if previous transmit has completed
        {
            ECanaRegs.CANME.bit.ME8 = 0;                            // Disable Tx Mailbox
            ECanaMboxes.MBOX8.MSGCTRL.all = Bytes;                  // Transmit x bytes of data
            ECanaMboxes.MBOX8.MSGID.all = 0;                        // Standard ID length, acceptance masks used, no remote frames
            ECanaMboxes.MBOX8.MSGID.bit.STDMSGID = Destination;     // Load destination address
            ECanaMboxes.MBOX8.MDL.all = TxDataL;
            ECanaMboxes.MBOX8.MDH.all = TxDataH;

            ECanaRegs.CANME.bit.ME8 = 1;                            // Enable Tx Mailbox
            ECanaRegs.CANTRS.bit.TRS8 = 1;                          // Set transmit request
        }
        break;
    case 9 :
        if(ECanaRegs.CANTRS.bit.TRS9 == 0)                          // Check to see if previous transmit has completed
        {
            ECanaRegs.CANME.bit.ME9 = 0;                            // Disable Tx Mailbox
            ECanaMboxes.MBOX9.MSGCTRL.all = Bytes;                  // Transmit x bytes of data
            ECanaMboxes.MBOX9.MSGID.all = 0;                        // Standard ID length, acceptance masks used, no remote frames
            ECanaMboxes.MBOX9.MSGID.bit.STDMSGID = Destination;     // Load destination address
            ECanaMboxes.MBOX9.MDL.all = TxDataL;
            ECanaMboxes.MBOX9.MDH.all = TxDataH;

            ECanaRegs.CANME.bit.ME9 = 1;                            // Enable Tx Mailbox
            ECanaRegs.CANTRS.bit.TRS9 = 1;                          // Set transmit request
        }
        break;
    }

    if (ECanaRegs.CANES.all != 0 || ECanaRegs.CANES.all != 0x30000 || ECanaRegs.CANES.all != 0x30001)
    {
        ECanaRegs.CANES.all = 0xFFF0000;                            //reset flags   //reset fault on CAN bus    0x1BB0000
    }
}

