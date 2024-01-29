/*******************************************************************************
 * 
 * @Company
 *      Pentageer
 * 
 * @Designer
 *      Daniel St-Pierre
 * 
 * @Date
 *      Jan 8 2023
 * 
 * @File Name
 *      Init.c
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/
#include "Init.h"


/*******************************************************************************
 * Function: initialize_mcu
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void initialize_mcu(void)
{
    init_port();
    
    //POWER_CTL = 1; 

    //Sleep_CTL = 1;
    
    Sleep_CTL = 0; 
    while(Sleep_CTL != 0)
    {
        Sleep_CTL = 0; 
    }
        
//    Xtal_Enable = 1; 
//    while(Xtal_Enable != 1)
//    {
//        Xtal_Enable = 1; 
//    }
    
    ///////////////////////////////////////
    // Enable Clock Switching
    //_FOSC(FCKSM_CSECMD);
    
    ///////////////////////////////////////
    init_osc_External(); // 40MHz
    //init_osc_Internal(); // 40Mhz
    //init_osc_low_speed(); //
    
    //Init_DMA(); 
    init_uart_1(); 
    //init_uart_1_DMA();
    //DMA_Channel_0(); // Uart1 / DMA => RX1 to TX2
    
    init_uart_2(); 
    //init_uart_2_DMA(); 
    //DMA_Channel_1(); // Uart2 / DMA => RX2 to TX1
    
    //DMA_Channel_2(); // Cannot use 2 DMA channel  
    
    //init_uart_3(); 
    
    init_timer_1(); // Time interrupt
    
    init_timer_2(); // main loop time keeping
    
    init_timer_3(); // Timeout for buggy function
    
    init_timer_4(); // wakeup time interrupt
    
    // referece clock enable, but not output
    init_ref_clock(); 
    
    //CLC_config(); // get 2nd slow clock for timer
    
    //init_watch_dog();
    
    init_CAN_1();
    
    CAN_Enable = 1; 
    while(CAN_Enable != 1)
    {
        CAN_Enable = 1; 
    }
    
    CRC_Init(); 
    
    // SPI Master mode
    init_SPI_1();
    init_SPI_2();
    init_SPI_3();
    
    SET_ADC_ADS863x_POWER_UP(SPI_CS_VOLT); 
    
    SET_ADC_ADS863x_AUX_CONFIG(SPI_CS_VOLT);
    
    SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, 0x0B);
    
    //MUX1_ADG732_INIT(); 
    //Set_All_Chip_Select(); 
    // set all Chip select to high

    //init_I2C(); 
    
    //init_ADC_AD7993();
    
    //ADXL355_SPI_Write_Accel_Device_Register(0x2C, 0x03); // Set 8g range
    
    //ADXL355_I2C_Set_Range(ACC_ADXL355_LG2_ID, 0x03); // Set 8g range
    
    //ADXL373_SPI_Init(); 
    ADXL373_SPI_Init_Wake_Up_Mode();
    
    //init_ADC(); 
    
    //init_MAG_MMC5983MA(); 
    
    //init_ADC_MCP3422(); 
    
    MEM_MT25QL01_Init(); 
    
    //init_sleep(); 
    //Enable_Sleep_Interrupt(); 
    
    //init_Dead_Man_timer(); 
    
    init_interrupt();
    
    set_interrupt_Enable(); 
    
    
}

/*******************************************************************************
 * Function: init_interrupt
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_interrupt(void)
{
    /* Interrupt nesting enabled here */
    INTCON1bits.NSTDIS = 0;

    /* Set Timer3 interrupt priority to 6 (level 7 is highest) */
    //IPC2bits.T3IP = 6;

    /* Set Uart 1 RX interrupt priority to 4 (level 7 is highest) */
    IPC2bits.U1RXIP = 4;
    
    /* Set Uart 1 RX Error interrupt priority to 4 (level 7 is highest) */
    IPC12bits.U1EIP = 4;
    
    /* Set CCP Timer 1 interrupt priority to 7 (level 7 is highest) */
    //IPC1bits.CCP1IP = 7;
    IPC1bits.CCT1IP = 6;
    
    // SPI 2 received
    //IPC7bits.SPI2RXIP = 7; 
    
    IPC7bits.SPI2TXIP = 7; 
    /* Set Uart 1 Event Error interrupt priority to 4 (level 7 is highest) */
    //IPC47bits.U1EVTIP = 6;
    
    //IPC0bits.T1IP = 4; // Timer1 interrupt priority level = 4
    //IPC23bits.PWM1IP = 6; // PWM1 interrupt priority level = 6
    
    // External Interrupt  1 => Accel_LG1_Int
    // INTCON2bits.INT1EP = 1; 
    
    // External Interrupt  2 => Accel_HG_Int
    IPC5bits.INT2IP = 3; 
    INTCON2bits.INT2EP = 1; // Interrupt on negative edge
    IEC1bits.INT2IE = 1; // enable External Interrupt 2
    
    // External Interrupt  3 => detect 5V 
//    IPC6bits.INT3IP = 3; 
//    INTCON2bits.INT3EP = 1; // Interrupt on negative edge
//    IEC1bits.INT3IE = 1; // enable External Interrupt 2
    
    //INTCON2bits.SWTRAP = 1; // Software trap for DMT ...
    
}

/*******************************************************************************
 * Function: set_interrupt_Enable
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void set_interrupt_Enable(void)
{
    /* Enable level 1-7 interrupts */
    /* No restoring of previous CPU IPL state performed here */
    INTCON2bits.GIE = 1;
}

/*******************************************************************************
 * Function: init_port
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_port(void)
{

    /*******************************************
    // PPS selection
    *******************************************/
    __builtin_write_RPCON(0x0000); // Unlock Registers
    
    /////////////////////////////////////////////////
    // PPS input
    /////////////////////////////////////////////////
    _U1RXR = 35;    // Assign U1Rx 
    _U2RXR = 38;    // Assign U2Rx 
    _U3RXR = 61;    // Assign U3Rx
    
    _INT2R = 33;     // Accel_HG_Int  set as EXT interrupt 2   
    
    
    _SDI1R = 49;    // Assign MISO 1
    
    _SDI2R = 57;    // Assign MISO 2

    _SDI3R = 52;    // Assign MISO 3
    
    //_CAN1RXR = 47;  // Assign CAN Input - Test board
    _CAN1RXR = 46;  // Assign CAN Input - SAST
    
    /////////////////////////////////////////////////
    // PPS output
    /////////////////////////////////////////////////
    _RP36R = 1;     // Assign U1TX
    _RP37R = 3;     // Assign U2TX
    _RP60R = 27;    // Assign U3TX
    
    
    _RP48R = 6;   // SPI - SCK1
    _RP50R = 5;   // SPI - MOSI1
    
    _RP56R = 9;   // SPI - SCK2
    _RP72R = 8;   // SPI - MOSI2

    _RP54R = 12;   // SPI - SCK3
    _RP53R = 11;   // SPI - MOSI3
    
    //_RP46R = 21;    // CAN Output  - Test board
    _RP47R = 21;    // CAN Output  - SAST
    
    __builtin_write_RPCON(0x0800); // Lock Registers
    
    //**************************************************************************
    //  PORT A
    //	Pin	Port	PPS	Function	IO          Description
    //	8	RA0		CTL_CS_A0       Output      CS select
    //	9	RA1		CTL_CS_A1		Output      CS select
    //	10	RA2		CTL_CS_A2		Output      CS select
    //	11	RA3		CTL_CS_A3       Output      CS select
    //	12	RA4		CTL_CS_A4       Output      CS select

    ANSELA= 0x0000; // Set analogic input 
    ODCA  = 0x0000; // Set Output for Open-Drain configuration
    LATA  = 0x0000; // latch output register setting (might not == to actual output)
    CNPUA = 0x0000; // weak pull up for input only
    CNPDA = 0x0000; // weak pull down for input only
    TRISA = 0x0000; // Input (1) or Output (0) register, overrided by Ansel

    //**************************************************************************
    //  PORT B
    //	Pin	Port	PPS     Function        IO          Description
    //	21	RB0     RP32	OSC1            input	
    //	22	RB1     RP33	INT_Alert_2     input	
    //  25	RB2     RP34                    Output
    //	26	RB3     RP35	Uart1 RX        input	
    
    //	27	RB4     RP36	Uart1 TX        output	
    //	33	RB5     RP37	Uart2 TX        output	
    //	34	RB6     RP38	Uart2 RX        input	
    //	35	RB7     RP39                    output
    
    //	36	RB8     RP40	PGED1           Output      n/a	SCL
    //	37	RB9     RP41	PGEC1           Output      n/a	SDA
    //	45	RB10	RP42                    Output
    //	46	RB11	RP43                    Output
    
    //	47	RB12	RP44                    Output
    //	48	RB13	RP45                    Output
    //	1	RB14	RP46	CAN RX          input	
    //	2	RB15	RP47	CAN TX          Output	

    ANSELB= 0x0000; // Set analogic input    
    ODCB  = 0x0300; // Set Output for Open-Drain configuration
    LATB  = 0x0000; // latch output register setting (might not == to actual output)      
    CNPUB = 0x0000; // weak pull up for input only
    CNPDB = 0x0000; // weak pull down for input only   
    TRISB = 0x404B; // Input (1) or Output (0) register, overrided by Ansel 
    

    //**************************************************************************
    // PORT C
    //	Pin	Port	PPS     Function	IO      Description
    //	7	RC0     RP48	SCK1        Output		
    //	15	RC1     RP49	MISO1       Input	
    //	16	RC2     RP50	MOSI1       Output	
    //	20	RC3     RP51	Gyro_ALarm  Input		
    
    //	38	RC4     RP52	MISO3		Input
    //	39	RC5     RP53	MOSI3		Output
    //	17	RC6     RP54	SCK3		Output
    //	24	RC7     RP55	n/a         Output
    
    //	28	RC8     RP56	SCK2        Output	
    //	29	RC9     RP57	MISO2       Input	
    //	40	RC10	RP58	n/a         Output	
    //	41	RC11	RP59	n/a         Output	
    
    //	3	RC12	RP60	Uart3 TX    Output	
    //	4	RC13	RP61	Uart3 RX	Input	

    ANSELC= 0x0000; // Set analogic input 
    ODCC  = 0x0000; // Set Output for Open-Drain configuration
    LATC  = 0x0000; // latch output register setting (might not == to actual output)
    CNPUC = 0x0000; // weak pull up for input only
    CNPDC = 0x0000; // weak pull down for input only  
    TRISC = 0x221A; // Input (1) or Output (0) register, overrided by Ansel 
    //TRISC = 0x0000; // Input (1) or Output (0) register, overrided by Ansel 

    //**************************************************************************
    // PORT D
    //	Pin	Port	PPS     Function	IO      Description
    //	44	RD1     RP65    Volt_Alarm  Input	
    //	30	RD8 	RP72	MOSI2       output	Master
    //	23	RD10	RP74	CS_Cont		Output
    //	6	RD13	RP77	CAN enable	Output	

    ANSELD= 0x0000; // Set analogic input 
    ODCD  = 0x0000; // Set Output for Open-Drain configuration
    LATD  = 0x0000; // latch output register setting (might not == to actual output)
    CNPUD = 0x0000; // weak pull up for input only
    CNPDD = 0x0000; // weak pull down for input only  
    TRISD = 0x0000; // Input (1) or Output (0) register, overrided by Ansel 
    //TRISD = 0x0000; // Input (1) or Output (0) register, overrided by Ansel 

}
/*******************************************************************************
 * Function: init_sleep(); 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_sleep(void)
{
    // Set ICN (input change notification) on RB1 - Accel HG for wake up
    CNCONBbits.CNSTYLE = 1; // Setting Active low
    CNEN1Bbits.CNEN1B1 = 1; // Setting Active low
    CNEN0Bbits.CNEN0B1 = 0; // Setting Active low
    
    //CNCONBbits.ON = 1; 
    
}

/*******************************************************************************
 * Function: Enable_Sleep_Interrupt(); 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Enable_Sleep_Interrupt(void)
{
    CNCONBbits.ON = 1; 
    
    IFS0bits.CNBIF = 0; // interupt flag
    CNFBbits.CNFB1 = 0; // port flag
    IEC0bits.CNBIE = 1; // enable interrupt 
    
    
}
/*******************************************************************************
 * Function: Disable_Sleep_Interrupt(); 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Disable_Sleep_Interrupt(void)
{
    IEC0bits.CNBIE = 0; // clear interrupt 
    IFS0bits.CNBIF = 0; // interupt flag
    CNFBbits.CNFB1 = 0; // port flag
    IEC0bits.CNBIE = 1; // enable interrupt 
    
    CNCONBbits.ON = 0; 
}
/*******************************************************************************
 * Function: init_osc
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_osc_External(void)
{
    
    ////code example for 48 MIPS system clock using POSC with 8 MHz external crystal
    //// Select FRC on POR
    //#pragma config FNOSC = FRC // Oscillator Source Selection (Internal Fast RC (FRC))
    //#pragma config IESO = OFF
    /// Enable Clock Switching and Configure POSC in XT mode
    //#pragma config POSCMD = XT
    //#pragma config FCKSM = CSECMD
    
    // MIPS (MHz) == Xtal/4 * PLLFBDIV / POST1DIV / 
    //System frequency (Fosc):  40.00 MHz [(8.00 MHz / 1) * 50 / 5 / 2 = 40.00 MHz]
    //FOSCbits.OSCIOFNC = 0; 
    ////////////////////////////////////////////////////////////////////////////
    // 10 MIPS
    // FOSC 20Mhz
    // Fck Peripheral == 10Mhz (instructions)
    // FVCO = 400 MHz,
    // FPLLO = 40 MHz)
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
    CLKDIVbits.PLLPRE = 1; // N1
    PLLFBDbits.PLLFBDIV = 50; // M
    PLLDIVbits.POST1DIV = 5; // N2
    PLLDIVbits.POST2DIV = 2; // N3 
    
    ////////////////////////////////////////////////////////////////////////////
    // 20 MIPS
    // FOSC 40Mhz
    // Fck Peripheral == 20Mhz (instructions)
    // FVCO = 400 MHz,
    // FPLLO = 80 MHz)
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
//    CLKDIVbits.PLLPRE = 1; // N1
//    PLLFBDbits.PLLFBDIV = 50; // M
//    PLLDIVbits.POST1DIV = 5; // N2
//    PLLDIVbits.POST2DIV = 1; // N3 
    
    ////////////////////////////////////////////////////////////////////////////
    // 40 MIPS
    // Fck == 20Mhz (instructions)
    // FVCO = 480 MHz,
    // FPLLO = 160 MHz)
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
//    CLKDIVbits.PLLPRE = 1; // N1
//    PLLFBDbits.PLLFBDIV = 60; // M
//    PLLDIVbits.POST1DIV = 3; // N2
//    PLLDIVbits.POST2DIV = 1; // N3
    
    // Fck == 48Mhz
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
//    CLKDIVbits.PLLPRE = 1; // N1=1
//    PLLFBDbits.PLLFBDIV = 2; // M = 30
//    PLLDIVbits.POST1DIV = 1; // N2=5
//    PLLDIVbits.POST2DIV = 1; // N3=1
    
    // 80 MIPS
    // Fck == 40Mhz (instructions)
    // FVCO = MHz,
    // FPLLO = MHz)
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
//    CLKDIVbits.PLLPRE = 1; // N1
//    PLLFBDbits.PLLFBDIV = 80; // M
//    PLLDIVbits.POST1DIV = 2; // N2
//    PLLDIVbits.POST2DIV = 1; // N3
    
       // 160 MIPS
    // Fck == 80Mhz (instructions)
    // FVCO = 640MHz,
    // FPLLO = 320MHz)
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
//    CLKDIVbits.PLLPRE = 1; // N1
//    PLLFBDbits.PLLFBDIV = 160; // M
//    PLLDIVbits.POST1DIV = 2; // N2
//    PLLDIVbits.POST2DIV = 1; // N3
    
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN!= 0);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK!= 1);

}

/*******************************************************************************
 * Function: init_osc
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_osc_Internal(void)
{
    //code example for 50 MIPS system clock using 8MHz FRC
    // Select Internal FRC at POR
    //_FOSCSEL(FNOSC_FRC & IESO_OFF);
    // Enable Clock Switching
    //_FOSC(FCKSM_CSECMD);

     ////////////////////////////////////////////////////////////////////////////
    // 10 MIPS
    // FOSC 20Mhz
    // Fck Peripheral == 10Mhz (instructions)
    // FVCO = 400 MHz,
    // FPLLO = 40 MHz)
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
    CLKDIVbits.PLLPRE = 1; // N1
    PLLFBDbits.PLLFBDIV = 50; // M
    PLLDIVbits.POST1DIV = 5; // N2
    PLLDIVbits.POST2DIV = 2; // N3 
    
    ////////////////////////////////////////////////////////////////////////////
    // Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
//    CLKDIVbits.PLLPRE = 1; // N1=1
//    PLLFBDbits.PLLFBDIV = 60; // M = 125
//    PLLDIVbits.POST1DIV = 6; // N2=5
//    PLLDIVbits.POST2DIV = 1; // N3=1
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    // Wait for PLL to lock
    //while (OSCCONbits.LOCK!= 1);
}

/*******************************************************************************
 * Function: clock_switching
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_clock_switching(void)
{
    
}
/*******************************************************************************
 * Function: clock_switching
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void clock_switching(void)
{
    
}
/*******************************************************************************
 * Function: init_timer_1
 * Parameters: none
 * Return: none
 * Description: Time keeping with interrupt
 ******************************************************************************/
void init_timer_1(void)
{
//    // FOSC = 48MHz
//    // instruction cycle = FOSC/4 = 12
//    // 12MHz / 8 / 375 = 4kHz ~ 250us
////    T1CONbits.TCKPS = 3;    // Prescaler  1:256
////    PR1 = 12; 
////    T1CONbits.TON = 1; 
//    
//    T1CONbits.TCS = 0; // clock from peripheral clock
//    T1CONbits.TCKPS = 0; // 1:1 prescale
//    PR1 = 0x8000; // rollover every 0x8000 clocks
//    T1CONbits.TON = 1; // start timer to generate ADC triggers
    
    // FOSC = 20MHz
    // instruction cycle = FOSC/4 = 12
    // PR1 = 20MHz / 2 / Prescaler / time period 
    // PR1 = 20MHz / 2 / 1 * 1ms = 10000
    // T1CONbits.TCKPS = 3;    // Prescaler  1:256
    // PR1 = 12; 
    // T1CONbits.TON = 1; 
    
    T1CONbits.TCS = 0; // clock from peripheral clock
    T1CONbits.TECS = 1; // Set to Tcy (Instruction cycle period)
    T1CONbits.TCKPS = 0; // 1:1 prescale
    PR1 = 10000; // rollover every X clocks
    
    IEC0bits.T1IE = 1; // enable interrupt
    IFS0bits.T1IF = 0; // clear flag
    
    T1CONbits.TON = 1; // start timer to
    
    
    
    
}

/*******************************************************************************
 * Function: init_timer_2
 * Parameters: none
 * Return: none
 * Description: Main loop timing no interrupt
 ******************************************************************************/
void init_timer_2(void)
{
    /*
     To use the module in Dual 16-Bit Timer mode:
        1. Set CCSEL = 0 to select the Time Base/Output Compare mode of the module.
        2. Set T32 = 0 to select the 16-bit time base operation.
        3. Set MOD[3:0] = 0000 to select the Time Base mode.
        4. Set SYNC[4:0] to the desired time base synchronization source:
        - Configure and enable the external source selected by SYNC[4:0] before enabling
        the timer.
        - If the timer is not using an external Sync source (SYNC[4:0] = 00000), or if the module
        is synchronizing to itself (the SYNC[4:0] bits select the module?s own value as a Sync
        source), write the desired count period of the primary 16-bit time base to CCPxPRL.
        5. If the secondary timer is also being used, write a non-zero value to CCPxPRH to specify
        the count period.
        6. If the special A/D trigger is being used, set CCPxRB for the desired trigger output time
        7. Enable the module by setting the CCPON bit.
        8. If an external synchronization source is selected in Step 4, configure
     */
    CCP1CON1Lbits.CCSEL = 0;        // Set compare module to general timer
    CCP1CON1Lbits.T32 = 0;          // Set dual 16 bits timer
    CCP1CON1Lbits.MOD = 0000;       // Set compare module to general timer
    CCP1CON1Lbits.CLKSEL = 2;      // Set Clock to FOSC
    //CCP1CON1L.TMRSYNC = 1; 
    
    CCP1CON1Hbits.SYNC = 0;         // Not use has external sync source
    
     // 10 MIPS - 50us
    // CCPxPRL = Fosc * tick = 20Mhz * 50us = 1000
    CCP1PRH = 0; 
    CCP1PRL = 1000; //
    
    
    //IEC0bits.CCT1IE = 1; 
    //IEC0bits.CCP1IE = 1; 
    
    CCP1CON1Lbits.CCPON = 1; // Enable
}

/*******************************************************************************
 * Function: init_timer_3
 * Parameters: none
 * Return: none
 * Description: Timeout back up
 ******************************************************************************/
void init_timer_3(void)
{
    // 
    CCP3CON1Lbits.CCPON = 0;
    CCP3CON1Lbits.CCSEL = 0;        // Set compare module to general timer
    CCP3CON1Lbits.T32 = 1;          // Set dual 16 bits timer
    CCP3CON1Lbits.MOD = 0;          // Set compare module to general timer
    CCP3CON1Lbits.CLKSEL = 2;       // Set Clock to FOSC
    CCP3CON1Lbits.TMRPS = 1;        // Time Base Prescale Select bits
    //CCP3CON1L.TMRSYNC = 1; 
    
    CCP3CON1Hbits.SYNC = 0;         // Not use has external sync source
    
    // 10 MIPS - 20Mhz
    // I2C 
    
    // CCPxPRL = Fosc * tick = 20Mhz * 1us = 20
    CCP3PRH = 0; 
    CCP3PRL = 1000; //
    //CCP3CON1Lbits.CCPON = 1; // Enable
}

/*******************************************************************************
 * Function: init_timer_4
 * Parameters: none
 * Return: none
 * Description: Timeout for waking up device while waiting 
 ******************************************************************************/
void init_timer_4(void)
{
    // 
    CCP4CON1Lbits.CCPON = 0;
    CCP4CON1Lbits.CCSEL = 0;        // Set compare module to general timer
    CCP4CON1Lbits.T32 = 1;          // Set dual 16 bits timer
    CCP4CON1Lbits.MOD = 0;          // Set compare module to general timer
    
    //CCP4CON1Lbits.CLKSEL = 3;       // Set CLC1 for LPRC clock source 
    CCP4CON1Lbits.CLKSEL = 1;       // Reference Clock (REFCLKO)
    //CCP4CON1Lbits.CLKSEL = 0;       // FOSC/2 (FP)
    
    
    CCP4CON1Lbits.TMRPS = 0;        // Time Base Prescale Select bits
    //CCP3CON1L.TMRSYNC = 1; 
    
    CCP4CON1Hbits.SYNC = 0;         // Not use has external sync source
    
    CCP4CON1Lbits.CCPSLP = 1;       // keep timer running in sleep mode
    
    PMD2bits.CCP4MD = 0;            // SCCP4 module is enabled (reverse logic)
    // 10 MIPS - 20Mhz
    // I2C 
    
    // CCPxPRL = Fosc * tick = 20Mhz * 1us = 20
    // 20Mhz * 5sec = 100000000 = 0x05F5E100
//    CCP4PRH = 0x05F5; 
//    CCP4PRL = 0xE100; //
    
    // 
    CCP4PRH = 0x0001; 
    CCP4PRL = 0xFFFF; //
    //CCP3CON1Lbits.CCPON = 1; // Enable
}
/*******************************************************************************
 * Function: start_timer_4
 * Parameters: none
 * Return: none
 * Description: Timeout for waking up device while waiting 
 ******************************************************************************/
void start_timer_4(void)
{
    IFS2bits.CCT4IF = 0; // clear flag
    IEC2bits.CCT4IE = 1; // Capture/Compare/Timer X Interrupt bit
    //IEC2bits.CCP4IE = 1; // Input Capture/Output Compare XInterrupt bit
    
    CCP4CON1Lbits.CCPON = 1; // Enable
}

/*******************************************************************************
 * Function: stop_timer_4
 * Parameters: none
 * Return: none
 * Description: Timeout for waking up device while waiting 
 ******************************************************************************/
void stop_timer_4(void)
{
    IEC2bits.CCT4IE = 0;
    CCP4CON1Lbits.CCPON = 0; // 
}

/*******************************************************************************
 * Function: init_ref_clock
 * Parameters: none
 * Return: none
 * Description: ref clock but output disabled only for clock in sleep
 ******************************************************************************/
void init_ref_clock(void)
{
    PMD4bits.REFOMD = 0; // Reference clock module is enabled (reverse logic)
    
    REFOCONLbits.ROEN = 0; // disabled ref clock (virtual pin)
    
    //while(REFOCONLbits.ROACTIVE == 1){}; // wait clock is off
    
   
    // Frefout = Frefin / (2 * (RODIV[14:0] + ROTRIM[8:0] / 512))
    // Frefout = 32 kHz [LPRF] / (2 * (1 + 1/512)) ==~ 16khz
    REFOCONH = 1; 
    REFOTRIMH = 1; 
    
    REFOCONLbits.ROSIDL = 0; // Reference Oscillator continues to run in Idle mode
    
    REFOCONLbits.ROSLP = 1; // Reference Oscillator continues to run in Sleep modes
    
    //REFOCONLbits.ROSEL = 0b0111; // REFI pin
    //REFOCONLbits.ROSEL = 0b0110; // FVCO/4
    //REFOCONLbits.ROSEL = 0b0101; // BFRC
    REFOCONLbits.ROSEL = 0b0100; // LPRC
    //REFOCONLbits.ROSEL = 0b0011; // FRC
    //REFOCONLbits.ROSEL = 0b0010; // Primary Oscillator
    //REFOCONLbits.ROSEL = 0b0001; // Peripheral clock (FP)
    //REFOCONLbits.ROSEL = 0b0000; // System clock (FOSC)
    
    while(REFOCONLbits.ROSWEN == 1){}; // wait clock
    
    REFOCONLbits.ROEN = 1; // enable ref clock (virtual pin)
    
    //while(REFOCONLbits.ROSWEN == 0){}; // wait clock
    while(REFOCONLbits.ROACTIVE == 0){}; // wait clock is ready
   
    
     
}
/*******************************************************************************
 * Function: CLC_config
 * Parameters: none
 * Return: none
 * Description: Timeout for waking up device while waiting 
 ******************************************************************************/
void CLC_config(void)
{
    
    CLC1SELbits.DS1 = 0b011; // INTRC/LPRC clock source
    CLC1GLSLbits.G1D2T = 1; // acitvate gate
    CLC1CONHbits.G1POL = 0; // non inverted
    CLC1CONLbits.MODE = 0b001; 
    CLC1CONLbits.LCEN = 1; 
    
}
/*******************************************************************************
 * Function: init_watch_dog
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_watch_dog(void)
{
    volatile unsigned *wdtKey;
    wdtKey = (&WDTCONH);
    //WDTCONLbits.CLKSEL = 2; // FRC oscillator
    //WDTCONLbits.CLKSEL = 3; // LPRC oscillator
    //WDTCONLbits.RUNDIV = 0b01101; //8.192s 
    //WDTCONLbits.WDTWINEN = 0; // Disables Window mode
    *wdtKey = 0x5743;
    WDTCONLbits.CLKSEL = 3; // LPRC oscillator
    WDTCONLbits.SLPDIV = 0b01101; //8.192s
    WDTCONLbits.RUNDIV = 0b01101; //8.192s
    WDTCONLbits.ON = 1;
    
    
}
/*******************************************************************************
 * Function: start_timer_4
 * Parameters: none
 * Return: none
 * Description: Timeout for waking up device while waiting 
 ******************************************************************************/
void start_watch_dog(void)
{
    WDTCONLbits.ON = 1; // Enable the wtch dog
}

/*******************************************************************************
 * Function: stop_timer_4
 * Parameters: none
 * Return: none
 * Description: Timeout for waking up device while waiting 
 ******************************************************************************/
void stop_watch_dog(void)
{
    WDTCONLbits.ON = 1; // Disable the wtch dog
}

/*******************************************************************************
 * Function: init_Dead_Man_timer
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_Dead_Man_timer(void)
{
    //DMTCNTL = 0; 
    //DMTCNTH = 0; 
    DMTCONbits.ON = 0; // enable DMT
}

/*******************************************************************************
 * Function: Reset_Dead_Man_timer
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Reset_Dead_Man_timer(void)
{
    DMTPRECLRbits.STEP1 = 0x40; 
    DMTCLRbits.STEP2 = 0x08; 
}
/*******************************************************************************
 * Game over
 ******************************************************************************/
