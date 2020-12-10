/*
 * User_Functions.c
 *
 *  Created on: 04 May 2017
 *      Author: Sonja
 */

#include "User_Defines.h"

void Initialise_BMS(void)
{
    //flagCurrent = 0;

    InitSysCtrl();
//    InitI2CGpio();
    Init_Gpio();
    InitAdc();
    //	InitSpiaGpio();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.I2CINT1A = &i2c_int1a_isr;
    PieVectTable.TINT0 = &cpu_timer0_isr;
    PieVectTable.TINT1 = &cpu_timer1_isr;
    PieVectTable.TINT2 = &cpu_timer2_isr;
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

//    I2CA_Init();
    InitCpuTimers();

    ConfigCpuTimer(&CpuTimer0, 60, 500000); //2 hz
    ConfigCpuTimer(&CpuTimer1, 60, 20000);  //50 hz
    ConfigCpuTimer(&CpuTimer2, 60, 500);    //2 Khz         //500

    CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
    CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
    CpuTimer2Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

    // Enable ADC interrupt 10 in the PIE: Group 10 interrupt 1
    PieCtrlRegs.PIEIER10.bit.INTx1 = 1;
    IER |= M_INT10;

    // Enable CPU interrupt 1 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;          //clock
    IER |= M_INT1;
    IER |= M_INT13;
    IER |= M_INT14;

    // Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    // Enable I2C INT8 which is connected to PIE group 8
    IER |= M_INT8;

    EnableInterrupts();

    EINT;
    ERTM;   // Enable Global realtime interrupt DBGM

    CAN_Init();
    configADC();

    // Reset the watchdog counter
    ServiceDog();

    // Enable the watchdog
    EALLOW;
    SysCtrlRegs.WDCR = 0x002F;
    EDIS;

    //DisableDog();
}

void Init_Gpio(void)
{
    EALLOW;

    //GPADIR: 0 - input
    //GPADIR: 1 - output
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;     //Mfet_Ctrl_8
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;      //Mfet_Ctrl_8

    /*GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     //Mfet_Ctrl_9
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;      //Mfet_Ctrl_9
    MOSFET 9 REMOVED*/

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;     //Mfet_Ctrl_6
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;      //Mfet_Ctrl_6

    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     //Mfet_Ctrl_7
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;      //Mfet_Ctrl_7

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;     //Mfet_Ctrl_3
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;      //Mfet_Ctrl_3

    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     //Mfet_Ctrl_4
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;      //Mfet_Ctrl_4

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     //Mfet_Ctrl_2
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;      //Mfet_Ctrl_2

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     //Mfet_Out_Sense_6
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;      //Mfet_Out_Sense_6

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     //Mfet_Out_Sense_3
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;      //Mfet_Out_Sense_3

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     //Mfet_Out_Sense_6
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;      //Mfet_Out_Sense_6

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;     //Mfet_Ctrl_0
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;      //Mfet_Ctrl_0

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;     //Mfet_Ctrl_1
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;      //Mfet_Ctrl_1

    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;     //Fuse_Out_Sense_9
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;      //Fuse_Out_Sense_9

    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;     //Main_Beam_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;      //Main_Beam_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;     //Heated_Seats_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;      //Heated_Seats_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;     //Wiper_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;      //Wiper_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;     //Mfet_Out_Sense_5
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;      //Mfet_Out_Sense_5

    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;     //Mfet_Out_Sense_2
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;      //Mfet_Out_Sense_2

    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;     //Mfet_Out_Sense_0
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;      //Mfet_Out_Sense_0

    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;     //Reverse_In_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;      //Reverse_In_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;     //High_Beam_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;      //High_Beam_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;     //High_Beam_Ctrl_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;      //High_Beam_Ctrl_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;     //Horn_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;      //Horn_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;     //Flasher_R_Out_Sense
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;      //Flasher_R_Out_Sense

    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;     //Mfet_Out_Sense_4
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;      //Mfet_Out_Sense_4

    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;     //Fuse_Out_Sense_5
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;      //Fuse_Out_Sense_5

    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;     //Fuse_Out_Sense_3
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;      //Fuse_Out_Sense_3

    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 1;      //Disable pull-up
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;     //LED_Out
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;      //LED_Out

    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;     //Main_Beam_Ctrl_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;      //Main_Beam_Ctrl_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;     //Flasher_L_Out_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;      //Flasher_L_Out_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO39 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;     //Mfet_Out_Sense_8
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;      //Mfet_Out_Sense_8

    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;     //Mfet_Ctrl_5
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;      //Mfet_Ctrl_5

    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;     //Mfet_Out_Sense_7
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 0;      //Mfet_Out_Sense_7

    GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;     //Handbrake_In_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;      //Handbrake_In_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;     //Radio_Out_Sense
    GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;      //Radio_Out_Sense

    GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;      //Disable pull-up
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;     //Mfet_Out_Sense_1
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;      //Mfet_Out_Sense_1

    EDIS;
}

void Toggle_LED(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO27 = 1;
}

void  Read_Cell_Voltages(void)
{
    // Read data from EEPROM section //
    int i;
    Voltage_total = 0;
    //reset values
    //Voltage_low = 10;
    float Voltages_backup5 = Voltages[5];
    float Voltages_backup10 = Voltages[10];

    float temp_V = 0;
    float temp_Voltage_high;
    temp_Voltage_high = 0;
    float temp_Voltage_low;
    temp_Voltage_low = 10;


    for(i = 0; i<15; i++)
    {
        temp_V = I2CA_ReadData(&I2cMsgIn1,0x0C+(i*0x02), 2);
        temp_V = (ADCgain * temp_V) + ADCoffset;

        if((i == 5) && ((Cell_B1 & 0x10)>>4 == 1))
            Voltages[i] = Voltages_backup5;
        else if(i == 5)
            Voltages[i] = temp_V;

        if((i == 10) && ((Cell_B2&0x10)>>4 == 1))
            Voltages[i] = Voltages_backup10;
        else if (i==10)
            Voltages[i] = temp_V;

        if(i != 5 && i != 10)
            Voltages[i] = temp_V;

        Voltage_total = Voltage_total +  Voltages[i];

        if(temp_Voltage_high<Voltages[i])
            temp_Voltage_high = Voltages[i];

        if(temp_Voltage_low>Voltages[i])
            temp_Voltage_low = Voltages[i];
    }

    Voltage_high = temp_Voltage_high;
    Voltage_low = temp_Voltage_low;
}

void Process_Voltages(void)
{
    //	static int delay = 0;
    if(Voltage_high > Vmax)         //3.6
    {
        balance = 1;            //start balancing
        flagCharged = 1;        //charged flag to to stop charging
        //		ContactorOut = 0;
    }

    if(Voltage_low > Vmin && Auxilliary_Voltage < Vauxmin && Auxilliary_Voltage > 8)
    {
        Auxilliary_counter = 0;			//turn on aux supply
        //		Aux_Control = 1;
    }
    else if(Auxilliary_counter > AuxChargeTime || Auxilliary_Voltage < 8)
    {
        //		Aux_Control = 0;										//turn off aux supply
    }

    Auxilliary_counter++;


    if(Voltage_low < Vmin && Voltage_low > Vcritical && Charger_status == 0)
    {
        //		Aux_Control = 0;
        flagDischarged = 1;
        //		led3 = 1;               //turn on red led
        //		ContactorOut = 0;       //turn off contactor            //turn off output
    }
    else if(Voltage_low < Vcritical && Charger_status == 0)
    {
        //		Aux_Control = 0;
        flagDischarged = 2;
        //		led3 = 1;               //turn on red led
    }

    if(Voltage_high<Vchargedflagreset )
        flagCharged = 0;

    if(Voltage_low>Vdischargedflagreset )
    {
        flagDischarged = 0;
        //		led3 = 0;               //turn off red led
    }

}

void Calculate_Current(void)
{
    Current = (test_current-2090)* 0.122;                   //2035    maal, moenie deel nie!!!!     0.0982--200/2048
}

void Read_System_Status(void)
{
    system_status = I2CA_ReadData(&I2cMsgIn1,0x00, 1);

}

void Process_System_Status(void)
{
    if(system_status != 00)
    {
        I2CA_WriteData(0x00, 0x3F);
    }
}

void Read_Temperatures(void)
{
    int i;
    int flag = 0;
    float Vts;
    float Rts;
    float temperature_avg=0;
    float temp_Temperature_high = 0;
    float temp_Temperature_low = 71;

    float temp_T = 0;

    //cells 0-3
    for(i = 0; i<4; i++)
    {
        Vts = (Temperatures_resistance[i]) * 0.00080566;
        Rts = (33000/Vts) - 10000;
        Temperatures[i] = (1/((log(Rts/10000))/4000+0.003356))-273;
    }

    //cell5,cell10
    temp_T = I2CA_ReadData(&I2cMsgIn1, 0x2E, 2);
    Vts = temp_T*ADCgain;
    Rts = (10000*Vts)/(3.3-Vts);
    Temperatures[4] = (1/((log(Rts/10000))/4000+0.003356))-273;

    temp_T = I2CA_ReadData(&I2cMsgIn1, 0x30, 2);
    Vts = temp_T*ADCgain;
    Rts = (10000*Vts)/(3.3-Vts);
    Temperatures[9] = (1/((log(Rts/10000))/4000+0.003356))-273;


    if(flag == 1)
        flagTemp = 1;
    else if(flag == 0)
        flagTemp = 0;
}

void Balance(int period, float reference)
{
    static float count = 0;
    float Cell_B_Voltage = reference;
    int i;

    if(balance == 1)
    {
        if(count ==0)       // 4 siklusse met onewe selle
        {
            //reset all balancing
            I2CA_WriteData(0x01,0x00);
            I2CA_WriteData(0x02,0x00);
            I2CA_WriteData(0x03,0x00);
            Cell_B1 = 0;
            Cell_B2 = 0;
            Cell_B3 = 0;

            //setup balancing
            for(i = 0; i<5; i+=2)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {
                    Cell_B1 = (Cell_B1 | (0x01 << i));
                }
            }

            for(i = 5; i<10; i+=2)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {

                    Cell_B2 = (Cell_B2 | (0x01 << (i-5)));
                }
            }

            for(i = 10; i<15; i+=2)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {

                    Cell_B3 = (Cell_B3 | (0x01 << (i-10)));
                }
            }

            if(Cell_B1==0x0 && Cell_B2==0x0 && Cell_B3==0x0)
            {
                count = period;
            }
            else
            {
                I2CA_WriteData(0x01,Cell_B1);
                I2CA_WriteData(0x02,Cell_B2);
                I2CA_WriteData(0x03,Cell_B3);
                count++;
            }

        }
        else if(count == period) // 4 siklusse met ewe selle
        {
            //reset all balancing
            I2CA_WriteData(0x01,0x00);
            I2CA_WriteData(0x02,0x00);
            I2CA_WriteData(0x03,0x00);
            Cell_B1 = 0;
            Cell_B2 = 0;
            Cell_B3 = 0;

            //setup balancing
            for(i = 1; i<5; i+=2)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {
                    Cell_B1 = (Cell_B1 | (0x01 << i));
                }
            }

            for(i = 6; i<10; i+=2)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {

                    Cell_B2 = (Cell_B2 | (0x01 << (i-5)));
                }
            }

            for(i = 11; i<15; i+=2)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {

                    Cell_B3 = (Cell_B3 | (0x01 << (i-10)));
                }
            }

            if(Cell_B1==0x0 && Cell_B2==0x0 && Cell_B3==0x0)
            {
                count = period*2;
            }
            else
            {
                I2CA_WriteData(0x01,Cell_B1);
                I2CA_WriteData(0x02,Cell_B2);
                I2CA_WriteData(0x03,Cell_B3);
                count++;
            }
        }
        else if(count == period*2)
        {
            //speel maar so bietjie
            balance = 0;

            for(i = 0; i<15; i++)
            {
                if(Voltages[i] > Cell_B_Voltage)
                {
                    balance++;
                }
            }

            if(balance !=0)
            {
                balance = 1;
            }
            else if(balance ==0)                //sit miskien else hier             hierdie is toets fase
            {
                balance = 0;
            }

            count = 0;
            I2CA_WriteData(0x01,0x00);
            I2CA_WriteData(0x02,0x00);
            I2CA_WriteData(0x03,0x00);
            Cell_B1 = 0;
            Cell_B2 = 0;
            Cell_B3 = 0;
        }
        else
        {
            count++;
        }
    }
    else
    {
        I2CA_WriteData(0x01,0x00);
        I2CA_WriteData(0x02,0x00);
        I2CA_WriteData(0x03,0x00);
        Cell_B1 = 0;
        Cell_B2 = 0;
        Cell_B3 = 0;
    }
}

unsigned char CRC8(unsigned char *ptr, unsigned char len,unsigned char key)
{
    unsigned char i;
    unsigned char crc=0;
    while(len--!=0)
    {
        for(i=0x80; i!=0; i/=2)
        {
            if((crc & 0x80) != 0)
            {
                crc *= 2;
                crc ^= key;
            }
            else
                crc *= 2;

            if((*ptr & i)!=0)
                crc ^= key;
        }
        ptr++;
    }
    return(crc);
}

Uint32 ChgCalculator(float Voltage, float Current)
{
    Uint32 answer= 0;
    Uint16 temp1 = 0;

    Voltage = Voltage*10;
    Current = Current*10;

    temp1 = (Uint16)Current;

    answer = answer | (temp1&0xFF);
    answer = (answer<<8) | (temp1>>8);

    temp1 = (Uint16)Voltage;

    answer = answer<<8 | (temp1&0xFF);
    answer = (answer<<8) | (temp1>>8);

    return answer;
}



