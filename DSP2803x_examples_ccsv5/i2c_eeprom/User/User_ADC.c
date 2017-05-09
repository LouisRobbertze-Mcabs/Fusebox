/*
 * User_ADC.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#include "User_ADC.h"

void configADC(void)
{
    EALLOW;
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINT1 trips after AdcResults latch
    AdcRegs.INTSEL1N2.bit.INT1E     = 1;    //Enabled ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;    //Disable ADCINT1 Continuous mode
    AdcRegs.INTSEL1N2.bit.INT1SEL   = 1;    //setup EOC1 to trigger ADCINT1 to fire
    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 0x0B; //0     set SOC0 channel select to ADCINB3(dummy sample for rev0 errata workaround)
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 0x0B; //0     set SOC1 channel select to ADCINB3
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 0x03; //  CPU Timer 0  // hierdie was 2
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 0x03; //
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 20;   //set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 20;   //set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)


    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 0x0C;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 20;
    EDIS;
}

void Reset_ADC(void)
{
    I2CA_WriteData(0x04,0x8);
    I2CA_WriteData(0x04,0x18);
}
