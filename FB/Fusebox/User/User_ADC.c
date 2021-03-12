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


    //Fusebox Current
    //channel A0 - SOC0
    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 0x00;
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 20;


    //Fuse_Out_1
    //channel B2 - SOC1
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 0x0A;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 20;


    //Fuse_Out_4
    //channel B4  - SOC2
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 0x0C;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 20;


    //Fuse box Temperature
    //channel A1 - SOC3
    AdcRegs.ADCSOC3CTL.bit.CHSEL    = 0x01;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC3CTL.bit.ACQPS    = 20;

    //Forward input
    //channel A2 - SOC4
    AdcRegs.ADCSOC4CTL.bit.CHSEL    = 0x02;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC4CTL.bit.ACQPS    = 20;

    //Brake light output
    //channel A3 - SOC5
    AdcRegs.ADCSOC5CTL.bit.CHSEL    = 0x03;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC5CTL.bit.ACQPS    = 20;

    //Key switch input
    //channel A4 - SOC6
    AdcRegs.ADCSOC6CTL.bit.CHSEL    = 0x04;
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC6CTL.bit.ACQPS    = 20;

    //Horn output
    //channel A5 - SOC7
    AdcRegs.ADCSOC7CTL.bit.CHSEL    = 0x05;
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC7CTL.bit.ACQPS    = 20;

    //E-stop
    //channel A6 - SOC8
    AdcRegs.ADCSOC8CTL.bit.CHSEL    = 0x06;
    AdcRegs.ADCSOC8CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC8CTL.bit.ACQPS    = 20;

    //Position Switch
    //channel A7 - SOC9
    AdcRegs.ADCSOC9CTL.bit.CHSEL    = 0x07;
    AdcRegs.ADCSOC9CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC9CTL.bit.ACQPS    = 20;

    //Relay 3                           -- needs to swop with relay 3 output (Heated seats)
    //channel B0 - SOC10
    AdcRegs.ADCSOC10CTL.bit.CHSEL    = 0x08;
    AdcRegs.ADCSOC10CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC10CTL.bit.ACQPS    = 20;

    //Relay 4                            -- needs to swop with relay 4 output (Radio out)
    //channel B1 - SOC11
    AdcRegs.ADCSOC11CTL.bit.CHSEL    = 0x09;
    AdcRegs.ADCSOC11CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC11CTL.bit.ACQPS    = 20;

    //12V Regulator - secondary
    //channel B3- SOC12
    AdcRegs.ADCSOC12CTL.bit.CHSEL    = 0x0B;
    AdcRegs.ADCSOC12CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC12CTL.bit.ACQPS    = 20;

    //Fuse_Out_7
    //channel B5 - SOC13
    AdcRegs.ADCSOC13CTL.bit.CHSEL    = 0x0D;
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC13CTL.bit.ACQPS    = 20;

    //Fuse_Out_2
    //channel B6 - SOC14
    AdcRegs.ADCSOC14CTL.bit.CHSEL    = 0x0E;
    AdcRegs.ADCSOC14CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC14CTL.bit.ACQPS    = 20;

    //Fuse_Out_8
    //channel B7 - SOC15
    AdcRegs.ADCSOC15CTL.bit.CHSEL    = 0x0F;
    AdcRegs.ADCSOC15CTL.bit.TRIGSEL  = 0x02;
    AdcRegs.ADCSOC15CTL.bit.ACQPS    = 20;

    EDIS;
}

