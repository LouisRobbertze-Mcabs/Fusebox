/*
 * User_Interrupts.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#include "User_Interrupts.h"

__interrupt void  adc_isr(void)
{
	//gee aandag hieraan. doen 'n stroom meting conversion teen 1 Hz soos spanning
	//Sit dit dalk deur 'n laag deurlaat filter y(k) = y(k - 1) + a[x(k) - y(k - 1)] met a = 1 - e^WcTs

	static float Filter_100HZ;
	static float Filter_100HZ_past = 0;
	static float current_p;
	//  int toets_stroom = 0;


	//test_current = current_p + (0.00314*(AdcResult.ADCRESULT1-current_p));     //   0.00314-1Hz     //  0.01249 - 4 Hz      //0.27-100Hz
	current_p=test_current;


	//Filter_100HZ = Filter_100HZ_past + (Ifilter*(AdcResult.ADCRESULT1-Filter_100HZ_past));     //   0.00314-1Hz     //  0.01249 - 4 Hz      //0.27-100Hz
	Filter_100HZ_past=Filter_100HZ;

	//   Filter_100HZ = (test_current-2109)* 0.122;

	if(Filter_100HZ > Imax || Filter_100HZ < Imin)                       ////////////////////////////////////////////////
	{
		//sit uittree af
//		ContactorOut = 0;       //turn off contactor
		//flagCurrent = 1;
	}                                                               					////////////////////////////////////////////////

	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
	PieCtrlRegs.PIEACK.bit.ACK10 = 1;   // Acknowledge interrupt to PIE

//	led2 = 0x01^led2;                   //toggle led
}

__interrupt void cpu_timer0_isr(void)
{
	static float Temp_Values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float Fuse_4_Signal;
    float Fuse_1_Signal;
	float Forward_Signal;
	float Brake_Signal;
	float Key_Sense_Signal;
	float Horn_Signal;
	float E_stop_Signal;
	float Position_Signal;

	float Relay_3_Signal;
	float Relay_4_Signal;

	float V_Reg_Signal;
	float Fuse_7_Signal;
	float Fuse_2_Signal;
	float Fuse_8_Signal;

	counter_2Hz++;

    //Fuse box Current
    //channel A0 - SOC0
	Fusebox_Current = Temp_Values[0] + (0.466*(((AdcResult.ADCRESULT0))-Temp_Values[0]));                         //add in proper gain
	Temp_Values[0] = Fusebox_Current;

    //Fuse_Out_1
    //channel B2 - SOC1
    Fuse_1_Signal = Temp_Values[1] + (0.466*(((AdcResult.ADCRESULT1))-Temp_Values[1]));                           //add in proper gain
    Temp_Values[1] = Fuse_1_Signal;
    //add if to give binary output

    //Fuse_Out_4
    //channel B4  - SOC2
	Fuse_4_Signal = Temp_Values[2] + (0.466*(((AdcResult.ADCRESULT2))-Temp_Values[2]));                           //add in proper gain
    Temp_Values[2] = Fuse_4_Signal;
    //add if to give binary output

    //Fuse box Temperature
    //channel A1 - SOC3
	Fusebox_Temperature = Temp_Values[3] + (0.466*(((AdcResult.ADCRESULT3))-Temp_Values[3]));                     //add in proper gain
    Temp_Values[3] = Fusebox_Temperature;

    //Forward input
    //channel A2 - SOC4
    Forward_Signal = Temp_Values[4] + (0.466*(((AdcResult.ADCRESULT4))-Temp_Values[4]));                           //add in proper gain
    Temp_Values[4] = Forward_Signal;

    //Brake light output
    //channel A3 - SOC5
    Brake_Signal = Temp_Values[5] + (0.466*(((AdcResult.ADCRESULT5))-Temp_Values[5]));                           //add in proper gain
    Temp_Values[5] = Brake_Signal;


    //Key switch input
    //channel A4 - SOC6
    Key_Sense_Signal = Temp_Values[6] + (0.466*(((AdcResult.ADCRESULT6))-Temp_Values[6]));                           //add in proper gain
    Temp_Values[6] = Key_Sense_Signal;

    //Horn output
    //channel A5 - SOC7
    Horn_Signal = Temp_Values[7] + (0.466*(((AdcResult.ADCRESULT7))-Temp_Values[7]));                           //add in proper gain
    Temp_Values[7] = Horn_Signal;

    //E-stop
    //channel A6 - SOC8
    E_stop_Signal = Temp_Values[8] + (0.466*(((AdcResult.ADCRESULT8))-Temp_Values[8]));                           //add in proper gain
    Temp_Values[8] = E_stop_Signal;

    //Position Switch
    //channel A7 - SOC9
    Position_Signal = Temp_Values[9] + (0.466*(((AdcResult.ADCRESULT9))-Temp_Values[9]));                           //add in proper gain
    Temp_Values[9] = Position_Signal;

    //Relay 3                           -- needs to swop with relay 3 output (Heated seats)
    //channel B0 - SOC10
    Relay_3_Signal = Temp_Values[10] + (0.466*(((AdcResult.ADCRESULT10))-Temp_Values[10]));                           //add in proper gain
    Temp_Values[10] = Relay_3_Signal;

    //Relay 4                            -- needs to swop with relay 4 output (Radio out)
    //channel B1 - SOC11
    Relay_4_Signal = Temp_Values[11] + (0.466*(((AdcResult.ADCRESULT11))-Temp_Values[11]));                           //add in proper gain
    Temp_Values[11] = Relay_4_Signal;

    //12V Regulator - secondary
    //channel B3- SOC12
    V_Reg_Signal = Temp_Values[12] + (0.466*(((AdcResult.ADCRESULT12))-Temp_Values[12]));                           //add in proper gain
    Temp_Values[12] = V_Reg_Signal;

    //Fuse_Out_7
    //channel B5 - SOC13
    Fuse_7_Signal = Temp_Values[13] + (0.466*(((AdcResult.ADCRESULT13))-Temp_Values[13]));                           //add in proper gain
    Temp_Values[13] = Fuse_7_Signal;

    //Fuse_Out_2
    //channel B6 - SOC14
    Fuse_2_Signal = Temp_Values[14] + (0.466*(((AdcResult.ADCRESULT14))-Temp_Values[14]));                           //add in proper gain
    Temp_Values[14] = Fuse_2_Signal;

    //Fuse_Out_8
    //channel B7 - SOC15
    Fuse_8_Signal = Temp_Values[15] + (0.466*(((AdcResult.ADCRESULT15))-Temp_Values[15]));                           //add in proper gain
    Temp_Values[15] = Fuse_8_Signal;


	CpuTimer0.InterruptCount++;
	PieCtrlRegs.PIEACK.bit.ACK1 = 1/* PIEACK_GROUP1*/;
}

__interrupt void cpu_timer1_isr(void)
{
	//check status of all flags as well as the key switch
	counter_50Hz++;
	static float Aux_Voltage_temp = 0;

	//Deurlaat filter y(k) = y(k - 1) + a[x(k) - y(k - 1)] met a = 1 - e^WcTs

	//adc/4096 *3.3* 10.51/10.51      12.2/2.2


	//Auxilliary_Voltage = Aux_Voltage_temp + (0.0609*(((AdcResult.ADCRESULT2)* 0.00442)-Aux_Voltage_temp));					//maak miskien gebruik van die config leer
	//Aux_Voltage_temp = Auxilliary_Voltage;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// testing

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CpuTimer1.InterruptCount++;
	EDIS;
}

__interrupt void cpu_timer2_isr(void)
{
	EALLOW;

	CpuTimer2.InterruptCount++;
	EDIS;
}

__interrupt void i2c_int1a_isr(void)     // I2C-A
{
	Uint16 IntSource;

	// Read interrupt source
	IntSource = I2caRegs.I2CISRC.all;

	// Interrupt source = stop condition detected
	if(IntSource == I2C_SCD_ISRC)
	{
		// If completed message was writing data, reset msg to inactive state
		if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY)
		{
			CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
			//I2cMsgIn1.MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;
		}
		else
		{
			// If a message receives a NACK during the address setup portion of the
			// EEPROM read, the code further below included in the register access ready
			// interrupt source code will generate a stop condition. After the stop
			// condition is received (here), set the message status to try again.
			// User may want to limit the number of retries before generating an error.
			if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
			{
				CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART;
			}
			// If completed message was reading EEPROM data, reset msg to inactive state
			// and read data from FIFO.
			else if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY)
			{
				CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;

				DataOut = I2caRegs.I2CDRR;
				DataOut2 = I2caRegs.I2CDRR;
			}
		}
	}  // end of stop condition detected
	else if(IntSource == 2)												//no acknowledge condition
	{
		// Generate some error due to invalid interrupt source
		CurrentMsgPtr->MsgStatus = 0xFF;
	}
	else
	{
		// Generate some error due to invalid interrupt source
		//__asm("   ESTOP0");
		CurrentMsgPtr->MsgStatus = 0xFF;
	}
	// Enable future I2C (PIE Group 8) interrupts
	PieCtrlRegs.PIEACK.bit.ACK8 = 1;
}

__interrupt void can_rx_isr(void)
{
	if (ECanaRegs.CANRMP.bit.RMP1 == 1)
	{
		CANSlaveReception();                        // Handle the received message
	}
	else if (ECanaRegs.CANRMP.bit.RMP2 == 1)
	{
		CANChargerReception();
	}
	else if(ECanaRegs.CANRMP.bit.RMP3 == 1)
	{
		CANSlaveConfig();
	}

	ECanaRegs.CANRMP.all = 0xFFFFFFFF;          // Reset receive mailbox flags
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;         // Acknowledge this interrupt to receive more interrupts from group 9
}

__interrupt void can_tx_isr(void)
{
	/*if (ECanaRegs.CANTA.all == 0x00000001)
    {
        ECanaRegs.CANTA.all = 0xFFFFFFFF;           // Reset tranmission flags
    }*/


	ECanaRegs.CANTA.all = 0xFFFFFFFF;           // Reset tranmission flags
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;         // Acknowledge this interrupt to receive more interrupts from group 9
}

