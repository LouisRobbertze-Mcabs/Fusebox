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

    //  float measure_C;
    static float current_p;
    //  int toets_stroom = 0;

    //test_current = AdcResult.ADCRESULT1;

    //current_ADC = current_ADC_p + (test_current - current_ADC_p)/2;

    //contactor oop:
    /*  if(ContactorOut == 0)
    {
        Current = 0;
    }
    else    //contactor toe
    {*/
    //Current = (measure_C-1820)* 0.131;                    //2035    maal, moenie deel nie!!!!     0.0982--200/2048

    //  Current = measure_C;

    test_current = current_p + (0.00314*(AdcResult.ADCRESULT1-current_p));     //   0.00314-1Hz     //  0.01249 - 4 Hz      //0.27-100Hz
    current_p=test_current;

    if(AdcResult.ADCRESULT1 > 3500 || AdcResult.ADCRESULT1 < 700)                       ////////////////////////////////////////////////
    {
        //sit uittree af
        ContactorOut = 0;       //turn off contactor
        flagCurrent = 1;
    }                                                               ////////////////////////////////////////////////

    //}
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.bit.ACK10 = 1;   // Acknowledge interrupt to PIE

    led2 = 0x01^led2;                   //toggle led
}

__interrupt void cpu_timer0_isr(void)
{
    counter_2Hz++;
    CpuTimer0.InterruptCount++;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1/* PIEACK_GROUP1*/;
}

__interrupt void cpu_timer1_isr(void)
{
    //check status of all flags as well as the key switch
    counter_50Hz++;
    static float Aux_Voltage_temp = 0;

    //Sit dit dalk deur 'n laag deurlaat filter y(k) = y(k - 1) + a[x(k) - y(k - 1)] met a = 1 - e^WcTs

	//adc/4096 *3.3* 10.51/10.51      12.2/2.2


    Auxilliary_Voltage = Aux_Voltage_temp + (0.0609*(((AdcResult.ADCRESULT2)* 0.00442)-Aux_Voltage_temp));
    Aux_Voltage_temp = Auxilliary_Voltage;


    if(KeySwitch == 1)  //keyswitch == 1
    {
        //  led3 = 1;       //turn on red led

        //binne die keydrive if
        if((flagDischarged == 0) && (flagCurrent == 0)  && (flagTemp == 0) && (Charger_status == 0))
        {

            ContactorOut = 1;           //turn on contactor
        }

    }
    else if((KeySwitch == 0) && (Charger_status == 0)) //keyswitch == 0
    {
        flagCurrent = 0;

        ContactorOut = 0;       //turn off contactor

        //  led3 = 0;       //turn off red led
    }

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
    else if(IntSource == 2)
    {
        // Generate some error due to invalid interrupt source
        __asm("   ESTOP0");
    }
    else
    {
        // Generate some error due to invalid interrupt source
        __asm("   ESTOP0");
    }
    // Enable future I2C (PIE Group 8) interrupts
    PieCtrlRegs.PIEACK.bit.ACK8 = 1;
}

__interrupt void can_rx_isr(void)
{
    if (ECanaRegs.CANRMP.all == 0x00000002)
    {
        CANSlaveReception();                        // Handle the received message
    }
    else if (ECanaRegs.CANRMP.all == 0x00000004)
    {
        CANChargerReception();
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

