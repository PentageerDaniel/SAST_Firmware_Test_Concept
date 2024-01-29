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
 *      main.c
 * 
 * @Project
 *      SAST
 * 
 ******************************************************************************/
/*******************************************************************************
 * Revision 
 ******************************************************************************/
// 
#define Version_Major   1
#define Version_Minor   1
#define Version_Patch   24
#define Version_Build   7

#define Hardware_PIC    "dspic33ck512mp605"

#define Hardware_Source 0x1A // 1A == SAST, 1B computer, 1C == CUA ... 

#define Firmware_type   0xAA // AA == Main, BB == Bootloader 

//<editor-fold defaultstate="collapsed" desc="Version Revision Description">
/********************************************************************************
 * Revision 1.0.24.2
1) change ADC reading for voltage, always one shot for drilling and not drilling
2) Add back magnetometer
3) Add error counter for I2C reading during 125k
*******************************************************************************
 * Revision 1.0.23.3
1) Add start drilling when 5V added
2) issue when erase and after start drilling no data
*******************************************************************************
 * Revision 1.0.22
1) Add Gyro switch power 
2) Memory change sleep option: All on or all sleep since keep only one alive is nut
*******************************************************************************  
 * Revision 1.0.21
1) Add toolface calculation and adding new message A9
2) Add new message debug for mag A3
3) Add function disable sensors
4) find error memory index for sleeping not right
5) add code to subtract voltage swing from gyro but not working
******************************************************************************* 
Revision 1.0.20
1) Testing sleep, still in progress
2) fix OSC pin function, so we can use Accel HG to wake up 
3) Add interrupt to wake up 
4) Test external int work, but no need at the moment
******************************************************************************* 
Revision 1.0.19
1) Add 125Hz drilling
2) Add get version and display at startup
3) Read 2 channel for ADC: Gyro and Gyro voltage (after mod)
4) Remove error escape on I2c write function. To be tested ....  
******************************************************************************* 
Revision 1.0.18
1) fix accel 373 burst detection
2) Todo add previos and after check for burst
******************************************************************************* 
Revision 1.0.17
1) Add multiplication for finding magnitude
******************************************************************************* 
Revision 1.0.16
1) Remove peak interrupt for HG accel
2) put back magnotemoter from 250Hz for vibe 
3) find issue sensor noise I2C Accel-> LG3 is bad
4) change burst using 2 array of 12288 bytes (-1.5s to 1.5s) 
******************************************************************************* 
Revision 1.0.15
1) Add peak CAN command
2) remove magnotemoter from 250Hz for vibe 
******************************************************************************* 
Revision 1.0.14
1) Add pointer searching Data
2) Add pointer searching Event not tested
3) Add fifo accel HG not tested
******************************************************************************* 
Revision 1.0.13
1) Add memory event I2C, non tested yet
******************************************************************************* 
Revision 1.0.12
1) Change I2C assembly debug function to fix memory issue
*******************************************************************************      
Revision 1.0.11
1) Try memory 4 bytes addressing rather than 3
*****************************************************************************
Revision 1.0.10
1) Backup
*****************************************************************************
Revision 1.0.9
1) Backup
*******************************************************************************
Revision 1.0.8
1) Add memory code for the 20units
*******************************************************************************
Revision 1.0.7
1) I2C problem patched with Assembly bit bang. 
*******************************************************************************
Revision 1.0.6
1) Problem with RTOS and I2C. If only gyro on line it works good.Might needs to do 
disregard other pheripheral if cannot find solution in the mean time 
*******************************************************************************
Revision 1.0.5
1) Add RTOS for 4ms + burst 
*******************************************************************************
Revision 1.0.4
1) DMA work in ping pong with UART 1 and 2, but cannot copy buffer to RAM. data is imcomplete. 
2) Issue with I2C for the current reading, it seems the INA part produce some noise 
and make ADC act bad. Remove 2 resistors in hardware so work can carry on. Will need to fix
most likely in hardware
*******************************************************************************
Revision 1.0.3
1) Fix DMA for UART 1 and 2. 
2) Issue with I2C, get bus collision at first write
******************************************************************************* 
Revision 1.0.2
1) ADD DMA channel for both UART 1: RX1 to TX2 and 
UART 2: RX2 to TX 1 pass through 
*******************************************************************************
Revision 1.0.1
Change frequency Fosc to 10Mips / 20Mhz. Verify that CAN can work for 1Mhz/4Mhz 
*******************************************************************************
Revision 1.0.0
Initial code
*******************************************************************************
* 
 */
//</editor-fold>

/*******************************************************************************
 * Include
 ******************************************************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include <xc.h>
#include "Init.h"
#include "variable.h"
#include <math.h>
#include <errno.h> /* for errno */

//#include <stdio.h>
//#include <stdlib.h>

/*******************************************************************************
 * DSPIC33CK512MP605 Configuration Bit Settings
 ******************************************************************************/
//<editor-fold defaultstate="collapsed" desc="Bits Configutation">
// DSPIC33CK512MP605 Configuration Bit Settings
// 'C' source line config statements
// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FSIGN

// FOSCSEL external
#pragma config FNOSC = PRIPLL          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC  External
#pragma config POSCMD = EC              // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = ON              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
#pragma config XTCFG = G1               // XT Config (8-16 MHz crystals)
#pragma config XTBST = DISABLE          // XT Boost (Default kick-start)

//// FOSCSEL internal
//#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
//#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)
//
//// FOSC
//#pragma config POSCMD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode)
//#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
//#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
//#pragma config PLLKEN = ON              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
//#pragma config XTCFG = G1               // XT Config (8-16 MHz crystals)
//#pragma config XTBST = DISABLE          // XT Boost (Default kick-start)

// FWDT
#pragma config RWDTPS = PS2147483648    // Run Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config SWDTPS = PS2147483648  // Sleep Mode Watchdog Timer Post Scaler select bits (1:2147483648)
//#pragma config SWDTPS = PS8192             // Sleep Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config FWDTEN = ON            // Watchdog Timer Enable bit (WDT enabled in hardware)

// FPOR
#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGC1 and PGD1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config NOBTSWP = DISABLED       // BOOTSWP instruction disable bit (BOOTSWP instruction is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF         // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF         // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 Pin bit (I2C2 mapped to SDA2/SCL2 pins)
#pragma config ALTI2C3 = OFF            // Alternate I2C3 Pin bit (I2C3 mapped to SDA3/SCL3 pins)
#pragma config SMBEN = SMBUS            // SM Bus Enable (SMBus input threshold is enabled)
#pragma config DUPPWM = PPS             // Duplicate PWM Pin Mapping (Default PWM Functions of PPS and Fixed Pins)
#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// FBTSEQ
#pragma config BSEQ = 0xFFF             // Relative value defining which partition will be active after device Reset; the partition containing a lower boot number will be active (Enter Hexadecimal value)
#pragma config IBSEQ = 0xFFF            // The one's complement of BSEQ; must be calculated by the user and written during device programming. (Enter Hexadecimal value)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//</editor-fold>

/*******************************************************************************
 * Function: boot
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
int main(void)
{
    uint8_t buffer[32] = {0x00}; 
    uint8_t cmd_buffer[2] = {0x00}; 
    uint8_t test = 0;
//    int16_t accel_X_HG = -100;
//    int16_t accel_Y_HG = 0xFF9C; // -100
//    int16_t accel_Z_HG = 2500;
//    int32_t result_X2 = 0;
//    int32_t result_Y2 = 0;
//    int32_t result_Z2 = 0;
//    uint32_t sum_accel_axis_HG = 0;
    uint16_t timeout_DEBUG = 0;
    uint16_t i = 0; 
    //uint8_t buffer[3] = {0x01,0x02,0x03}; 
    
    // need to add delay
    
    initialize_mcu(); 
    
//    Start_Timer_3(12500);
//    while(Check_Timer_3() == 0){}; 
//    Stop_Timer_3();
    
    ///////////////////////////////////////////////
    // default time
    Time.year = 0x17; 
    Time.month = 0x05; 
    Time.days = 0x0F; 
    Time.hours = 0x08; 
    Time.minutes = 0x00; 
    Time.seconds = 0x00; 
    Time.miliseconds = 0x0000;
    /////////////////////////////////////////////////////
    
    //Debug_PIN_TX1 = 1;
    
    //IO_Ports_Setting(); 
    
    //Debug_PIN_TX1 = 0;
    I2C_Errors_Counter = 0; 
    
    CS_CONT = 0; 
    
    ADC_VOLT_PD = 1; 
    
    while(1)
    {
        
        if(IFS0bits.CCT1IF == 1) 
        {
            IFS0bits.CCT1IF = 0;
            // 10 Mips - 20Mhz + timer == Slice time is 50us
            TimerCounter100us += 1;
            TimerCounter200us += 1;
            TimerCounter250us += 1; 
            
            
            /*******************************************************************
             * 50us LOOP routine                                          
            *******************************************************************/
            if(State_Flags.Drill_State == 1)
            {
//                timeout_DEBUG++;
//                if(timeout_DEBUG > 1000)
//                {
//                    State_Flags.Drill_State = 0; 
//                    timeout_DEBUG = 0; 
//                }
                if(State_Flags.Drill_125Hz_State == 1) 
                {
                    RTOS_50us_Routine_125Hz(); // 125Hz
                }
                else if(State_Flags.Drill_250Hz_State == 1) 
                {
                    RTOS_50us_Routine_250Hz(); // 250Hz
                }
                else
                {
                    RTOS_50us_Routine_125Hz(); // 125Hz
                }
            }
            else
            {
                //LEDR = !LEDR; // LED red
                //LEDR = 0; // LED red
            }
            
            if(State_Flags.Idle_State == 1)
            {

            }
            

        
            /*******************************************************************
             * 100us LOOP routine                                          
            *******************************************************************/
            if(TimerCounter100us == 2)
            {
                
                
                TimerCounter1ms += 1;
                TimerCounter400us += 1; 
                TimerCounter100us = 0; 
            }
            
            /*******************************************************************
            * 200us LOOP routine                                          
            *******************************************************************/
            if(TimerCounter200us == 200) // 200us
            {
//                if((State_Flags.Drill_State == 1) || (Debug_Flags.Burst == 1))
//                {
//                    Get_Burst_Data(); 
//                }
                TimerCounter200us = 0; 
            }
            
            /*******************************************************************
             * 250us LOOP routine                                          
            *******************************************************************/
            if(TimerCounter250us == 5)
            {
                //Get_Voltage_3V3_5V(); 
                
                TimerCounter250us = 0; 
            }
            
            /*******************************************************************
            * 400us LOOP routine                                          
            *******************************************************************/
            if(TimerCounter400us == 4) // 400us
            {
                TimerCounter400us = 0; 
            }

            /*******************************************************************
             * 1ms LOOP routine                                          
            *******************************************************************/
            if(TimerCounter1ms == 10) 	// 1ms
            {
                
                if(Init_Flag)
                {
                    //Debug_PIN_TX1 = !Debug_PIN_TX1;
                    
                    if(MT25QL01_Flag.Mem_Erase == 1)
                    {
                        MT25QL01_Flag.Mem_Erase = 0; 
                        buffer[0] = 0x38; 
                        buffer[1] = 0x4F; // O
                        buffer[2] = 0x4B; // K
                        buffer[3] = MT25QL01_To_Erase; // K
                        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
                        MEM_MT25QL01_Erase_Memory(MT25QL01_To_Erase); 
                        
                    }
                    
//                    if(MEM_CY15B064J_Flag.Mem_Erase_Pass == 1)
//                    {
//                        MEM_CY15B064J_Flag.Mem_Erase_Pass = 0; 
//                        MEM_CY15B064J_Flag.Mem_Erase_Request = 0; 
//                        buffer[0] = 0x43; 
//                        buffer[1] = 0xAC; // ok
//                        buffer[2] = 0xED; 
//                        buffer[3] = MEM_CY15B064J_Erase_In_Used;
//                        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//                        //MEM_CY15B064J_Erase(MEM_CY15B064J_Erase_In_Used); 
//                        
//                    }
                    
                    //////////////////////////////////////////////////////////
                    //State_Flags.Mem_Event_Pointer_Seek = 0;
                    //State_Flags.Mem_Data_Pointer_Seek = 0; 
//                    if(State_Flags.Mem_Data_Pointer_Seek == 1)
//                    {
//                        MEM_MT25QL01_Pointer_Seaching(); 
//                    }
//                    
//                    if(State_Flags.Mem_Data_Pointer_Seek == 0 &&
//                       State_Flags.Mem_Event_Pointer_Seek == 1)
//                    {
//                        MEM_CY15B064J_Pointer_Seaching();
//                        //State_Flags.Mem_Event_Pointer_Seek = 0;
//                    }
                    ///////////////////////////////////////////////////////////
                    
                    
//                    if(MEM_CY15B064J_Flag.Mem_Read == 1)
//                    {
//                        MEM_CY15B064J_Read_All_Event_Mem(); 
//                    }
                    //RTOS_50us_Routine(); 
                    //LEDG = !LEDG; // LED green
                    //LEDR = !LEDR; // LED red
                }
                
                TimerCounter1ms = 0; 	// reset timer
                TimerCounter250ms += 1; 
            }

  
            
            /*******************************************************************
             * 250ms LOOP routine                                          
            *******************************************************************/
            if(TimerCounter250ms == 250) // 250ms
            {
                //PORTCbits.RC12 = !PORTCbits.RC12; // CS_MEM2
                if(Init_Flag)
                {
                    //Debug_PIN_TX1 = !Debug_PIN_TX1;
                    
                    if(State_Flags.Idle_State == 1)
                    {
                        //Debug_PIN_TX1 = !Debug_PIN_TX1;
                        
                        //Get_Voltage_3V3_5V();
                        
//                        if((NumberEventSaved>0) && (State_Flags.Mem_Event_Pointer_Seek == 0))
//                        {
//                            //Write_Event_I2C_Mem(1); 
//                            buffer[0] = 0xAC; // ok
//                            buffer[1] = 0xED; 
//                            buffer[2] = 01; 
//                            buffer[3] = NumberEventSaved; 
//                            CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//                        }
//                        else
//                        {
//                            
//                        }
                    }
                    
                    
                }
                else
                {
                    Init_counter += 1; 
                    if((Init_Flag == 0) && (Init_counter >= Init_max_count))
                    {
                        IO_Ports_Setting();
                        //Debug_PIN_TX1 = 1;
                        //Get_Version_Firmware(buffer); 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); //
                        //Init_Drill_State(); 
                        
                        Init_Idle_State();
                        //State_Flags.Time_Sync_Set = 0; 
                        Init_Flag = 1; 
                        #ifdef Uart1_Debug_Message
                        buffer[0] = 0xC0; 
                        buffer[1] = 0xDE; 
                        buffer[2] = 0x00;
                        buffer[3] = 0x01;
                        write_string_uart_1(buffer, 4);
                        #endif
                    }
                }
                
                TimerCounter250ms = 0;
                TimerCounter1s += 1; 
            }
            /*******************************************************************
             * 1s LOOP routine                                          
            *******************************************************************/
            if(TimerCounter1s == 4) 	// 1s
            {
                //LEDG = !LEDG; // LED green
                //LEDR = !LEDR; // LED green
                //write_uart_3(0xAB);
                
                
                
//                buffer[0] = 0xAB; 
//                buffer[1] = 0xA1; 
//                buffer[2] = Get_Accel_Device_ID(); 
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
//                if(test == 0)
//                {
//                    //SET_ADC_ADS868x_Device_ID(SPI_CS_GYRO, i++);
//                    //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, 0x00);
//                    //SET_ALARM_H_TH_REG(SPI_CS_GYRO, 0x00, 0x00); 
//                    //Get_ADC_ADS863x_AUX_CONFIG(SPI_CS_VOLT);
//                    ADC_ADS868x_READ_DATA(SPI_CS_GYRO); 
//                    if(i>= 16)
//                    {
//                        i = 0; 
//                    }
//                    test = 1; 
//                }
//                else
//                {
//                    //Get_ADC_ADS868x_RANGE(SPI_CS_GYRO);
//                    //Get_ADC_ADS868x_Device_ID(SPI_CS_GYRO);
//                    //GET_ALARM_H_TH_REG(SPI_CS_GYRO); 
//                    
//                    //Get_ADC_ADS863x_RANGE(SPI_CS_VOLT);
//                      
//                    
//                    
//                    ///////////////////////////////////////////////
//                    //Get_ADC_ADS863x_AUX_CONFIG(SPI_CS_VOLT); 
//                    //ADC_ADS863x_READ_DATA(SPI_CS_VOLT, 1); 
//                    test = 0; 
//                    
//                }
                 
//                buffer[0] = 0xAB; 
//                buffer[1] = 0xA2; 
//                buffer[2] = Get_ADC_ADS868x_Device_ID(SPI_CS_GYRO); 
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                
//                if(test == 0)
//                {
//                    test = 1; 
//                    //CS_CONT = 0; 
//                    //CTL_CS_WR = 0;
//                    //PORTA = 0x02; 
//                    //CTL_CS_A0 = 0; 
//                    //CTL_CS_A1 = ~CTL_CS_A1; 
//                    //CTL_CS_A2 = 0; 
//                    //CTL_CS_A3 = 0; 
//                    //CTL_CS_A4 = 0; 
//                    //CTL_CS_WR = 1;
//                    //CS_CONT = 1; 
//                    //MUX1_ADG732_CHIP_SELECT(2);
//                    //CTL_CS_A1 = 1;
//                    //MUX1_ADG732_CHIP_SELECT(5);
//                }
//                else
//                {
//                    test = 0; 
//                    //PORTA = 0x00; 
////                    CS_CONT = 0; 
////                    CTL_CS_WR = 0;
////                    CTL_CS_A0 = 0; 
////                    CTL_CS_A1 = 0; 
////                    CTL_CS_A2 = 0; 
////                    CTL_CS_A3 = 0; 
////                    CTL_CS_A4 = 0; 
////                    CTL_CS_WR = 1;
////                    CS_CONT = 1; 
//                    //CTL_CS_A1 = 0;
//                    //MUX1_ADG732_CHIP_SELECT(0);
//                    //MUX1_ADG732_CHIP_DESELECT(0); 
//                }
                
                
                ///////////////////////////////////////////////////
                // TRansfer Xtall EXT to INT to EXT ...
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                Heartbeat_counter++; 
                if(Heartbeat_counter >= Heartbeat_max_count)
                {
                    Heartbeat_counter = 0; 
                    //Sleep_CTL = 1;
//                    if(test_Xtall == 1)
//                    {
//                        init_osc_Internal(); 
//                        test_Xtall = 0; 
//                        Sleep_CTL = 1; 
//                    }
//                    else
//                    {
//                        Sleep_CTL = 0; 
//                        init_osc_External(); 
//                        test_Xtall = 1; 
//                    }
                }
                ///////////////////////////////////////////////////
                
                
//                if(Init_Flag)
//                {
//                    
//                    
//                    if(State_Flags.Sleep_State == 0)
//                    {
////                        Go_To_Sleep_counter++; 
////                        if(Go_To_Sleep_counter >= Go_To_Sleep_max_count)
////                        {
////                            Go_To_Sleep_counter = 0; 
////                            Go_To_Sleep(); 
////                            //Xtal_Enable = 0; 
////                        }
//                        if(Volt_5V_Flags.Vol_Drill_Below_Sent == 1)
//                        {
//                            Go_To_Sleep_counter++; 
//                            if(Go_To_Sleep_counter >= Go_To_Sleep_max_count)
//                            {
//                                Go_To_Sleep_counter = 0; 
//                                Disabled_All_Sensors();
//                                //Debug_PIN_TX1 = 1; 
//                                Go_To_Sleep(); 
//                                //Xtal_Enable = 0; 
//                            }
//
//                        }
//                        
//                    }
//                    
//                    if(Accel_HG_Flag.Interrupt == 1)
//                    {
//                        Go_To_Sleep_counter = 0; // cancel going to sleep while reading Int 
//                        switch(Accel_HG_Sequencer)
//                        {
//                            case 0: 
//                                buffer[0] = ADXL373_SPI_Get_Register(0x04);
//                                break;
//                            case 1: 
//                                buffer[0] = ADXL373_SPI_Get_Register(0x05);
//                                break;
//                            case 2: 
//                                //cmd_buffer[0] = (ACC373_MAXPEAK_X_H << 1)| 0x01;
//                                //ADXL373_SPI_Get_Data(cmd_buffer, 1, buffer, 6)
//                                ADXL373_SPI_Get_Max_Peak();         
//                                break;
//                        }
//                        Accel_HG_Sequencer++;
//                        if(Accel_HG_Sequencer >= 3)
//                        {
//                            Accel_HG_Flag.Interrupt = 0; 
//                            Accel_HG_Sequencer = 0; 
//                        }
//                    }
//
//                }
   
                TimerCounter1s = 0;
                TimerCounter1m += 1; 
            }
            
            /*******************************************************************
             * 1m LOOP routine                                          
            *******************************************************************/
            if(TimerCounter1m == 60) 	// 1 minute
            {
                //Time_Sync(); 
                
                Time_Sync_Timeout_counter += 1; 
                if(Time_Sync_Timeout_counter >= Time_Sync_max_count)
                {
                    State_Flags.Time_Sync_Set = 1; 
                    Time_Sync_Timeout_counter = 0; 
                    
                }
                
                
                
                if((State_Flags.Drill_State == 1) || (State_Flags.Idle_State == 1))
                {
                    Time_Stamp_Timeout_counter += 1; 
                    if(Time_Stamp_Timeout_counter >= Time_Stamp_max_count)
                    {
                        //Save_Event_Buffer(uint8_t packetID, uint8_t event, uint8_t *data)
                        //buffer[0] = 0xAC; // ok
                        //buffer[1] = 0xED; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); // debug
                        //Save_Event_Cmd_Buffer(0xAA, 0x0C);
                        Time_Stamp_Timeout_counter = 0; 

                    }
                }
                
//                if(State_Flags.Idle_State == 1)
//                {
//                    if(NumberEventSaved>0)
//                    {
//                        Write_Event_I2C_Mem(1); 
//                        buffer[0] = 0xAC; // ok
//                        buffer[1] = 0xED; 
//                        buffer[2] = 0x01; 
//                        CAN_Encode_Sending(0x1B,0xC4, buffer, 2); // debug
//                    }
//                }
                
                TimerCounter1m = 0; 
            }
            
            /*******************************************************************
             * End LOOP routine                                          
            *******************************************************************/
            
            IFS0bits.CCT1IF = 0; 
        }
    }
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Get_Version_Firmware(uint8_t *buffer)
{
    buffer[0] = Hardware_Source;
    buffer[1] = Firmware_type; 
    buffer[2] = Version_Major;
    buffer[3] = Version_Minor;
    buffer[4] = Version_Patch;
    buffer[5] = Version_Build;
    return; 
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void IO_Ports_Setting(void)
{
//    CAN_Enable = 0;
//    while(CAN_Enable != 0)
//    {
//        CAN_Enable = 0; 
//    }
//    CAN_Enable = 1; 
//    while(CAN_Enable != 1)
//    {
//        CAN_Enable = 1; 
//    }
//    
//    Gyro_Enable = 0; 
//    while(Gyro_Enable != 0)
//    {
//        Gyro_Enable = 0; 
//    }
    
//    Sleep_CTL = 0; 
//    while(Sleep_CTL != 0)
//    {
//        Sleep_CTL = 0; 
//    }
    
//    Sleep_CTL = 0; 
//    while(Sleep_CTL != 0)
//    {
//        Sleep_CTL = 0; 
//    }
//    Debug_PIN_TX1 = 0;
//    while(Debug_PIN_TX1 != 0)
//    {
//        Debug_PIN_TX1 = 0; 
//    }
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void State_Machine_Reset(void)
{
    State_Flags.Init_State = 0;
    State_Flags.Idle_State = 0; 
    State_Flags.Sleep_State = 0;
    State_Flags.Drill_State = 0; 
    State_Flags.Drill_Init_State = 0;
    State_Flags.Drill_125Hz_State = 0; 
    State_Flags.Drill_250Hz_State = 0; 
    State_Flags.Burst_State = 0; 
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Init_Idle_State(void)
{
    //Debug_PIN_TX1 = 1;
    if(State_Flags.Idle_State != 1)
    {
        State_Machine_Reset(); 
    
        //ADC_MCP3422_Sequencer = 0; 

        State_Flags.Idle_State = 1; 
        State_Flags.Mem_Data_Pointer_Seek = 1; 
        //State_Flags.Mem_Event_Pointer_Seek = 1; 
    }
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Init_Drill_State(void)
{
    uint8_t buffer[3] = {0};
    //uint16_t tempo16;
    //State_Machine_Reset(); 
    ////////////////////////////////////////////////////////////////////////////
    // Gyro power
//    Gyro_Enable = 1; 
//    while(Gyro_Enable != 1)
//    {
//        Gyro_Enable = 1; 
//    }
    
    ////////////////////////////////////////////////////////////////////////////
    // wake memory
    MEM_MT25QL01_Wake_UP_All_Memory();
//    tempo16 = MEM_MT25QL01_Check_Status_Sleep(MT25QL01_In_Used);
//    if(tempo16 == 0xDEAD)
//    {
//        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_In_Used); 
//        Start_Timer_3(300);
//        while(Check_Timer_3() == 0){}; 
//        Stop_Timer_3();
//    }
//    if(MT25QL01_Flag.Mem_All_Sleep == 1)
//    {
//        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_In_Used);
//    }
    
    ////////////////////////////////////////////////////////////////////////////
    // HG Accel
     
    //ADXL373_SPI_Init_Wake_Up_Mode();
    
    if(ADXL373_SPI_ID(SPI_CS_ACC_HG) == 0xAD)
    {
        ADXL373_SPI_Init();
        
        ADXL373_SPI_Start_Sensor(); 
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB1; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
        
    }
    else
    {
        // error
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;       
        buffer[2] = 0xE1; 
        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Accel LG1
    if(Get_Accel_Device_ID(SPI_CS_ACC_LG1) == 0xAD)
    {
        
        ADXL355_SPI_Start_Sensor(SPI_CS_ACC_LG1); 
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB2; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    else
    {
        // error
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;       
        buffer[2] = 0xE2; 
        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Accel LG2
    if(Get_Accel_Device_ID(SPI_CS_ACC_LG2) == 0xAD)
    {
        
        ADXL355_SPI_Start_Sensor(SPI_CS_ACC_LG2); 
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB2; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    else
    {
        // error
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;       
        buffer[2] = 0xE3; 
        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    
    ////////////////////////////////////////////////////////////////////////////
    buffer[0] = MAG_MMC5983MA_read_ID(); 
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 1); // debug
    
    if(buffer[0] == 0x30)
    {
        //init_MAG_MMC5983MA(); // init 
        
        //Write_1_reg_I2C(MAG_MMC5983_ID,0x0B,0x0E); // auto meas, 200Hz
        //Write_1_reg_I2C(MAG_MMC5983_ID,0x0B,0x0F); // auto meas, 1000Hz
        buffer[0] = 0x0B;
        buffer[1] = 0x0F; // auto meas, 1000Hz
        MAG_MMC5983MA_Write_data_SPI(buffer, 2); 
        
        
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB4; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    else
    {
        // error
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;       
        buffer[2] = 0xE4; 
        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    }
    
    buffer[0] = 0xBB;
    buffer[1] = 0xCC;       
    buffer[2] = 0xDD; 
    CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    
    //ADC_MCP3422_Sequencer = 0; 
    //ADC_MCP3422_Set_Auto_Conversion(); // 3v3 only
   
    State_Flags.Drill_State = 1; 
    //State_Flags.Drill_250Hz_State = 1; 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Disabled_All_Sensors(void)
{
    uint8_t buffer[3] = {0};
    ////////////////////////////////////////////////////////////////////////////
    // Gyro power
//    Gyro_Enable = 0; 
//    while(Gyro_Enable != 0)
//    {
//        Gyro_Enable = 0; 
//    }
        
    ////////////////////////////////////////////////////////////////////////////
    // Memory put to sleep
    //MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_In_Used); 
    
    //MEM_MT25QL01_Shutdowm_All_Memory();
    
    // TODO: ensure all memories are sleeping 
    
    
    ////////////////////////////////////////////////////////////////////////////
    // HG Accel
    // Set to wake up with impact
    ADXL373_SPI_Stop_Sensor(); 
    
    ADXL373_SPI_Init_Wake_Up_Mode();
    
    ////////////////////////////////////////////////////////////////////////////
    // Accel LG1
    
    ADXL355_SPI_Stop_Sensor(SPI_CS_ACC_LG1); 
    
    ////////////////////////////////////////////////////////////////////////////
    // Accel LG2 - ACC_ADXL355_LG2_ID
    //ADXL355_I2C_Stop_Sensor(ACC_ADXL355_LG2_ID); 
    ADXL355_SPI_Stop_Sensor(SPI_CS_ACC_LG2); 
    ////////////////////////////////////////////////////////////////////////////
    // Accel LG3 - ACC_ADXL355_LG3_ID
    //ADXL355_I2C_Stop_Sensor(ACC_ADXL355_LG3_ID); 
    
    ////////////////////////////////////////////////////////////////////////////
    //init_ADC_MCP3422(); 
//    ADC_MCP3422_Sequencer = 0; 
//    ADC_MCP3422_Disable_Auto_Conversion();
//    init_ADC_MCP3422(); 
    
    ////////////////////////////////////////////////////////////////////////////
    // Magnetometer
    //Write_1_reg_I2C(MAG_MMC5983_ID,0x0B,0x00);// disable auto meas
    buffer[0] = 0x0B;
    buffer[1] = 0x00;
    MAG_MMC5983MA_Write_data_SPI(buffer, 2); 
    
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Fill_Data_Array(uint8_t *input, uint8_t *output, uint8_t pointer, uint8_t length)
{
    uint8_t i; 
    
    for(i=0;i<length;i++)
    {
        output[pointer++] = input[i]; 
    }
}
/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void Save_To_RAM(uint8_t *input, uint8_t length)
{
    
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void Get_Voltage_3V3_5V(void)
{
    /* Voltage calculation
     * R1 = 102K
     * R2 = 34k || 25.5k 
     * Reference = 2.048V
     * divider = R2 / (R1 + R2) = 0.125
     * LSB = 2 * Vref / 2^n == 2 * 2.048V / 2^12 = 0.001V
     * PGA = 1 (Gain)
     * Ref 2.048
     * voltage = digital value << 8; 
     */
    //uint8_t buffer[2] = {0}; 
    uint16_t voltage_formatted_3V3 = 0; 
    uint16_t voltage_formatted_5V = 0;
    uint8_t buffer[4] = {0};
    uint8_t status = 0;
    /*
     * Voltage approximate
     * CAN Voltage = 8000 to 15000
     * 5V = 4500 to 6000
     * 3.3 = 2700 to 4000
     */
    
    switch (ADC_MCP3422_Sequencer)
    {
        case 0: 
            //ADC_MCP3422_Convert_Ch1();
            //ADC_MCP3422_Sequencer++; 
            break;
        case 1: 
            
            //status = I2CSequentialReadByteDirect(buffer, VOL_MCP3422A0_ID, 0x02); 
            
            if(status == 0)
            {
                Voltage_3V3 = buffer[0] & 0x0F; 
                Voltage_3V3 = Voltage_3V3 << 8 | buffer[1]; 
                voltage_formatted_3V3 = Voltage_3V3 << 3;
                Voltage_3V3_Level_Check(voltage_formatted_3V3); 
//                buffer[0] = 0x33; 
//                buffer[1] = (voltage_formatted_3V3 & 0xFF00)>> 8; 
//                buffer[2] = voltage_formatted_3V3 & 0xFF; 
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
            }
            else
            {
                // TODO handle error
                buffer[0] = 0x33; 
                buffer[1] = 0xDE; 
                buffer[2] = 0xAD;
                buffer[3] = 0x00;
                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
            }
            
            ADC_MCP3422_Sequencer++; 
            break;
        case 2: 
            //ADC_MCP3422_Convert_Ch2();
            //ADC_MCP3422_Sequencer++; 
            break;
        case 3: 
            //status = I2CSequentialReadByteDirect(buffer, VOL_MCP3422A0_ID, 0x02); 
            
            if(status == 0)
            {
                Voltage_5V = buffer[0] & 0x0F; 
                Voltage_5V = Voltage_5V << 8 | buffer[1]; 
                voltage_formatted_5V = Voltage_5V << 3;
                Voltage_5V_Level_Check(voltage_formatted_5V);
//                buffer[0] = 0x50; 
//                buffer[1] = (voltage_formatted_5V & 0xFF00)>> 8; 
//                buffer[2] = voltage_formatted_5V & 0xFF; 
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
            }
            else
            {
                // TODO handle error
                buffer[0] = 0x50; 
                buffer[1] = 0xDE; 
                buffer[2] = 0xAD;
                buffer[3] = 0x00;
                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
            } 
            ADC_MCP3422_Sequencer++; 
        case 4: 
            ADC_MCP3422_Sequencer = 0; 
                break; 
        default: 
            ADC_MCP3422_Sequencer = 0; 
            break;
    }
    
    ////////////////////////////////////////////////////////////////////////////
//    switch (ADC_MCP3422_Sequencer)
//    {
//        case 0: 
//            ADC_MCP3422_Convert_Ch1();
//            ADC_MCP3422_Sequencer++; 
//            break;
//        case 1:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 2:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 3:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 4: 
//            //Voltage_3V3 = ADC_MCP3422_Read_Ch1(); 
//            status = I2CSequentialReadByteDirect(buffer, VOL_MCP3422A0_ID, 0x02); 
//            
//            if(status == 0)
//            {
//                Voltage_3V3 = buffer[0] & 0x0F; 
//                Voltage_3V3 = Voltage_3V3 << 8 | buffer[1]; 
//                voltage_formatted_3V3 = Voltage_3V3 << 3;
//                Voltage_3V3_Level_Check(voltage_formatted_3V3); 
//            }
//            else
//            {
//                // TODO handle error
//            }
//            
//            ADC_MCP3422_Sequencer++; 
//            break;
//        case 5:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 6:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 7:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 8: 
//            ADC_MCP3422_Convert_Ch2();
//            ADC_MCP3422_Sequencer++; 
//            break;
//        case 9:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 10:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 11:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 12: 
//            status = I2CSequentialReadByteDirect(buffer, VOL_MCP3422A0_ID, 0x02); 
//            
//            if(status == 0)
//            {
//                Voltage_5V = buffer[0] & 0x0F; 
//                Voltage_5V = Voltage_5V << 8 | buffer[1]; 
//                voltage_formatted_5V = Voltage_5V << 3;
//                Voltage_5V_Level_Check(voltage_formatted_5V);
//            }
//            else
//            {
//                // TODO handle error
//            } 
//            
//            
//            // Table result
//            // 9V == 0x2350 ==> 9040 
//            // 6V == 0x17B0 ==> 6064
//            
//            //voltage_formatted_3V3 = Voltage_3V3;
//            //voltage_formatted_5V = Voltage_5V;
//            
////            buffer[0] = (voltage_formatted_5V & 0xFF00)>> 8; 
////            buffer[1] = voltage_formatted_5V & 0xFF; 
////            buffer[2] = (voltage_formatted_3V3 & 0xFF00)>> 8; 
////            buffer[3] = voltage_formatted_3V3 & 0xFF; 
////            CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//            
////            buffer[0] = (voltage_formatted_3V3 & 0xFF00)>> 8; 
////            buffer[1] = voltage_formatted_3V3 & 0xFF; 
////            CAN_Encode_Sending(0x1B,0xC4, buffer, 2); // debug
//            
////            if(voltage_formatted_5V > 5000)
////            {
////                Debug_PIN_TX1 = 1;
////            }
////            else
////            {
////                Debug_PIN_TX1 = 0;
////            }
//            
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 13:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 14:
//            ADC_MCP3422_Sequencer++;
//            break;
//        case 15:
//            ADC_MCP3422_Sequencer++;
//            break;
//        default: 
//            ADC_MCP3422_Sequencer = 0; 
//            break;
//    }
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void Voltage_5V_Level_Check(uint16_t volt5V)
{
    //Debug_PIN_TX1 = !Debug_PIN_TX1;
    uint8_t buffer[5] = {0};
    Sum_Voltage_5V += volt5V; 
    
    Avg_Voltage_5V_Pointer++; 
    
    if(Avg_Voltage_5V_Pointer >= NumberSampleVoltAwg)
    {
        Avg_Voltage_5V_Pointer = 0; 
        
        Avg_Voltage_5V = Sum_Voltage_5V >> NumberSampleVoltDivisor; 
        
        Sum_Voltage_5V = 0; 
        
        /***********************************************************************
         // CAN voltage detected
         **********************************************************************/ 
        if(Avg_Voltage_5V >= CAN_VOLTAGE_ABOVE_THRESH)
        {

            if(Volt_5V_Flags.Vol_CAN_Above_Sent == 0)
            {
//                //Volt_5V_Flags.All_Flags = 0; 
//                //Volt_5V_Flags.Vol_CAN_Above_Sent = 1; 
//                Volt_5V_Flags.Vol_CAN_Above_Sent = 1; 
//                Volt_5V_Flags.Vol_Drill_Above_Sent = 0;
//                Volt_5V_Flags.Vol_Drill_Below_Sent = 0; 
//                CAN_Enable = 1; 
//                while(CAN_Enable != 1)
//                {
//                    CAN_Enable = 1; 
//                }
//                
//                buffer[0] = 0x50; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x75;
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//                
//                #ifdef Uart1_Debug_Message
//                    buffer[0] = 0x50; 
//                    buffer[1] = 0xBE; 
//                    buffer[2] = 0x11;
//                    buffer[3] = 0x75;
//                    write_string_uart_1(buffer, 4);
//                #endif
//                if(State_Flags.Drill_125Hz_State == 1)
//                {
//                    // Stop drilling
//                    //Init_Idle_State();
//                    State_Machine_Reset();
//                    State_Flags.Idle_State = 1;
//                    Disabled_All_Sensors();
//                }
//                else
//                {
//                    if(State_Flags.Idle_State != 1)
//                    {
//                        State_Machine_Reset(); 
//                        State_Flags.Idle_State = 1; 
//                    }
//                }
            }
        }
        /***********************************************************************
         // Drilling - 5V detected
         **********************************************************************/
        else if((Avg_Voltage_5V > DRILLING_VOLTAGE_ABOVE_THRESH) && 
                 Avg_Voltage_5V < DRILLING_VOLTAGE_MAX_THRESH)
        {
            if(Volt_5V_Flags.Vol_Drill_Above_Sent == 0)
            {
//                CAN_Enable = 0;
//                while(CAN_Enable != 0)
//                {
//                    CAN_Enable = 0; 
//                }
//                //Volt_5V_Flags.All_Flags = 0; 
//                //Volt_5V_Flags.Vol_Drill_Above_Sent = 1; 
//                Volt_5V_Flags.Vol_CAN_Above_Sent = 0; 
//                Volt_5V_Flags.Vol_Drill_Above_Sent = 1;
//                Volt_5V_Flags.Vol_Drill_Below_Sent = 0; 
//                buffer[0] = 0x50; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x50;
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//                
//                #ifdef Uart1_Debug_Message
//                buffer[0] = 0x50; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x50;
//                write_string_uart_1(buffer, 4);
//                #endif
//
//                if(Volt_3V3_Flags.Vol_3V3_Normal_Sent == 1)
//                {
//                    if(State_Flags.Drill_125Hz_State == 0)
//                    {
//                        // Start drilling routine
//                        State_Machine_Reset();
//                        State_Flags.Drill_125Hz_State = 1;
//                        Init_Drill_State();
//                    }
//                }
                 
            }
            
        }
        /***********************************************************************
         // 5V low voltage => No drilling
         **********************************************************************/
        else if(Avg_Voltage_5V < DRILLING_VOLTAGE_BELOW_THRESH)
        {
            if(Volt_5V_Flags.Vol_Drill_Below_Sent == 0)
            {
//                CAN_Enable = 0;
//                while(CAN_Enable != 0)
//                {
//                    CAN_Enable = 0; 
//                }
//                //Volt_5V_Flags.All_Flags = 0; 
//                Volt_5V_Flags.Vol_CAN_Above_Sent = 0; 
//                Volt_5V_Flags.Vol_Drill_Above_Sent = 0;
//                Volt_5V_Flags.Vol_Drill_Below_Sent = 1; 
//                buffer[0] = 0x50; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x40;
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//                
//                #ifdef Uart1_Debug_Message
//                buffer[0] = 0x50; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x50;
//                write_string_uart_1(buffer, 4);
//                #endif
//
//                if(State_Flags.Drill_125Hz_State == 1)
//                {
//                    // Stop drilling
//                    State_Machine_Reset(); 
//                    State_Flags.Idle_State = 1; 
//                    Disabled_All_Sensors();
//                }
//                else
//                {
//                    if(State_Flags.Idle_State != 1)
//                    {
//                        State_Machine_Reset(); 
//                        State_Flags.Idle_State = 1; 
//                    }
//                    
//                }
            }
        }
    }
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void Voltage_3V3_Level_Check(uint16_t volt3V3)
{

    uint8_t buffer[4] = {0};
    
    Sum_Voltage_3V3 += volt3V3; 
    
//    buffer[0] = 0x33; 
//    buffer[1] = Sum_Voltage_3V3 >> 8; 
//    buffer[2] = Sum_Voltage_3V3;
//    buffer[3] = Avg_Voltage_3V3_Pointer;
//    buffer[4] = 0x01;
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 5); // debug
    
    Avg_Voltage_3V3_Pointer++; 
    
    if(Avg_Voltage_3V3_Pointer >= NumberSampleVoltAwg)
    {
        
        Avg_Voltage_3V3_Pointer = 0; 
        
        Avg_Voltage_3V3 = Sum_Voltage_3V3 >> NumberSampleVoltDivisor; 
        
//        buffer[0] = 0x33; 
//        buffer[1] = Sum_Voltage_3V3 >> 8; 
//        buffer[2] = Sum_Voltage_3V3;
//        buffer[3] = Avg_Voltage_3V3 >> 8;
//        buffer[4] = Avg_Voltage_3V3;
//        buffer[5] = 0x02;
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
        
        Sum_Voltage_3V3 = 0; 
                
        /***********************************************************************
         // CAN voltage detected
         **********************************************************************/
        if(Avg_Voltage_3V3 > CAN_VOLTAGE_ABOVE_THRESH)
        {
            if(Volt_3V3_Flags.Vol_3V3_CAN_Sent == 0)
            {
//                //Volt_3V3_Flags.All_Flags = 0; 
//                Volt_3V3_Flags.Vol_3V3_Below_Sent = 0; 
//                Volt_3V3_Flags.Vol_3V3_CAN_Sent = 1; 
//                Volt_3V3_Flags.Vol_3V3_Normal_Sent = 0; 
//                Volt_3V3_Flags.Vol_3V3_Over_Sent = 0; 
//                //Volt_3V3_Flags.Vol_3V3_CAN_Sent = 1; 
//                buffer[0] = 0x33; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x75;
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//                #ifdef Uart1_Debug_Message
//                buffer[0] = 0x33; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x75;
//                write_string_uart_1(buffer, 4);
//                #endif
//                
//                if(State_Flags.Drill_125Hz_State == 1)
//                {
//                    // Stop drilling
//                    State_Machine_Reset(); 
//                    State_Flags.Idle_State = 1; 
//                    Disabled_All_Sensors();
//
//                }
//                else
//                {
//                    if(State_Flags.Idle_State != 1)
//                    {
//                        State_Machine_Reset(); 
//                        State_Flags.Idle_State = 1; 
//                    }
//                }
            }
            
            
        }
        /***********************************************************************
         // No more 3V3, then 5V take over
         **********************************************************************/
//        else if((Avg_Voltage_3V3 > BAT_3V3_VOLTAGE_OVERRIDED_THRESH) &&
//                (Avg_Voltage_3V3 < CAN_VOLTAGE_ABOVE_THRESH)) 
//        if((Avg_Voltage_3V3 < CAN_VOLTAGE_ABOVE_THRESH) &&
//                (Avg_Voltage_3V3 > BAT_3V3_VOLTAGE_OVERRIDED_THRESH)) 
        if(Avg_Voltage_3V3 < CAN_VOLTAGE_ABOVE_THRESH)
        {
//            if(Avg_Voltage_3V3 > BAT_3V3_VOLTAGE_OVERRIDED_THRESH)
//            {
//                //Debug_PIN_TX1 = 0;
//                
//                //// 7500 > voltage 3V3 > 4500
//                if(Volt_3V3_Flags.Vol_3V3_Over_Sent == 0)
//                {
//                    //Volt_3V3_Flags.All_Flags = 0; 
//                    //Volt_3V3_Flags.Vol_3V3_Over_Sent = 1; 
//                    Volt_3V3_Flags.Vol_3V3_Below_Sent = 0; 
//                    Volt_3V3_Flags.Vol_3V3_CAN_Sent = 0; 
//                    Volt_3V3_Flags.Vol_3V3_Normal_Sent = 0; 
//                    Volt_3V3_Flags.Vol_3V3_Over_Sent = 1; 
////                    buffer[0] = 0x33; 
////                    buffer[1] = 0xBE; 
////                    buffer[2] = 0x11;
////                    buffer[3] = 0x50;
////                    CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
////                    #ifdef Uart1_Debug_Message
////                    buffer[0] = 0x33; 
////                    buffer[1] = 0xBE; 
////                    buffer[2] = 0x11;
////                    buffer[3] = 0x50;
////                    write_string_uart_1(buffer, 4);
////                    #endif
//
//
//                    if(State_Flags.Drill_125Hz_State == 1)
//                    {
//                        // Stop drilling
//                        State_Machine_Reset(); 
//                        State_Flags.Idle_State = 1; 
//                        Disabled_All_Sensors();
//                    }
//                    else
//                    {
//                        if(State_Flags.Idle_State != 1)
//                        {
//                            State_Machine_Reset(); 
//                            State_Flags.Idle_State = 1; 
//                        }
//                    }
//
//
//                }
//            }
            
        }
        /***********************************************************************
         // normal battery power
         **********************************************************************/
//        if ((Avg_Voltage_3V3 < BAT_3V3_VOLTAGE_HIGH_THRESH) &&
//                (Avg_Voltage_3V3 > BAT_3V3_VOLTAGE_LOW_THRESH)) 
        if (Avg_Voltage_3V3 < BAT_3V3_VOLTAGE_HIGH_THRESH)
        {
//            if (Avg_Voltage_3V3 > BAT_3V3_VOLTAGE_LOW_THRESH)
//            {
//                //Debug_PIN_TX1 = 1;
//                //// 4500 > voltage 3V3 > 4500
//                if(Volt_3V3_Flags.Vol_3V3_Normal_Sent == 0)
//                {
//                    //Volt_3V3_Flags.All_Flags = 0; 
//                    //Volt_3V3_Flags.Vol_3V3_Normal_Sent = 1; 
//                    Volt_3V3_Flags.Vol_3V3_Below_Sent = 0; 
//                    Volt_3V3_Flags.Vol_3V3_CAN_Sent = 0; 
//                    Volt_3V3_Flags.Vol_3V3_Normal_Sent = 1; 
//                    Volt_3V3_Flags.Vol_3V3_Over_Sent = 0; 
////                    buffer[0] = 0x33; 
////                    buffer[1] = 0xBE; 
////                    buffer[2] = 0x11;
////                    buffer[3] = 0x33;
////                    CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
////                    #ifdef Uart1_Debug_Message
////                    buffer[0] = 0x33; 
////                    buffer[1] = 0xBE; 
////                    buffer[2] = 0x11;
////                    buffer[3] = 0x33;
////                    write_string_uart_1(buffer, 4);
////                    #endif
//
//                    if(Volt_5V_Flags.Vol_Drill_Above_Sent == 1)
//                    {
//                        if(State_Flags.Drill_125Hz_State == 0)
//                        {
//                            // Start drilling routine
//                            State_Machine_Reset();
//                            State_Flags.Drill_125Hz_State = 1;
//                            Init_Drill_State();
//                        }
//                    }
//                }
//            }
        }
        /***********************************************************************
         // Alert battery dead soon 
         **********************************************************************/
        if(Avg_Voltage_3V3 < BAT_3V3_VOLTAGE_MIN_THRESH)
        {
            
//            if(Volt_3V3_Flags.Vol_3V3_Below_Sent == 0)
//            {
//                //Volt_3V3_Flags.All_Flags = 0; 
//                //Volt_3V3_Flags.Vol_3V3_Below_Sent = 1;  
//                Volt_3V3_Flags.Vol_3V3_Below_Sent = 1; 
//                Volt_3V3_Flags.Vol_3V3_CAN_Sent = 0; 
//                Volt_3V3_Flags.Vol_3V3_Normal_Sent = 0; 
//                Volt_3V3_Flags.Vol_3V3_Over_Sent = 0; 
//                buffer[0] = 0x33; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x28;
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
//                #ifdef Uart1_Debug_Message
//                buffer[0] = 0x33; 
//                buffer[1] = 0xBE; 
//                buffer[2] = 0x11;
//                buffer[3] = 0x28;
//                write_string_uart_1(buffer, 4);
//                #endif
//                
//                if(State_Flags.Drill_125Hz_State == 1)
//                {
//                    // Stop drilling
//                    State_Machine_Reset(); 
//                    State_Flags.Idle_State = 1; 
//                    Disabled_All_Sensors();
//                }
//                else
//                {
//                    if(State_Flags.Idle_State != 1)
//                    {
//                        State_Machine_Reset(); 
//                        State_Flags.Idle_State = 1; 
//                    }
//                }
//            }
            

        }
//        else
//        {
//            
//        }
    }
}
/*******************************************************************************
 * Function: Set_Burst_Array
 * Parameters: uint8_t *data, uint8_t length
 * Return: none
 * Description: Store data in ram buffer
 ******************************************************************************/
void Set_Burst_Array(uint8_t *data, uint8_t length)
{
    //uint8_t packet_buffer[9];
    //uint8_t status = 0; 
    uint16_t i; 
    uint16_t crc;

    /***************************************************************************
    * Write the header                                         
    ***************************************************************************/
    if(Burst_Sequencer == 0)
    {
        
//        Buffer_Burst[0] = 0xA7; 
//        Buffer_Burst[1] = Time.days; 
//        Buffer_Burst[2] = Time.hours; 
//        Buffer_Burst[3] = Time.minutes; 
//        Buffer_Burst[4] = Time.seconds; 
//        Buffer_Burst[5] = (Time.miliseconds & 0xFF00) >> 8; 
//        Buffer_Burst[6] = Time.miliseconds & 0x00FF; 
//        Buffer_Burst[7] = (Gyro_value & 0xFF00) >> 8; 
//        Buffer_Burst[8] = Gyro_value & 0x00FF;
//        Buffer_Burst[9] = data[0]; 
//        Buffer_Burst[10] = data[1]; 
//        Buffer_Burst[11] = data[2]; 
//        Buffer_Burst[12] = data[3]; 
//        Buffer_Burst[13] = data[4];
        
        Buffer_Burst[0] = 0xC7; 
        Buffer_Burst[1] = Time.days; 
        Buffer_Burst[2] = Time.hours; 
        Buffer_Burst[3] = Time.minutes; 
        Buffer_Burst[4] = Time.seconds; 
        Buffer_Burst[5] = (Time.miliseconds & 0xFF00) >> 8; 
        Buffer_Burst[6] = Time.miliseconds & 0x00FF; 
        Buffer_Burst[7] = (Gyro_value & 0xFF00) >> 8; 
        Buffer_Burst[8] = Gyro_value & 0x00FF;
        Buffer_Burst[9] = data[0]; 
        Buffer_Burst[10] = data[1]; 
        Buffer_Burst[11] = data[2]; 
        Buffer_Burst[12] = data[3]; 
        Buffer_Burst[13] = data[4];
        
        Burst_Sequencer = 3;

    }
    /***************************************************************************
    * Write part 1 (8 bytes) of data packet                                        
    ***************************************************************************/
    else if(Burst_Sequencer == 1)
    {
//        Buffer_Burst[0] = 0xA8; // header
//        Buffer_Burst[1] = data[0]; 
//        Buffer_Burst[2] = data[1]; 
//        Buffer_Burst[3] = data[2]; 
//        Buffer_Burst[4] = data[3]; 
//        Buffer_Burst[5] = data[4];
//        Buffer_Burst[6] = (Gyro_value & 0x0FF0) >> 4;
//        Buffer_Burst[7] = (Gyro_value & 0x000F) << 4;
        
        Buffer_Burst[0] = 0xC8; // header
        Buffer_Burst[1] = (Gyro_value & 0xFF00) >> 8;
        Buffer_Burst[2] = Gyro_value & 0x00FF;
        Buffer_Burst[3] = data[0]; 
        Buffer_Burst[4] = data[1]; 
        Buffer_Burst[5] = data[2]; 
        Buffer_Burst[6] = data[3]; 
        Buffer_Burst[7] = data[4] & 0xF0;
        Burst_Sequencer += 1;
            
    }
    else if(Burst_Sequencer == 2)
    {
        Buffer_Burst[7] |= (data[4] & 0xF0) >> 4;
        Buffer_Burst[8] = data[0];
        Buffer_Burst[9] = data[1]; 
        Buffer_Burst[10] = data[2]; 
        Buffer_Burst[11] = data[3]; 
        Buffer_Burst[12] = (Gyro_value & 0xFF00) >> 8; 
        Buffer_Burst[13] = Gyro_value & 0x00FF;
        Burst_Sequencer += 1;
    }
    
    
    /***************************************************************************
    * Writing to big RAM array                                      
    ***************************************************************************/
    if(Burst_Sequencer == 3)
    {
        // write CRC
        crc = CRC_ChecksumByte(Buffer_Burst, 14, 0x00); 
        Buffer_Burst[14] = (crc & 0xFF00) >> 8; 
        Buffer_Burst[15] = crc & 0x00FF;
        
        // write to buffer
        
        if(State_Flags.Burst_State_Old == 0)
        {
            // with backup for old data
            for(i=0; i<16;i++)
            {
                //BurstBuffer32[BurstBuffer32_Pointer++] = Buffer_Burst[i]; 
                Buffer_RAM_Before[Buffer_RAM_Before_Pointer++] = Buffer_Burst[i];
                BurstBuffer256_Before_Pointer++; 
            }
            
            if(BurstBuffer256_Before_Pointer >= BurstBuffer256_Pointer_Max)
            {
                 Burst_Before_Pointer += 1; 
                 if(Burst_Before_Pointer >= BurstBuffer256_Slice_Max) 
                 {
                     // roll over 
                     Buffer_RAM_Before_Pointer = 0; 
                     Burst_Before_Pointer = 0; 

                 }
                // roll over array 
                BurstBuffer256_Before_Pointer = 0; 
                //Burst_Pointer = 0;
                Burst_Sequencer = 0; 

                // write to 
            }
            else
            {
               Burst_Sequencer = 1; 
            }  
        }
        else
        {
            // with backup for old data
            if(State_Flags.Burst_State_New == 0)
            {
                for(i=0; i<16;i++)
                {
                    //BurstBuffer32[BurstBuffer32_Pointer++] = Buffer_Burst[i]; 
                    Buffer_RAM_After[Buffer_RAM_After_Pointer++] = Buffer_Burst[i];
                    BurstBuffer256_After_Pointer++; 
                }
                if(BurstBuffer256_After_Pointer >= BurstBuffer256_Pointer_Max)
                {
                     Burst_After_Pointer += 1; 
                     if(Burst_After_Pointer >= BurstBuffer256_Slice_Max) 
                     {
                         State_Flags.Burst_State_New = 1; 
                         // do not roll over 
                         //Buffer_RAM_Before_Pointer = 0; 
                         //Burst_Pointer = 0; 

                     }
                    // roll over array 
                    BurstBuffer256_After_Pointer = 0; 
                    //Burst_Pointer = 0;
                    Burst_Sequencer = 0; 

                    // write to 
                }
                else
                {
                   Burst_Sequencer = 1; 
                } 
            }
             
            
        }
        
        
        
         
    }
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void Set_Burst_Writing(void)
{
    uint8_t buffer[32] = {0};
    uint8_t i;
    
    if(State_Flags.Burst_State == 1 && State_Flags.Burst_Init_State == 0)
    {
        State_Flags.Burst_Init_State = 1; 
        State_Flags.Burst_State_Old = 1; 
        State_Flags.Burst_State_New = 0; 
        Buffer_Write_Before_Pointer = 0; 
        Buffer_Write_After_Pointer = 0; 
        Buffer_RAM_After_Pointer = 0; 
//        // find right place pointer -> right slice of 256 bytes to get time stamp right
//        if((Burst_Before_Pointer > 0) && (Burst_Before_Pointer <= BurstBuffer256_Slice_Max-1))
//        {
//            Buffer_Write_Before_Pointer = (Burst_Before_Pointer) + 1; 
//            
//        }
//        else if(Burst_Before_Pointer == BurstBuffer256_Slice_Max)
//        {
//            Buffer_Write_Before_Pointer = 0; 
//        }
//        else
//        {
//            Buffer_Write_Before_Pointer = 0; 
//        }

    }
    
    if(State_Flags.Burst_State_Old == 1)
    {
        for(i=0; i < 32; i++)
        {
            buffer[i] = Buffer_RAM_Before[Buffer_Write_Before_Pointer++]; 
            //Buffer_Write_Counter++; 
        }
        MEM_MT25QL01_Write_Bytes(MT25QL01_In_Used, buffer, 32); // write to memory
        
        if(Buffer_Write_Before_Pointer >= Buffer_Write_Pointer_Max)
        {
            State_Flags.Burst_State_Old = 0; 
            BurstBuffer256_Before_Pointer = 0;
            Burst_Before_Pointer = 0; 
            Buffer_Write_Before_Pointer = 0; 
            Buffer_RAM_Before_Pointer = 0; 
        }
    }
    else
    {
        if(State_Flags.Burst_State_New == 1)
        {
            for(i=0; i < 32; i++)
            {
                buffer[i] = Buffer_RAM_After[Buffer_Write_After_Pointer++]; 
                //Buffer_Write_Counter++; 
            }
            MEM_MT25QL01_Write_Bytes(MT25QL01_In_Used, buffer, 32); // write to memory
            
            if(Buffer_Write_After_Pointer >= Buffer_Write_Pointer_Max)
            {
                //Buffer_Write_Counter = 0; 
                State_Flags.Burst_State = 0; 
                State_Flags.Burst_Init_State = 0; 
                Buffer_RAM_After_Pointer = 0; 
                Buffer_Write_Before_Pointer = 0;  // to write to memory
                Buffer_Write_After_Pointer = 0;  // to write to memory
                //Burst_Before_Pointer = 0; 
                Burst_After_Pointer = 0;
                //BurstBuffer256_Before_Pointer = 0;
                BurstBuffer256_After_Pointer = 0;
                State_Flags.Burst_Paused = 1; 
            }
        }
    }
    

    
   
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void Save_Super_Burst(uint8_t *data)
{
    
}
/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void RTOS_50us_Routine_250Hz(void)
{
    uint8_t status = 0; 
    uint8_t i;
    uint8_t buffer[16] = {0}; 
    //uint8_t tempo_buf[5] = {0}; 
    uint8_t cmd[1] = {0};
    uint16_t tempo16; 
    uint16_t voltage_formatted_3V3 = 0; 
    uint16_t voltage_formatted_5V = 0;
    //uint32_t tempo32; 
    switch(RTOS_50us_Seguencer)
    {
        case RTOS_50us_Step_1ms:
            
            //Debug_PIN_TX1 = 1;
            switch (RTOS_50us_Counter)
            {
                
                ////////////////////////////////////////////////
                case 0: // ADC Gyro - 100us
                    Gyro_value = ADC_ADS868x_READ_DATA(SPI_CS_GYRO); 

                    break;
                ////////////////////////////////////////////////    
                case 1: // Accel HG
                    // ~ 100 us
                    // 7 registers reading => 76us
                    // 25 registers reading => 256us
                    //Debug_PIN_TX1 = 0;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer); 
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5); 

                    break;
                ////////////////////////////////////////////////    
                case 2: // Accel LG1
                    // 150us
                    cmd[0] = (ACC355_TEMP2 << 1) | 0x01;
                    ADXL355_SPI_Get_Data(SPI_CS_ACC_LG1, cmd, 1, buffer, 11); 
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 11); // debug
                    for(i=0; i<11;i++)
                    {
                        Accel_LG1_Data[i] = buffer[i]; 
                    }
        
                    
                    break;
                ////////////////////////////////////////////////    
                case 3: // voltage reading 
                    // ~150us
                    if(ADC_MCP3422_Sequencer == 0)
                    {
                        Voltage_3V3 = ADC_ADS863x_READ_DATA(SPI_CS_VOLT, 1); 
                        //voltage_formatted_3V3 = Voltage_3V3 << 2;
                        ADC_MCP3422_Sequencer++;
                    }
                    else if(ADC_MCP3422_Sequencer == 60)
                    {
                        Voltage_5V = ADC_ADS863x_READ_DATA(SPI_CS_VOLT, 0); 
                        //voltage_formatted_5V = Voltage_5V << 2;
                        ADC_MCP3422_Sequencer++;
                    }
                    else
                    {
                        ADC_MCP3422_Sequencer++;
                        if(ADC_MCP3422_Sequencer>= 120)
                        {
                            ADC_MCP3422_Sequencer = 0; 
                        }
                    }
                    break;

            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 11) //
            {
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0; 
                RTOS_50us_Seguencer += 1; 
            }
            
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        case RTOS_50us_Step_2ms :
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro - 100us
                    //Debug_PIN_TX1 = 1;
                    Gyro_value = ADC_ADS868x_READ_DATA(SPI_CS_GYRO); 

                    break;
                ////////////////////////////////////////////////  
                case 1: // 100us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer); 
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;

                ////////////////////////////////////////////////
                case 2: // 150us -> Accel LG2
                    cmd[0] = (ACC355_TEMP2 << 1) | 0x01;
                    ADXL355_SPI_Get_Data(SPI_CS_ACC_LG2, cmd, 1, buffer, 11); 
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 11); // debug
                    for(i=0; i<11;i++)
                    {
                        Accel_LG2_Data[i] = buffer[i]; 
                    }
                    break;

                ///////////////////////////////////////////////
                case 3: // Magnetometer - 100us
                    MAG_MMC5983MA_Get_data_SPI(buffer, 6);
                    for(i=0; i<6;i++)
                    {
                        Magneto_Data[i] = buffer[i]; 
                    }
                    break;

                ///////////////////////////////////////////////

            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 11)
            {
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0;
                RTOS_50us_Seguencer += 1; 
            }
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        case RTOS_50us_Step_3ms:
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro - 56us
                    Debug_PIN_TX1 = 1;
                    Gyro_value = ADC_ADS868x_READ_DATA(SPI_CS_GYRO); 

                    break;
                ////////////////////////////////////////////////    
                case 1: // 100us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    //ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ////////////////////////////////////////////////
                case 2: // 800us -> // burst writing if needed
                    if(State_Flags.Burst_State == 1 && State_Flags.Burst_Paused == 0)
                    {
                        Set_Burst_Writing();
                        RTOS_50us_Counter = 15; // bypass delay
                    }
                    else
                    {
                        
                        Calculation_TF(); 
                        
                        if(State_Flags.Burst_Paused == 1)
                        {
                            Burst_Pause_Delay_counter++;
                            if(Burst_Pause_Delay_counter >= Burst_Pause_Delay_max_count)
                            {
                                Burst_Pause_Delay_counter = 0; 
                            }
                        }
                    }
                    break;

            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 7)
            {
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0;
                RTOS_50us_Seguencer += 1; 
            }
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        case RTOS_50us_Step_4ms :
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro - 100us
                    Gyro_value = ADC_ADS868x_READ_DATA(SPI_CS_GYRO); 

                    break;
                ////////////////////////////////////////////////   
                case 1: // Accel HG - 100us
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;

                ///////////////////////////////////////////////
                case 2: // Writting to memory 750us
                    // 732us (SPI is 400us + 300us writing)
                    //Debug_PIN_TX1 = 1;
                    Fill_Array_For_Writing(); 
                    //Debug_PIN_TX1 = 0;
                    break;
                ///////////////////////////////////////////////

            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 15)
            {
                //Debug_PIN_TX1 = 0;
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                RTOS_50us_Counter = 0;
                RTOS_50us_Seguencer = 0; // reset

            }
            
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////    
       
        default:
            RTOS_50us_Counter = 0;
            RTOS_50us_Seguencer = 0; // reset
            break;
    }
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: none
 * Description: 
 ******************************************************************************/
void RTOS_50us_Routine_125Hz(void)
{
    uint8_t status = 0; 
    uint8_t i;
    uint8_t buffer[16] = {0}; 
    //uint8_t tempo_buf[5] = {0}; 
    uint8_t cmd[1] = {0};
    uint16_t tempo16; 
    //uint16_t gyro_raw_value_Unsigned = 0; 
    uint16_t voltage_formatted_3V3 = 0; 
    uint16_t voltage_formatted_5V = 0;
    
    //uint16_t gyro_Vol_Ref_Unsigned = 0 ; 
    //int16_t gyro_raw_value_Signed; 
    //int16_t gyro_Vol_Ref_Signed; 
    //uint32_t tempo32; 
    switch(RTOS_50us_Seguencer)
    {
        case RTOS_50us_Step_1ms:
            
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                ////////////////////////////////////////////////    
                case 1: // Accel HG
                    // ~ 100 us
                    // 7 registers reading => 76us
                    // 25 registers reading => 256us
                    //Debug_PIN_TX1 = 0;
                    //status = ADXL373_Read_Fifo(ADXL373_FIFO);
//                    if(status > 2)
//                    {
//                        State_Flags.Super_Burst_Rec = 1; 
//                    }
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer); 
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5); 
                    
                            
                    
                    //cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    //ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    //ADXL373_SPI_Check_Level(buffer); 
                    //ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    //Set_Burst_Array(Accel_HG_Data,5); 
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ////////////////////////////////////////////////    
//                case 2: // voltage reading 
//                    // ~150us
//                    // 3-5 registers reading => 71 to 133us
//                    
//                    switch (ADC_MCP3422_Sequencer)
//                    {
//                        case 16:
//                            ADC_MCP3422_Convert_Ch1();
//                            break;
//                        case 32: // 250ms / 8ms
//                            //Voltage_3V3 = ADC_MCP3422_Read_Ch1(); 
//                            status = I2CSequentialReadByteDirect(buffer, VOL_MCP3422A0_ID, 0x02); 
//
//                            if(status == 0)
//                            {
//                                Voltage_3V3 = buffer[0] & 0x0F; 
//                                Voltage_3V3 = Voltage_3V3 << 8 | buffer[1]; 
//                                voltage_formatted_3V3 = Voltage_3V3 << 3;
//                                Voltage_3V3_Level_Check(voltage_formatted_3V3); 
//                            }
//                            else
//                            {
//                                buffer[0] = 0xEE; 
//                                buffer[1] = 0x05; 
//                                CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
//                                I2C_Errors_Flags |= I2C_Volt_Read_3V3_Error; 
//                                I2C_Errors_Counter++;
//                            }
//                            break;
//                        case 48:
//                            ADC_MCP3422_Convert_Ch2();
//                            break;
//                        case 64: // 250ms / 8ms
//                            status = I2CSequentialReadByteDirect(buffer, VOL_MCP3422A0_ID, 0x02); 
//
//                            if(status == 0)
//                            {
//                                Voltage_5V = buffer[0] & 0x0F; 
//                                Voltage_5V = Voltage_5V << 8 | buffer[1]; 
//                                voltage_formatted_5V = Voltage_5V << 3;
//                                Voltage_5V_Level_Check(voltage_formatted_5V);
//                            }
//                            else
//                            {
//                                buffer[0] = 0xEE; 
//                                buffer[1] = 0x07; 
//                                CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
//                                I2C_Errors_Flags |= I2C_Volt_Read_5V_Error; 
//                                I2C_Errors_Counter++;
//                            } 
//                            ADC_MCP3422_Sequencer = 0; 
//                            break;
//                        default: 
//                            //ADC_MCP3422_Sequencer = 0; 
//                            //ADC_MCP3422_Sequencer++; 
//                            break;
//                    }
//                    
//                    ADC_MCP3422_Sequencer++;
//                    break;
                ////////////////////////////////////////////////    

                     
                     
            }
            RTOS_50us_Counter += 1; 
            //if(RTOS_50us_Counter >= 8) // with voltage reading
            if(RTOS_50us_Counter >= 11) // no voltage reading
            {
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0; 
                RTOS_50us_Seguencer += 1; 
            }
            
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        case RTOS_50us_Step_2ms :
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                //////////////////////////////////////////////// 
                case 1: // 100us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer); 
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;

                ////////////////////////////////////////////////
                case 2: // 150us -> Accel LG1
                    cmd[0] = (ACC355_TEMP2 << 1) | 0x01;
                    ADXL355_SPI_Get_Data(SPI_CS_ACC_LG1, cmd, 1, buffer, 11); 
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 11); // debug
                    for(i=0; i<11;i++)
                    {
                        Accel_LG1_Data[i] = buffer[i]; 
                    }
                    break;
                ////////////////////////////////////////////////   
                case 3: // Magneto
                    MAG_MMC5983MA_Get_data_SPI(buffer, 6); 
                    for(i=0; i<6;i++)
                    {
                        Magneto_Data[4] = buffer[i]; 
                    }
                    break;
      
            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 4)
            {
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0;
                RTOS_50us_Seguencer += 1; 
            }
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        case RTOS_50us_Step_3ms:
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                ////////////////////////////////////////////////   
                case 1: // 100us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    //ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ////////////////////////////////////////////////
                case 3: // 800us -> // burst writing if needed
                    // //LEDR = !LEDR; // LED green
                    
                    if(State_Flags.Burst_State == 1)
                    {
                        debug_LED_counter++; 
                        if(debug_LED_counter > debug_LED_Burst_Fast_max_count)
                        {
                            //LEDR = !LEDR;
                            //Debug_PIN_TX1 = !Debug_PIN_TX1;
                            debug_LED_counter = 0; 
                        }
                        Set_Burst_Writing();
                        RTOS_50us_Counter = 15; // bypass delay
                    }
                    else
                    {
                        debug_LED_counter++; 
                        if(debug_LED_counter > debug_LED_Burst_max_count)
                        {
                            //Debug_PIN_TX1 = !Debug_PIN_TX1;
                            //LEDR = !LEDR;
                            debug_LED_counter = 0; 
                        }
                    }
//                    if(State_Flags.Burst_State == 1 && State_Flags.Burst_Paused == 0)
//                    {
//                        debug_LED_counter++; 
//                        if(debug_LED_counter > debug_LED_Burst_max_count)
//                        {
//                            Debug_PIN_TX1 = !Debug_PIN_TX1;
//                            debug_LED_counter = 0; 
//                        }
//                        Set_Burst_Writing();
//                        RTOS_50us_Counter = 15; // bypass delay
//                    }
//                    else
//                    {
//                        //Debug_PIN_TX1 = !Debug_PIN_TX1;
//                        debug_LED_counter++; 
//                        if(debug_LED_counter > debug_LED_max_count)
//                        {
//                            Debug_PIN_TX1 = !Debug_PIN_TX1;
//                            debug_LED_counter = 0; 
//                        }
//                        if(State_Flags.Burst_Paused == 1)
//                        {
//                            Burst_Pause_Delay_counter++;
//                            if(Burst_Pause_Delay_counter >= Burst_Pause_Delay_max_count)
//                            {
//                                Burst_Pause_Delay_counter = 0; 
//                            }
//                        }
//                    }
     
                ///////////////////////////////////////////////
//                case 16: // Accel HG - Extra sample
//                    // ~ 100 us
//                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
//                    ADXL373_SPI_Check_Level(buffer); 
//                    break;
            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 11)
            {
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0;
                RTOS_50us_Seguencer += 1; 
            }
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        case RTOS_50us_Step_4ms :
            //Debug_PIN_TX1 = !Debug_PIN_TX1;
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                ////////////////////////////////////////////////    
                case 1: // 300us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;

            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 11)
            {
                //Debug_PIN_TX1 = 0;
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
                RTOS_50us_Counter = 0;
                RTOS_50us_Seguencer += 1; 
            }
            break;
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////    
        case RTOS_50us_Step_5ms :
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                ////////////////////////////////////////////////    
                case 1: // 300us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ///////////////////////////////////////////////
                case 2: // 300us -> Accel LG2
                    cmd[0] = ACC355_XDATA3;
                    //status = I2CSequentialSetReadReg(buffer, ACC_ADXL355_LG2_ID, cmd[0], 9);
                    if(status == 0)
                    {
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 11); // debug 
                        //ADXL355_I2C_Data_Scan(0x1D);
//                        for(i=0; i<11;i++)
//                        {
//                            Accel_LG2_Data[i] = buffer[i]; 
//                        }
                        for(i=0; i<9;i++) //
                        {
                            // 0 = temp
                            // 1 = temp
                            // 2 = X
                            // 3 = X
                            // 4 = X
                            // 5 = Y
                            // 6 = Y
                            // 7 = Y
                            // 8 = Z
                            // 9 = Z
                            // 10 = Z
                            Accel_LG2_Data[i+2] = buffer[i]; 
                        }
                    }
                    else
                    {
                        for(i=0; i<9;i++) // 
                        {
                            Accel_LG2_Data[0] = 0x11; // error
                        }
                        I2C_Errors_Flags |= I2C_Accel_LG2_Error;
                        buffer[0] = 0xEE; 
                        buffer[1] = 0x09; 
                        CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        I2C_Errors_Counter++;
                    }
                    
                    break;
   
            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 4)
            {
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0; 
                RTOS_50us_Seguencer += 1; 
            }
            break; 
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////   
        case RTOS_50us_Step_6ms :
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                ////////////////////////////////////////////////     
                case 1: // 300us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ////////////////////////////////////////////////    
                 case 2:
                    // getting fu** face 
                    Calculation_TF(); 
                    break;
                //////////////////////////////////////////////// 
                    
                    
//                case 2: // Accel LG3
//                    // 300us
//                    // 3-5 registers reading => 133us
//                    cmd[0] = ACC355_YDATA3;
//                    status = I2CSequentialSetReadReg(buffer, ACC_ADXL355_LG3_ID, cmd[0], 6);
//                    if(status == 0)
//                    {
//                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 11); // debug
////                        for(i=0; i<11;i++)
////                        {
////                            Accel_LG3_Data[i] = buffer[i]; 
////                        }
//                        for(i=0; i<6;i++) // only Z axis
//                        {
//                            // 0 = temp
//                            // 1 = temp
//                            // 2 = X
//                            // 3 = X
//                            // 4 = X
//                            // 5 = Y
//                            // 6 = Y
//                            // 7 = Y
//                            // 8 = Z
//                            // 9 = Z
//                            // 10 = Z
//                            Accel_LG3_Data[i+5] = buffer[i]; 
//                        }
//                        //ADXL355_I2C_Data_Scan(ACC_ADXL355_LG2_ID);
//                    }
//                    else
//                    {
//                        for(i=0; i<6;i++) // only Z axis
//                        {
//                            Accel_LG3_Data[i+5] = 0x11; // error
//                        }
//                        I2C_Errors_Flags |= I2C_Accel_LG3_Error; 
//                        buffer[0] = 0xEE; 
//                        buffer[1] = 0x03; 
//                        CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
//                    }
//                    
//                    break;
            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 4)
            {
                //Debug_PIN_TX1 = 0;
                RTOS_50us_Counter = 0; 
                RTOS_50us_Seguencer += 1; 
            }
            break; 
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////   
        case RTOS_50us_Step_7ms :
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0: // ADC Gyro 
                    // ~ 150us - 200 us
                    // 3 registers reading => 112us
                    // 5 registers reading => 181us
                    //Debug_PIN_TX1 = 1;
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x10, 0x04); // read ch 1
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        }
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        
                    }
                    break;
                ////////////////////////////////////////////////    
                case 1: // 300us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ////////////////////////////////////////////////
                case 3: // 800us -> // burst writing if needed
                    if(State_Flags.Burst_State == 1 && State_Flags.Burst_Paused == 0)
                    {
                        Set_Burst_Writing();
                        RTOS_50us_Counter = 15; // bypass delay
                    }
                    else
                    {
                        if(State_Flags.Burst_Paused == 1)
                        {
                            Burst_Pause_Delay_counter++;
                            if(Burst_Pause_Delay_counter >= Burst_Pause_Delay_max_count)
                            {
                                Burst_Pause_Delay_counter = 0; 
                            }
                        }
                    }
                ////////////////////////////////////////////////    
            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 11)
            {
                RTOS_50us_Counter = 0; 
                RTOS_50us_Seguencer += 1; 
            }
            break; 
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////   
        case RTOS_50us_Step_8ms :
            switch (RTOS_50us_Counter)
            {
                ////////////////////////////////////////////////
                case 0:
                    //status = I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x04);
                    if(status == 0)
                    {
                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
                        Gyro_value = (tempo16 << 8) | buffer[1]; 
                        
                        tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
                        tempo16 = (tempo16 << 8) | buffer[3]; 
                        if(tempo16 > Gyro_Vol_Min_Threshold)
                        {
                            Gyro_Vol_Ref_Unsigned = tempo16; 
                        } 
                        ////////////////////////////////////////////////////////////////////////
//                        tempo16 = buffer[0] & 0x0F; // Filter 4 MSB bit
//                        tempo16 = (tempo16 << 8) | buffer[1]; 
//                        if(tempo16 == 0)
//                        {
//                            Gyro_value = 0x09C4; // 2500 ==> 0 
//                            I2C_Errors_Flags |= I2C_ADC_Gyro_Error;
//                        }
//                        else
//                        {
//                            gyro_raw_value_Unsigned = tempo16; 
//                            
//                            tempo16 = buffer[2] & 0x0F; // Filter 4 MSB bit
//                            tempo16 = (tempo16 << 8) | buffer[3]; 
//                            
//                            if(tempo16 == 0 && Gyro_Vol_Ref_Unsigned != 0)
//                            {
//                                // keep value voltage ref from last result
//                                if(gyro_raw_value_Unsigned > Gyro_Vol_Ref_Unsigned)
//                                {
//                                    Gyro_value = 2500 + gyro_raw_value_Unsigned - Gyro_Vol_Ref_Unsigned; 
//                                }
//                                else
//                                {
//                                    Gyro_value = 2500 + Gyro_Vol_Ref_Unsigned - gyro_raw_value_Unsigned; 
//                                }
//                            }
//                            else
//                            {
//                                Gyro_Vol_Ref_Unsigned = tempo16;
//                                
//                                if(gyro_raw_value_Unsigned > Gyro_Vol_Ref_Unsigned)
//                                {
//                                    Gyro_value = 2500 + gyro_raw_value_Unsigned - Gyro_Vol_Ref_Unsigned; 
//                                }
//                                else
//                                {
//                                    Gyro_value = 2500 + Gyro_Vol_Ref_Unsigned - gyro_raw_value_Unsigned; 
//                                }
//                            }
//                        }
                        ////////////////////////////////////////////////////////////////////////////////
                        
                        
                        //tempo16 = buffer[2]; 
                        //Gyro_temp = (tempo16 << 8) | buffer[3];
                        //Current_3V3 = 0; // not used yet 
                        //Current_5V = 0; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // debug
                    }
                    else
                    {
                        //buffer[0] = 0xEE; 
                        //buffer[1] = 0x0C; 
                        //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); 
                        Gyro_value = 0x09C4; // 2500 ==> 0 
                        I2C_Errors_Flags |= I2C_ADC_Gyro_Error;
                        I2C_Errors_Counter++;
                    }
                    break;
                ////////////////////////////////////////////////    
                case 1: // 300us -> Accel HG
                    cmd[0] = (ACC373_XDATA_H << 1) | 0x01;
                    ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
                    ADXL373_SPI_Check_Level(buffer);
                    ADXL373_Shift_Data(buffer,Accel_HG_Data); 
                    Set_Burst_Array(Accel_HG_Data,5);
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
                    break;
                ///////////////////////////////////////////////
                case 2: // 550us -> 
                    // 732us (SPI is 400us + 300us writing)
                    // writing to memory
                    //TestRAM[TestRAM_Pointer++] =0; 
                    //CAN_Encode_Sending(0x1B,0xC4, buffer, 11);
                    //Debug_PIN_TX1 = 1;
                    Fill_Array_For_Writing(); 
                    I2C_Errors_Flags = 0; // RESET I2C errors
                    //Debug_PIN_TX1 = 0;
                    break;
                ///////////////////////////////////////////////
            }
            RTOS_50us_Counter += 1; 
            if(RTOS_50us_Counter >= 3)
            {
                RTOS_50us_Counter = 0; 
                RTOS_50us_Seguencer = 0;  
                //Debug_PIN_TX1 = !Debug_PIN_TX1;
            }
            break; 
            
        default:
            RTOS_50us_Seguencer = 0;
            break;
    }
}
/*******************************************************************************
 * Function: Test sensor
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Fill_Array_For_Writing(void)
{
    //uint8_t i; 
    uint8_t buffer_L[16] = {0};
    uint8_t buffer_H[16] = {0};
    uint16_t crc;
    //Buffer_Burst[5] = (Time.miliseconds & 0xFF00) >> 8; 
    //Buffer_Burst[6] = Time.miliseconds & 0xFF00; 
    //buffer[0] = 0x00;
    //TestRAM[TestRAM_Pointer++] = Accel_LG3_Data[i];
    
    if(State_Flags.Drill_125Hz_State == 1)
    {
        if(Drill_Pointer == 0) // Timestamp 
        {
            /*******************************************************************
            * Packet 1a Time reference Once every 32ms
            *******************************************************************/
            //buffer_L[0] = 0xA1; // with magnetometer
            buffer_L[0] = 0xA4; // no magnetometer
            buffer_L[1] = Time.year;
            buffer_L[2] = Time.month;
            buffer_L[3] = Time.days;
            buffer_L[4] = Time.hours;
            buffer_L[5] = Time.minutes;
            buffer_L[6] = Time.seconds;
            buffer_L[7] = (Time.miliseconds & 0xFF00) >> 8;
            buffer_L[8] = Time.miliseconds & 0x00FF;
            buffer_L[9] = Accel_HG_Data[0];
            buffer_L[10] = Accel_HG_Data[1];
            buffer_L[11] = Accel_HG_Data[2];
            buffer_L[12] = Accel_HG_Data[3];
            buffer_L[13] = Accel_HG_Data[4];
            
             // write CRC
            //Debug_PIN_TX1 = 1;
            crc = CRC_ChecksumByte(buffer_L, 14, 0x00); 
            //Debug_PIN_TX1 = 0;
            buffer_L[14] = (crc & 0xFF00) >> 8; 
            buffer_L[15] = crc & 0x00FF;
            
            /*******************************************************************
            * Packet 1b Time reference Once every 32ms
            *******************************************************************/
            buffer_H[0] = (Gyro_temp & 0xFF00) >> 8;// Temp gyro MSB - 12bits
            buffer_H[1] = Gyro_temp & 0x00FF;       // Temp gyro LSB - 12bits
            buffer_H[2] = Accel_LG1_Data[0];        // temp LG1 MSB - 12bits
            buffer_H[3] = Accel_LG1_Data[1];        // temp LG1 LSB - 12bits
//            buffer_H[4] = Magneto_Data[0];
//            buffer_H[5] = Magneto_Data[1];
//            buffer_H[6] = Magneto_Data[2];
//            buffer_H[7] = Magneto_Data[3];
//            buffer_H[8] = Magneto_Data[4];
//            buffer_H[9] = Magneto_Data[5];
            buffer_H[4] = (Voltage_3V3 & 0xFF00)>> 8;
            buffer_H[5] = Voltage_3V3 & 0xFF;
            
            buffer_H[6] = 0x00;
            buffer_H[7] = 0x00;
            buffer_H[8] = (Gyro_Vol_Ref_Unsigned & 0xFF00) >> 8;
            buffer_H[9] = Gyro_Vol_Ref_Unsigned & 0x00FF;
            buffer_H[10] = (Gyro_value & 0xFF00) >> 8;// Gyro value 12 bits
            buffer_H[11] = Gyro_value & 0x00FF;     // Gyro value 12 bits
            buffer_H[12] = (Voltage_5V & 0xFF00)>> 8;// debug 5V flag not used just yet
            buffer_H[13] = Voltage_5V & 0xFF;    // debug 5V flag not used just yet
            
             // write CRC
            crc = CRC_ChecksumByte(buffer_H, 14, 0x00); 
            buffer_H[14] = (crc & 0xFF00) >> 8; 
            buffer_H[15] = crc & 0x00FF;
            
            
        }
        else
        {
            /*******************************************************************
            * Drilling packet 1a 125Hz
            *******************************************************************/
            
            buffer_L[0] = 0xA3; // Z mag
            buffer_L[1] = (Time.miliseconds & 0xFF00) >> 8;
            buffer_L[2] = Time.miliseconds & 0x00FF;
            buffer_L[3] = Accel_LG1_Data[2];
            buffer_L[4] = Accel_LG1_Data[3];
            buffer_L[5] = (Accel_LG1_Data[4] & 0xF0) | ((Accel_LG1_Data[5] & 0xF0) >> 4);
            buffer_L[6] = ((Accel_LG1_Data[5] & 0x0F) << 4) | ((Accel_LG1_Data[6] & 0xF0) >> 4);
            buffer_L[7] = ((Accel_LG1_Data[6] & 0x0F) << 4) | ((Accel_LG1_Data[7] & 0xF0) >> 4);
            buffer_L[8] = Accel_LG1_Data[8];
            buffer_L[9] = Accel_LG1_Data[9];
            buffer_L[10] = (Accel_LG1_Data[10] & 0xF0) | ((Accel_LG2_Data[2] & 0xF0) >> 4);
            buffer_L[11] = ((Accel_LG2_Data[2] & 0x0F) << 4) | ((Accel_LG2_Data[3] & 0xF0) >> 4);
            buffer_L[12] = ((Accel_LG2_Data[3] & 0x0F) << 4) | ((Accel_LG2_Data[4] & 0xF0) >> 4);
            buffer_L[13] = Accel_LG2_Data[5];
            
             // write CRC
            crc = CRC_ChecksumByte(buffer_L, 14, 0x00); 
            buffer_L[14] = (crc & 0xFF00) >> 8; 
            buffer_L[15] = crc & 0x00FF;
            
            /*******************************************************************
            * Drilling packet 1b 125Hz
            *******************************************************************/
            buffer_H[0] = Accel_LG2_Data[6];    
            buffer_H[1] = (Accel_LG2_Data[7] & 0xF0) | ((Gyro_value & 0x0F00) >> 8);   
            buffer_H[2] = Gyro_value & 0x00FF;      
            buffer_H[3] = Accel_HG_Data[0];   
            buffer_H[4] = Accel_HG_Data[1];
            buffer_H[5] = Accel_HG_Data[2];
            buffer_H[6] = Accel_HG_Data[3];
            buffer_H[7] = (Accel_HG_Data[4] & 0xF0) | ((Accel_LG2_Data[8] & 0xF0) >> 4);
            buffer_H[8] = ((Accel_LG2_Data[8] & 0x0F) << 4) | ((Accel_LG2_Data[9] & 0xF0) >> 4);
            buffer_H[9] = ((Accel_LG2_Data[9] & 0x0F) << 4) | ((Accel_LG2_Data[10] & 0xF0) >> 4);
//            buffer_H[10] = Tool_Face_Int32 >> 24;
//            buffer_H[11] = Tool_Face_Int32 >> 16;
//            buffer_H[12] = Tool_Face_Int32 >> 8;
//            buffer_H[13] = Tool_Face_Int32; 
            
//            buffer_H[10] = Magneto_Data[2];
//            buffer_H[11] = Magneto_Data[3];
//            buffer_H[12] = Magneto_Data[4];
//            buffer_H[13] = Magneto_Data[5]; 
            
            buffer_H[10] = Gyro_Vol_Ref_Unsigned >> 8;
            buffer_H[11] = Gyro_Vol_Ref_Unsigned;
            buffer_H[12] = Magneto_Data[4];
            buffer_H[13] = Magneto_Data[5]; 

             // write CRC
            crc = CRC_ChecksumByte(buffer_H, 14, 0x00); 
            buffer_H[14] = (crc & 0xFF00) >> 8; 
            buffer_H[15] = crc & 0x00FF;
        }
        
        
        Drill_Pointer += 1; 
        if(Drill_Pointer >= 125) // 125 Hz
        {
            Drill_Pointer = 0; 
        }
        
        Write_To_Memory(buffer_L, buffer_H); 
        //CAN_Encode_Sending(0x1B,0xC4, buffer_L, 16); // debug
        //CAN_Encode_Sending(0x1B,0xC4, buffer_H, 16); // debug
    }
    else if(State_Flags.Drill_250Hz_State == 1)
    {
        if(Drill_Pointer == 0) // Timestamp 
        {
            // 01 02 03 04 05 06 07 08 09 10 11 12 13 14
            /*******************************************************************
            * Packet 1a Time reference Once every 
            *******************************************************************/
            //buffer_L[0] = 0xB1;
            //buffer_L[0] = 0xB4;
            buffer_L[0] = 0xC1;
            buffer_L[1] = Time.year;
            buffer_L[2] = Time.month;
            buffer_L[3] = Time.days;
            buffer_L[4] = Time.hours;
            buffer_L[5] = Time.minutes;
            buffer_L[6] = Time.seconds;
            buffer_L[7] = (Time.miliseconds & 0xFF00) >> 8;
            buffer_L[8] = Time.miliseconds & 0x00FF;
            buffer_L[9] = Accel_HG_Data[0];
            buffer_L[10] = Accel_HG_Data[1];
            buffer_L[11] = Accel_HG_Data[2];
            buffer_L[12] = Accel_HG_Data[3];
            buffer_L[13] = Accel_HG_Data[4]; 
            
             // write CRC
            crc = CRC_ChecksumByte(buffer_L, 14, 0x00); 
            buffer_L[14] = (crc & 0xFF00) >> 8; 
            buffer_L[15] = crc & 0x00FF;
            
            /*******************************************************************
            * Packet 1b Time reference Once every 32ms
            *******************************************************************/
            buffer_H[0] = ((Accel_LG1_Data[0] & 0x0F) << 4) | ((Accel_LG1_Data[1] & 0xF0) >> 4); // Temp LG1
            buffer_H[1] = ((Accel_LG1_Data[0] & 0x0F) << 4) | ((Accel_LG2_Data[0] & 0xF0) >> 4); // Temp LG1 + Temp LG2
            buffer_H[2] = Accel_LG2_Data[1]; // temp LG2
            buffer_H[3] = Magneto_Data[0];
            buffer_H[4] = Magneto_Data[1];
            buffer_H[5] = Magneto_Data[2];
            buffer_H[6] = Magneto_Data[3];
            buffer_H[7] = Magneto_Data[4];
            buffer_H[8] = Magneto_Data[5];   
            buffer_H[9] = (Gyro_value & 0xFF00) >> 8;// Gyro value 16 bits
            buffer_H[10] = Gyro_value & 0x00FF;     // Gyro value 16 bits
            buffer_H[11] = ((Voltage_3V3 & 0xFF0) >> 4); 
            buffer_H[12] = ((Voltage_3V3 & 0x0F) << 4) | ((Voltage_5V & 0xF00) >> 8); 
            buffer_H[13] = Voltage_5V & 0xFF;
            

//            buffer_H[0] = (Gyro_temp & 0xFF00) >> 8;// Temp gyro MSB - 12bits
//            buffer_H[1] = Gyro_temp & 0x00FF;       // Temp gyro LSB - 12bits
//            buffer_H[2] = Accel_LG1_Data[0];        // temp LG1 MSB - 12bits
//            buffer_H[3] = Accel_LG1_Data[1];        // temp LG1 LSB - 12bits
//            buffer_H[4] = Magneto_Data[0];
//            buffer_H[5] = Magneto_Data[1];
//            buffer_H[6] = Magneto_Data[2];
//            buffer_H[7] = Magneto_Data[3];
//            buffer_H[8] = Magneto_Data[4];
//            buffer_H[9] = Magneto_Data[5];
////            buffer_H[4] = (Voltage_3V3 & 0xFF00)>> 8;
////            buffer_H[5] = Voltage_3V3 & 0xFF;
////            buffer_H[6] = 0x00;
////            buffer_H[7] = 0x00;
////            buffer_H[8] = 0x00;
////            buffer_H[9] = 0x00;
//            buffer_H[10] = (Gyro_value & 0xFF00) >> 8;// Gyro value 12 bits
//            buffer_H[11] = Gyro_value & 0x00FF;     // Gyro value 12 bits
//            buffer_H[12] = (Voltage_5V & 0xFF00)>> 8;// debug 5V lag not used just yet
//            buffer_H[13] = Voltage_5V & 0xFF;    // debug 5V flag not used just yet
            
             // write CRC
            crc = CRC_ChecksumByte(buffer_H, 14, 0x00); 
            buffer_H[14] = (crc & 0xFF00) >> 8; 
            buffer_H[15] = crc & 0x00FF;
            
            
        }
        else
        {
            /*******************************************************************
            * Drilling packet 1a 250Hz
            *******************************************************************/
//            Accel_LG1_Data[2]  = value & 0xFF; 
//            Accel_LG1_Data[3]  = value & 0xFF; 
//            Accel_LG1_Data[4]  = value & 0xF0; 
//            Accel_LG1_Data[5]  = value & 0xFF; 
//            Accel_LG1_Data[6]  = value & 0xFF; 
//            Accel_LG1_Data[7]  = value & 0xF0;
//            Accel_LG1_Data[8]  = value & 0xFF; 
//            Accel_LG1_Data[9]  = value & 0xFF; 
//            Accel_LG1_Data[10] = value & 0xF0;  
            
            
            // testing compression ////////////////////////////
//            Accel_LG1_Data[2]  = 0xAB; 
//            Accel_LG1_Data[3]  = 0xCD; 
//            Accel_LG1_Data[4]  = 0xE0; 
//            Accel_LG1_Data[5]  = 0x12; 
//            Accel_LG1_Data[6]  = 0x34; 
//            Accel_LG1_Data[7]  = 0x50;
//            Accel_LG1_Data[8]  = 0x67; 
//            Accel_LG1_Data[9]  = 0x89; 
//            Accel_LG1_Data[10] = 0xA0;      
//            Accel_LG2_Data[8]  = 0x12; 
//            Accel_LG2_Data[9]  = 0x34; 
//            Accel_LG2_Data[10] = 0x50; 
//            Accel_LG3_Data[8]  = 0x12; 
//            Accel_LG3_Data[9]  = 0x34; 
//            Accel_LG3_Data[10] = 0x50;  
//            Gyro_value = 0xABC; 
            // 0C 1A 1B C4 00 18 B2 00 9F AB CD E1 23 45 67 89 A1 23 45 12 B6 2E EE 0D 
            // 0C 1A 1B C4 00 18 34 5A BC 00 00 00 00 00 7E 31 7D 42 87 B0 C0 22 1E 0D

            ///////////////////////////////////////////
            
//            //buffer_L[0] = 0xB2;
//            buffer_L[0] = 0xB5;
//            buffer_L[1] = (Time.miliseconds & 0xFF00) >> 8;
//            buffer_L[2] = Time.miliseconds & 0x00FF;
//            buffer_L[3] = Accel_LG1_Data[2];
//            buffer_L[4] = Accel_LG1_Data[3];
//            buffer_L[5] = (Accel_LG1_Data[4] & 0xF0) | ((Accel_LG1_Data[5] & 0xF0) >> 4);
//            buffer_L[6] = ((Accel_LG1_Data[5] & 0x0F) << 4) | ((Accel_LG1_Data[6] & 0xF0) >> 4);
//            buffer_L[7] = ((Accel_LG1_Data[6] & 0x0F) << 4) | ((Accel_LG1_Data[7] & 0xF0) >> 4);
//            buffer_L[8] = Accel_LG1_Data[8];
//            buffer_L[9] = Accel_LG1_Data[9];
////            buffer_L[10] = (Accel_LG1_Data[10] & 0xF0) | ((Accel_LG2_Data[8] & 0xF0) >> 4);
////            buffer_L[11] = ((Accel_LG2_Data[8] & 0x0F) << 4) | ((Accel_LG2_Data[9] & 0xF0) >> 4);
////            buffer_L[12] = ((Accel_LG2_Data[9] & 0x0F) << 4) | ((Accel_LG2_Data[10] & 0xF0) >> 4);
////            buffer_L[13] = Accel_LG3_Data[8];
//            buffer_L[10] = (Accel_LG1_Data[10] & 0xF0) | ((Accel_LG2_Data[5] & 0xF0) >> 4);
//            buffer_L[11] = ((Accel_LG2_Data[5] & 0x0F) << 4) | ((Accel_LG2_Data[6] & 0xF0) >> 4);
//            buffer_L[12] = ((Accel_LG2_Data[6] & 0x0F) << 4) | ((Accel_LG2_Data[7] & 0xF0) >> 4);
//            buffer_L[13] = Accel_LG2_Data[8];
//            
//             // write CRC
//            crc = CRC_ChecksumByte(buffer_L, 14, 0x00); 
//            buffer_L[14] = (crc & 0xFF00) >> 8; 
//            buffer_L[15] = crc & 0x00FF;
            
            ///////////////////////////////////////////////
            //buffer_L[0] = 0xD1; // 250Hz GEN 2
            buffer_L[0] = 0xD2; // 250Hz GEN 2 - Mag debug
            buffer_L[1] = (Time.miliseconds & 0x0FF0) >> 4;
            buffer_L[2] = ((Time.miliseconds & 0x0F) << 4)| ((Accel_LG1_Data[2] & 0xF0) >> 4); // MS, X
            buffer_L[3] = ((Accel_LG1_Data[2] & 0x0F) << 4) | ((Accel_LG1_Data[3] & 0xF0) >> 4); // X
            buffer_L[4] = ((Accel_LG1_Data[3] & 0x0F) << 4) | ((Accel_LG1_Data[4] & 0xF0) >> 4); // X
            buffer_L[5] = Accel_LG1_Data[5]; // Y
            buffer_L[6] = Accel_LG1_Data[6]; // Y
            buffer_L[7] = (Accel_LG1_Data[7] & 0xF0) | ((Accel_LG1_Data[8] & 0xF0) >> 4); // Y, Z
            buffer_L[8] = ((Accel_LG1_Data[8] & 0x0F) << 4) | ((Accel_LG1_Data[9] & 0xF0) >> 4); // Z
            buffer_L[9] = (Accel_LG1_Data[9] & 0xF0) | ((Accel_LG1_Data[10] & 0xF0) >> 4); // Z
            buffer_L[10] = Accel_LG2_Data[2]; // X
            buffer_L[11] = Accel_LG2_Data[3]; // X
            buffer_L[12] = (Accel_LG2_Data[4] & 0xF0) | ((Accel_LG2_Data[5] & 0xF0) >> 4); // X, Y
            buffer_L[13] = ((Accel_LG2_Data[5] & 0x0F) << 4) | ((Accel_LG2_Data[6] & 0xF0) >> 4); // Y
            
             // write CRC
            crc = CRC_ChecksumByte(buffer_L, 14, 0x00); 
            buffer_L[14] = (crc & 0xFF00) >> 8; 
            buffer_L[15] = crc & 0x00FF;

            /*******************************************************************
            * Drilling packet 1b 250Hz
            *******************************************************************/
            buffer_H[0] = ((Accel_LG2_Data[6] & 0x0F) << 4) | ((Accel_LG2_Data[4] & 0xF0) >> 4); // Y, Z
            buffer_H[1] = Accel_LG2_Data[8]; // Z
            buffer_H[2] = Accel_LG2_Data[9]; // Z
            buffer_H[3] = (Accel_LG2_Data[10] & 0xF0) | ((Accel_HG_Data[0] & 0xF0) >> 4); // Z, X   
            buffer_H[4] = ((Accel_HG_Data[0] & 0x0F) << 4) | ((Accel_HG_Data[1] & 0xF0) >> 4); // X
            buffer_H[5] = ((Accel_HG_Data[1] & 0x0F) << 4) | ((Accel_HG_Data[2] & 0xF0) >> 4); // Y
            buffer_H[6] = ((Accel_HG_Data[2] & 0x0F) << 4) | ((Accel_HG_Data[3] & 0xF0) >> 4); // Y
            buffer_H[7] = ((Accel_HG_Data[3] & 0x0F) << 4) | ((Accel_HG_Data[4] & 0xF0) >> 4); // Z
            buffer_H[8] = (Gyro_value & 0xFF00) >> 8;
            buffer_H[9] = Gyro_value & 0x00FF;
//            buffer_H[10] = Tool_Face_Int32 >> 24;
//            buffer_H[11] = Tool_Face_Int32 >> 16;
//            buffer_H[12] = Tool_Face_Int32 >> 8;
//            buffer_H[13] = Tool_Face_Int32; 
            buffer_H[10] = Magneto_Data[0];
            buffer_H[11] = Magneto_Data[1];
            buffer_H[12] = Magneto_Data[2];
            buffer_H[13] = Magneto_Data[3];
            
            //////////////////////////////////////////////////////////////////
             // write CRC
            crc = CRC_ChecksumByte(buffer_H, 14, 0x00); 
            buffer_H[14] = (crc & 0xFF00) >> 8; 
            buffer_H[15] = crc & 0x00FF;
        }
        
        Drill_Pointer += 1; 
        if(Drill_Pointer >= 250) // 250 Hz
        {
            Drill_Pointer = 0; 
        }

        
        Write_To_Memory(buffer_L, buffer_H); 
        //CAN_Encode_Sending(0x1B,0xC4, buffer_L, 16); // debug
        //CAN_Encode_Sending(0x1B,0xC4, buffer_H, 16); // debug
    }
    else
    {
        // error
    }
    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Write_To_Memory(uint8_t *buffer_L, uint8_t *buffer_H)
{
    uint8_t i;
    uint8_t pointer = 0;
    uint8_t buffer[32];
    
    for(i=0; i<16; i++)
    {
        buffer[pointer++] = buffer_L[i]; 
    }
    
    for(i=0; i<16; i++)
    {
        buffer[pointer++] = buffer_H[i]; 
    }
    
    if(MT25QL01_Flag.Mem_All_Sleep == 1)
    {
        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_In_Used); 
    }

    MEM_MT25QL01_Write_Bytes(MT25QL01_In_Used, buffer, 32);
    
//    if(Debug_Flags.Test_Data_Out == 1)
//    {
//        //LEDR = 1; 
//        for(i=0; i<16; i++)
//        {
//            //TestRAM[TestRAM_Pointer++] = buffer_L[i]; 
//        }
//
//        for(i=0; i<16; i++)
//        {
//            //TestRAM[TestRAM_Pointer++] = buffer_H[i];
//        }
//
//        if(TestRAM_Pointer >= 8192) // 8192
//        {
//            TestRAM_Pointer = 0; 
//            Debug_Flags.Test_Data_Out = 0; 
//            Debug_Flags.Read_Data_Out = 1; 
//            State_Flags.Drill_State = 0; 
//            State_Flags.Drill_250Hz_State = 0; 
//            
//
//        }
//    }
//    else
//    {
//        
//    }
    


    
}
/*******************************************************************************
 * Function: Read memory
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Read_Memory(void)
{
    //uint8_t i;
    //uint8_t buffer[32];

//    if(Debug_Flags.Read_Data_Out == 1)
//    {
//        //LEDR = !LEDR; 
//        for(i=0; i<32; i++)
//        {
//            buffer[i] = TestRAM[TestRAM_Pointer++]; 
//        }
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 32);
//
//        if(TestRAM_Pointer >= 8192) // 8192
//        {
//            TestRAM_Pointer = 0; 
//            Debug_Flags.Test_Data_Out = 0; 
//            Debug_Flags.Read_Data_Out = 0; 
//        }
//    }
//    
//    if(Debug_Flags.Read_Burst_Out == 1)
//    {
//        for(i=0; i<32; i++)
//        {
//            buffer[i] = BufferRAM[Test_BufferRAM_Pointer++]; 
//        }
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 32);
//
//        if(Test_BufferRAM_Pointer >= 16384)
//        {
//            Test_BufferRAM_Pointer = 0; 
//            Debug_Flags.Test_Burst_Out = 0; 
//            Debug_Flags.Read_Burst_Out = 0; 
//
//        }
//    }
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: Save Event Buffer to be writing later in I2C Memory MEM_CY15B064J
 ******************************************************************************/
void Save_Event_Buffer(uint8_t packetID, uint8_t event, uint8_t *data)
{
    uint8_t buffer[16];
    uint16_t crc;
    uint8_t i; 
    
    // all event are 16 bytes
    buffer[0] = packetID;
    buffer[1] = Time.year;
    buffer[2] = Time.month;
    buffer[3] = Time.days;
    buffer[4] = Time.hours;
    buffer[5] = Time.minutes;
    buffer[6] = Time.seconds;
    buffer[7] = (Time.miliseconds & 0xFF00) >> 8;
    buffer[8] = Time.miliseconds & 0x00FF;
    buffer[9] = event;
    buffer[10] = data[0];
    buffer[11] = data[1];
    buffer[12] = data[2];
    buffer[13] = data[3];

     // write CRC
    crc = CRC_ChecksumByte(buffer, 14, 0x00); 
    //buffer[14] = (crc & 0xFF00) >> 8; 
    //buffer[15] = crc & 0x00FF;
    
    for(i=0; i<14; i++)
    {
        MemoryEventBuffer[EventPointerBuffer++] = buffer[i];
    }
    
    MemoryEventBuffer[EventPointerBuffer++] = (crc & 0xFF00) >> 8; 
    MemoryEventBuffer[EventPointerBuffer++] = crc & 0x00FF;
     
    if(EventPointerBuffer >= EventPointerMax)
    {
        EventPointerBuffer = 0; // roll over circular buffer
    }
    
    
    NumberEventSaved++; 
    

    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: Write Event I2C Memory MEM_CY15B064J
 ******************************************************************************/
void Save_Event_Cmd_Buffer(uint8_t packetID, uint8_t event)
{
    uint8_t buffer[16];
    uint16_t crc;
    uint8_t i; 
    
    // all event are 16 bytes
    buffer[0] = packetID;
    buffer[1] = Time.year;
    buffer[2] = Time.month;
    buffer[3] = Time.days;
    buffer[4] = Time.hours;
    buffer[5] = Time.minutes;
    buffer[6] = Time.seconds;
    buffer[7] = (Time.miliseconds & 0xFF00) >> 8;
    buffer[8] = Time.miliseconds & 0x00FF;
    buffer[9] = event;
    buffer[10] = 0x00; // not used
    buffer[11] = 0x00; // not used
    buffer[12] = 0x00; // not used
    buffer[13] = 0x00; // not used

     // write CRC
    crc = CRC_ChecksumByte(buffer, 14, 0x00); 
    //buffer[14] = (crc & 0xFF00) >> 8; 
    //buffer[15] = crc & 0x00FF;
    
    for(i=0; i<14; i++)
    {
        MemoryEventBuffer[EventPointerBuffer++] = buffer[i];
    }
    
    MemoryEventBuffer[EventPointerBuffer++] = (crc & 0xFF00) >> 8; 
    MemoryEventBuffer[EventPointerBuffer++] = crc & 0x00FF;
     
    NumberEventSaved++; 
    
    if(EventPointerBuffer >= EventPointerMax)
    {
        EventPointerBuffer = 0; // roll over circular buffer
    }
    

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: Write Event I2C Memory MEM_CY15B064J
 ******************************************************************************/
void Write_Event_I2C_Mem(uint8_t NumberEvenToWrite)
{
    
    uint8_t i,j; 
    uint8_t buffer[16];
    uint8_t numberEvent = NumberEventSaved;
    //uint8_t memory_I2C_address = 1; MEM_CY15B064J_Get_I2C_Address(MEM_CY15B064J_Read_In_Used);
//    if(NumberEvenToWrite <= 0)
//    {
//        return; 
//    }
    
    for(i=0; i<NumberEvenToWrite; i++)
    {
        if(numberEvent <= 0)
        {
            return; 
            buffer[0] = 0xEE;
            buffer[1] = 0x02;
            buffer[2] = 0x08;
            CAN_Encode_Sending(0x1B,0xC4, buffer, 3);
        }
         
        for(j=0; j<16; j++)
        {
            buffer[j] = MemoryEventBuffer[EventPointerWriting++];
        }
        
        if(EventPointerWriting >= EventPointerMax)
        {
            EventPointerWriting = 0; // roll over circular buffer
        }

        // all event are 16 bytes
        //memory_I2C_address = MEM_CY15B064J_Get_I2C_Address(MEM_CY15B064J_Write_In_Used);
        
        //MEM_CY15B064J_Write_Bytes(memory_I2C_address, MEM_CY15B064J_Write_bytes_pointer,buffer, 16);
        MEM_CY15B064J_Write_bytes_pointer += 16; 
        NumberEventSaved -= 1; 
                
        if(MEM_CY15B064J_Write_bytes_pointer >= MEM_CY15B064J_bytes_Max)
        {
            MEM_CY15B064J_Write_In_Used+= 1; 
            if(MEM_CY15B064J_Write_In_Used > MEM_CY15B064J_Number_Max)
            {
                // write all data
                MEM_CY15B064J_Write_In_Used = 1; 
                MEM_CY15B064J_Write_bytes_pointer = 0; 
                return; 
            }
        }
    }
    
    
}

/*******************************************************************************
 * Function: Time_Sync
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Time_Sync(void)
{
    uint16_t checksum16 = 0;
    uint8_t checksum8;
    uint8_t i; 
    uint8_t buffer[3] = {0};
    if(State_Flags.Time_Sync_Set == 0)
    {
        // 17 10 10 13 17 05 0A 10 26 06 32 00 00 D2 17 C7
        // 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15

        //buffer[0] = 0xCC;
        //buffer[1] = 0xCC;       
        //buffer[2] = Uart_1_data_pointer; 
        //CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                
        if(Uart_1_data_pointer == 16)
        {
            State_Flags.Time_Sync_Processing = 1; 
            
            for (i=0; i < 15; i++) // remove SOF
            {
                checksum16 += Uart_1_data_buffer[i];
            }
            
            checksum8 = checksum16 & 0xFF; 
            
            if(checksum8 != Uart_1_data_buffer[15])
            {
                // error
                buffer[0] = 0xEE;
                buffer[1] = 0xAA;       
                buffer[2] = 0xE1; 
                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                State_Flags.Time_Sync_Processing = 0;
                reset_uart_1_registers(); 
                return; 
            }
            
            
            if(Uart_1_data_buffer[0] != 0x17) // SOF
            {
                buffer[0] = 0xEE;
                buffer[1] = 0xAA;       
                buffer[2] = 0xE2; 
                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                State_Flags.Time_Sync_Processing = 0;
                reset_uart_1_registers(); 
                return; 
            }
            
            if(Uart_1_data_buffer[1] != 0x10) // Length 1
            {
                buffer[0] = 0xEE;
                buffer[1] = 0xAA;       
                buffer[2] = 0xE3; 
                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                State_Flags.Time_Sync_Processing = 0;
                reset_uart_1_registers(); 
                return;
            }
    
            
            if(Uart_1_data_buffer[2] != 0x10) // Length 2
            {
                buffer[0] = 0xEE;
                buffer[1] = 0xAA;       
                buffer[2] = 0xE4; 
                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                State_Flags.Time_Sync_Processing = 0;
                reset_uart_1_registers(); 
                return;
            }
            
            if(Uart_1_data_buffer[3] != 0x13) // ID
            {
                buffer[0] = 0xEE;
                buffer[1] = 0xAA;       
                buffer[2] = 0xE5; 
                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                State_Flags.Time_Sync_Processing = 0;
                reset_uart_1_registers(); 
                return;
            }
            
            if(Uart_1_data_buffer[14] != 0x17) // SOF
            {
                buffer[0] = 0xEE;
                buffer[1] = 0xAA;       
                buffer[2] = 0xE6; 
                CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
                State_Flags.Time_Sync_Processing = 0;
                reset_uart_1_registers(); 
                return; 
            }
            
            Time.year = Uart_1_data_buffer[4]; 
            Time.month = Uart_1_data_buffer[5]; 
            Time.days = Uart_1_data_buffer[6]; 
            Time.hours = Uart_1_data_buffer[7]; 
            Time.minutes = Uart_1_data_buffer[8]; 
            Time.seconds = Uart_1_data_buffer[9]; 
            Time.miliseconds = 0x0000;

            
            State_Flags.Time_Sync_Set = 1; 
            reset_uart_1_registers(); 
            Drill_Pointer = 0;
        }
    }
    
    State_Flags.Time_Sync_Processing = 0; 
}

/*******************************************************************************
 * Function: Test_Calc_TF
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Test_Calc_TF(void)
{
    /***************************************************************************
     * float => (32-bit single precision floating point) 7 decimal  ???
     * double => (64-bit double precision floating point) 15 decimal   ???  
     **************************************************************************/
    //Debug_PIN_TX1 = 1;
    /***************************************************************************
     * general declaration
     **************************************************************************/
    uint8_t buffer[16] = {0};
//    int32_t tempo_float = 0;
//    int32_t tempo_Int32 = 0;
    
    /***************************************************************************
     * declare constant
     **************************************************************************/
    
    // angle = -120;                    // fix value (60 or 120 TBD)
    // radius = 12mm                    // 12mm == 0.012m
    const float cos_k = -0.5;           // RAD
    const float sin_k = -0.866025404;   // RAD
    const float One_r_s = 83.333333;    // 1 / radius So to axis
    const float dt = 0.008;             // delta time depend on sampling rate
    
    float a_a_x = 16591 * 0.000153036;          // converted in m/s2
    float a_a_y = 0 * 0.000153036;              // converted in m/s2
    //float a_a_z = 61918 * 0.000153036;          // converted in m/s2
    float a_s_x = 20663 * 0.000153036;          // converted in m/s2
    float a_s_y = 0 * 0.000153036;              // converted in m/s2
    float a_s_z = 88048 * 0.000153036;          // converted in m/s2
    
//    tempo_float = a_a_y * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[0] = tempo_Int32 >> 24; 
//    buffer[1] = tempo_Int32 >> 16; 
//    buffer[2] = tempo_Int32 >> 8; 
//    buffer[3] = tempo_Int32;
//   CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
    
//    float a_a_x = 2.539020276;      // converted in m/s2
//    float a_a_y = 0;                // converted in m/s2
//    float a_a_z = 9.475683048;      // converted in m/s2
//    float a_s_x = 3.162182868;      // converted in m/s2
//    float a_s_y = 0;                // converted in m/s2
//    float a_s_z = 13.474513728;     // converted in m/s2
    
    /***************************************************************************
     * declare variable
     **************************************************************************/
    int32_t alpha_int32 = 0;
    float alpha = 0; 
    float alpha_tempo = 0; 
    
    int32_t omega_int32 = 0;
    float omega = 0; 
    float omega_tempo_1 = 0; 
    float omega_tempo_2 = 0; 
    float omega_tempo_3 = 0; 
    
    int32_t phy_t_int32 = 0;
    float phy_t = 0; 
    float phy_t_tempo_1 = 0; 
    float phy_t_tempo_2 = 0; 
    float phy_t_tempo_3 = 0; 
    float phy_t_tempo_4 = 0; 
    
    float phy_t_old = 0; 
    
    /***************************************************************************
     * alpha calculation
     **************************************************************************/
    alpha_tempo = a_s_y - a_a_y; 
    alpha = alpha_tempo * One_r_s; 
            
    /***************************************************************************
     * Omega calculation
     **************************************************************************/
    // ST1
    omega_tempo_1 = cos_k * a_s_x; 
    
    // ST2
    omega_tempo_2 = sin_k * a_s_z; 
    
    omega_tempo_2 -= a_a_x; 
    
    // ST3
    omega_tempo_3 = -(omega_tempo_1 + omega_tempo_2); 
    
    omega_tempo_1 = omega_tempo_3 * One_r_s;
    // ST4
    //Debug_PIN_TX1 = 1;
    omega = sqrt (omega_tempo_1);
    if (errno)
    {
        // error
        buffer[0] = 0xEE; 
        buffer[1] = 0xEE; 
        buffer[2] = 0xEE; 
        buffer[3] = 0xEE;
        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
    }

     
    
    /***************************************************************************
     * phy calculation
     **************************************************************************/
    // ST6
    phy_t_tempo_1 = omega * dt; 
    
    // ST7
    phy_t_tempo_2 = alpha * 0.5; 
    
    // ST8
    phy_t_tempo_3 = dt * dt; 
    
    // ST9
    phy_t_tempo_4 = phy_t_tempo_2 + phy_t_tempo_3; 
    
    // ST10 
    phy_t = phy_t_old + phy_t_tempo_1 + phy_t_tempo_4; 
    
    /***************************************************************************
     * conversion to integer
     **************************************************************************/
    alpha_tempo = alpha * 65536;
    alpha_int32 = (int32_t) alpha_tempo; 
    
    omega_tempo_1 = omega * 65536;
    omega_int32 = (int32_t) omega_tempo_1;
    
    phy_t_tempo_1 = phy_t * 65536;
    phy_t_int32 = (int32_t) phy_t_tempo_1;
    
    
    //Debug_PIN_TX1 = 0;
    /***************************************************************************
     * display debug
     **************************************************************************/
//    buffer[0] = 0xCA; 
//    buffer[1] = 0x1C; 
//    buffer[2] = alpha_int32 >> 24; 
//    buffer[3] = alpha_int32 >> 16;
//    buffer[4] = alpha_int32 >> 8;
//    buffer[5] = alpha_int32; 
//    buffer[6] = omega_int32 >> 24; 
//    buffer[7] = omega_int32 >> 16; 
//    buffer[8] = omega_int32 >> 8;
//    buffer[9] = omega_int32; 
//    buffer[10] = phy_t_int32 >> 24; 
//    buffer[11] = phy_t_int32 >> 16; 
//    buffer[12] = phy_t_int32 >> 8;
//    buffer[13] = phy_t_int32; 
//    buffer[14] = a_a_z; 
//    buffer[15] = 0xED; 
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 14);
}

/*******************************************************************************
 * Function: Calculation_TF
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Calculation_TF(void)
{
    
    int32_t tempo32 = 0;
//    uint8_t buffer[48] = {0};
//    int32_t tempo_float = 0;
//    int32_t tempo_Int32 = 0;
//    int pointer = 0; 
    
     /***************************************************************************
     * declare constant
     **************************************************************************/
    
    // angle = -120;                    // fix value (60 or 120 TBD)
    // radius = 12mm                    // 12mm == 0.012m
    const double cos_k = -0.5;           // RAD
    const double sin_k = -0.866025404;   // RAD
    const double One_r_s = 83.333333;    // 1 / radius So to axis
    const double dt = 0.008;             // delta time depend on sampling rate
    double LG1_x = 0;                    // converted in m/s2
    double LG1_y = 0;                    // converted in m/s2
    double LG1_z = 0;                    // converted in m/s2
    double LG2_x = 0;                    // converted in m/s2
    double LG2_y = 0;                    // converted in m/s2
    double LG2_z = 0;                    // converted in m/s2
    double a_a_x = 0;                    // converted in m/s2
    double a_a_y = 0;                    // converted in m/s2
    double a_a_z = 0;                    // converted in m/s2
    double a_s_x = 0;                    // converted in m/s2
    double a_s_y = 0;                    // converted in m/s2
    double a_s_z = 0;                    // converted in m/s2
    // temp
    // Temp
    // 2 = X
    // 3 = X
    // 4 = X
    // 5 = Y
    // 6 = Y
    // 7 = Y
    // 8 = Z
    // 9 = Z
    // 10 = Z
    // Accel_LG1_Data and Accel_LG1_Data Conversion; 
    
    tempo32 = Accel_LG1_Data[2]; 
    tempo32 = (tempo32 << 8) | Accel_LG1_Data[3]; 
    tempo32 = (tempo32 << 4) | ((Accel_LG1_Data[4] & 0xF0) >> 4); 
    if((tempo32 & 0x80000) == 0x80000)
    {
        tempo32 |= 0xFFF00000; 
    }
    LG1_x  = (double)(tempo32);
    LG1_x = LG1_x * 0.000153036;          // converted in m/s2

    
//    ////////////////////////////////////////////////////////////////////////////
//    tempo_float = a_a_x * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[0] = tempo32 >> 24; 
//    buffer[1] = tempo32 >> 16; 
//    buffer[2] = tempo32 >> 8; 
//    buffer[3] = tempo32;
//    buffer[4] = tempo_Int32 >> 24; 
//    buffer[5] = tempo_Int32 >> 16; 
//    buffer[6] = tempo_Int32 >> 8; 
//    buffer[7] = tempo_Int32;
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 8);
//    ////////////////////////////////////////////////////////////////////////////
    
//    if((tempo32 & 0x80000) == 0x80000)
//    {
//        a_a_x = (float)((tempo32 | 0xFFF00000)); 
//    }
//    else
//    {
//        a_a_x  = (float)(tempo32); 
//    }
    
    tempo32 = Accel_LG1_Data[5]; 
    tempo32 = (tempo32 << 8) | Accel_LG1_Data[6]; 
    tempo32 = (tempo32 << 4) | ((Accel_LG1_Data[7] & 0xF0) >> 4); 
    if((tempo32 & 0x80000) == 0x80000)
    {
        tempo32 |= 0xFFF00000; 
    }
    LG1_y  = (double)(tempo32);
    LG1_y = LG1_y * 0.000153036;          // converted in m/s2
    
//    ////////////////////////////////////////////////////////////////////////////
//    tempo_float = a_a_y * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[0] = tempo32 >> 24; 
//    buffer[1] = tempo32 >> 16; 
//    buffer[2] = tempo32 >> 8; 
//    buffer[3] = tempo32;
//    buffer[4] = tempo_Int32 >> 24; 
//    buffer[5] = tempo_Int32 >> 16; 
//    buffer[6] = tempo_Int32 >> 8; 
//    buffer[7] = tempo_Int32;
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 8);
//    ////////////////////////////////////////////////////////////////////////////
//    if((tempo32 & 0x80000) == 0x80000)
//    {
//        a_a_y = (float)((tempo32 | 0xFFF00000)); 
//    }
//    else
//    {
//        a_a_y  = (float)(tempo32); 
//    }
    
    tempo32 = Accel_LG1_Data[8]; 
    tempo32 = (tempo32 << 8) | Accel_LG1_Data[9]; 
    tempo32 = (tempo32 << 4) | ((Accel_LG1_Data[10] & 0xF0) >> 4); 
    if((tempo32 & 0x80000) == 0x80000)
    {
        tempo32 |= 0xFFF00000; 
    }
    LG1_z  = (double)(tempo32);
    LG1_z = LG1_z * 0.000153036;          // converted in m/s2

    
    
    tempo32 = Accel_LG2_Data[2]; 
    tempo32 = (tempo32 << 8) | Accel_LG2_Data[3]; 
    tempo32 = (tempo32 << 4) | ((Accel_LG2_Data[4] & 0xF0) >> 4); 
    if((tempo32 & 0x80000) == 0x80000)
    {
        tempo32 |= 0xFFF00000; 
    }

    LG2_x  = (double)(tempo32);
    LG2_x = LG2_x * 0.000153036;          // converted in m/s2
    
//    ////////////////////////////////////////////////////////////////////////////
//    tempo_float = a_s_x * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[0] = tempo32 >> 24; 
//    buffer[1] = tempo32 >> 16; 
//    buffer[2] = tempo32 >> 8; 
//    buffer[3] = tempo32;
//    buffer[4] = tempo_Int32 >> 24; 
//    buffer[5] = tempo_Int32 >> 16; 
//    buffer[6] = tempo_Int32 >> 8; 
//    buffer[7] = tempo_Int32;
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 8);
//    ////////////////////////////////////////////////////////////////////////////
//    if((tempo32 & 0x80000) == 0x80000)
//    {
//        a_s_x = (float)((tempo32 | 0xFFF00000)); 
//    }
//    else
//    {
//        a_s_x  = (float)(tempo32); 
//    }
    
    tempo32 = Accel_LG2_Data[5]; 
    tempo32 = (tempo32 << 8) | Accel_LG2_Data[6]; 
    tempo32 = (tempo32 << 4) | ((Accel_LG2_Data[7] & 0xF0) >> 4); 
    if((tempo32 & 0x80000) == 0x80000)
    {
        tempo32 |= 0xFFF00000; 
    }
    LG2_y  = (double)(tempo32);
    LG2_y = LG2_y * 0.000153036;          // converted in m/s2
//    if((tempo32 & 0x80000) == 0x80000)
//    {
//        a_s_y = (float)((tempo32 | 0xFFF00000)); 
//    }
//    else
//    {
//        a_s_y  = (float)(tempo32); 
//    }
    
    tempo32 = Accel_LG2_Data[8]; 
    tempo32 = (tempo32 << 8) | Accel_LG2_Data[9]; 
    tempo32 = (tempo32 << 4) | ((Accel_LG2_Data[10] & 0xF0) >> 4); 
    if((tempo32 & 0x80000) == 0x80000)
    {
        tempo32 |= 0xFFF00000; 
    }
    LG1_z  = (double)(tempo32); 
    LG1_z = LG1_z * 0.000153036;          // converted in m/s2
//    if((tempo32 & 0x80000) == 0x80000)
//    {
//        a_s_z = (float)((tempo32 | 0xFFF00000)); 
//    }
//    else
//    {
//        a_s_z  = (float)(tempo32); 
//    }


    
     /***************************************************************************
     * Asign the right axis with the accel
     **************************************************************************/
    a_a_x = LG1_x;
    a_a_y = LG1_y;
    a_a_z = LG1_z;
    a_s_x = LG2_x;                    
    a_s_y = LG2_y;                    
    a_s_z = LG2_z;          
            
//    a_a_x = -(LG1_y);                    
//    a_a_y = LG1_z;                    
//    a_a_z = -(LG1_x);                    
//    a_s_x = -(LG2_y);                    
//    a_s_y = LG2_x;                    
//    a_s_z = LG2_z;                    
    
    
    /***************************************************************************
     * declare variable for calculation
     **************************************************************************/
    //int32_t alpha_int32 = 0;
    double alpha = 0; 
    double alpha_tempo = 0; 
    
    //int32_t omega_int32 = 0;
    double omega = 0; 
    double omega_tempo_1 = 0; 
    double omega_tempo_2 = 0; 
    double omega_tempo_3 = 0; 
    
    //int32_t phy_t_int32 = 0;
    //float phy_t = 0; 
    double phy_t_tempo_1 = 0; 
    double phy_t_tempo_2 = 0; 
    double phy_t_tempo_3 = 0; 
    double phy_t_tempo_4 = 0; 
    
    //float phy_t_old = 0; 
    
    /***************************************************************************
     * alpha calculation
     **************************************************************************/
    alpha_tempo = a_s_y - a_a_y; 
    alpha = alpha_tempo * One_r_s; 
            
    /***************************************************************************
     * Omega calculation
     **************************************************************************/
    // ST1
    omega_tempo_1 = cos_k * a_s_x; 
    
    // ST2
    omega_tempo_2 = sin_k * a_s_z; 
    
    omega_tempo_2 -= a_a_x; 
    
    // ST3
    omega_tempo_3 = -(omega_tempo_1 + omega_tempo_2); 
    
    omega_tempo_1 = omega_tempo_3 * One_r_s;
    // ST4
    //Debug_PIN_TX1 = 1;
    omega_tempo_2 = fabs (omega_tempo_1); // get absolute value
    
    omega = sqrt (omega_tempo_2);
    if (errno)
    {
        Tool_Face_phy_float = 0;
        Tool_Face_Old_float = 0;
        Tool_Face_Int32 = 0;
        Tool_Face_Old_Int32 = 0;
        return; 
        // error
//        buffer[0] = 0xEE; 
//        buffer[1] = 0xEE; 
//        buffer[2] = 0xEE; 
//        buffer[3] = 0xEE;
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
    }

    /***************************************************************************
     * phy calculation
     **************************************************************************/
    // ST6
    phy_t_tempo_1 = omega * dt; 
    //phy_t_tempo_1 = omega; 
    //phy_t_tempo_1 = dt; 
    
    ////////////////////////////////////////////////////////////////////////////
//    tempo_float = phy_t_tempo_1 * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    pointer = 0;
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
    ////////////////////////////////////////////////////////////////////////////
    
    // ST7
    phy_t_tempo_2 = alpha * 0.5; 
    
    ////////////////////////////////////////////////////////////////////////////
//    tempo_float = phy_t_tempo_2 * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
    ////////////////////////////////////////////////////////////////////////////
    
    // ST8
    phy_t_tempo_3 = dt * dt; 
    
     ////////////////////////////////////////////////////////////////////////////
//    tempo_float = phy_t_tempo_3 * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
    ////////////////////////////////////////////////////////////////////////////
    
    // ST9
    phy_t_tempo_4 = phy_t_tempo_2 * phy_t_tempo_3; 
    
     ////////////////////////////////////////////////////////////////////////////
//    tempo_float = phy_t_tempo_4 * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//     CAN_Encode_Sending(0x1B,0xC4, buffer, 16);
    ////////////////////////////////////////////////////////////////////////////
    
    // ST10 
    //Tool_Face_phy_float = phy_t_tempo_1 + phy_t_tempo_4; 
    
    Tool_Face_phy_float = Tool_Face_Old_float + phy_t_tempo_1 + phy_t_tempo_4; 
    
    Tool_Face_Old_float = Tool_Face_phy_float; // loading old value for next run 
    
   
    
    /***************************************************************************
     * conversion to integer
     **************************************************************************/
//    alpha_tempo = alpha * 65536;
//    alpha_int32 = (int32_t) alpha_tempo; 
//    
//    omega_tempo_1 = omega * 65536;
//    omega_int32 = (int32_t) omega_tempo_1;
    
    phy_t_tempo_1 = Tool_Face_phy_float * 32768;
    Tool_Face_Int32 = (int32_t) phy_t_tempo_1;
    
    //////////////////////////////////////////////////////////////////////////////
//    tempo_float = a_a_x * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    pointer = 0;
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = a_a_y * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = a_a_z * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = a_s_x * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = a_s_y * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = a_s_z * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = alpha * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = omega * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    tempo_float = Tool_Face_phy_float * 32768; 
//    tempo_Int32 = (int32_t) tempo_float; 
//    
//    buffer[pointer++] = tempo_Int32 >> 24; 
//    buffer[pointer++] = tempo_Int32 >> 16; 
//    buffer[pointer++] = tempo_Int32 >> 8; 
//    buffer[pointer++] = tempo_Int32;
//    
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 36);
    
    //State_Machine_Reset();
    //State_Flags.Idle_State = 1; 
//    ////////////////////////////////////////////////////////////////////////////
}
/*******************************************************************************
 * Function: Test sensor
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Read_Sensors(void)
{
    //uint8_t buffer[16] = {0}; 
    //uint8_t cmd[2] = {0}; 
   ///////////////////////////////////////////////////////////////////////////// 
   // Read ADC AD7994
   //Read_1_reg_I2C(0x21, 0x10); // reading channel 4 only
   //I2CSequentialReadReg_CAN(0x21, 0x80,0x02); // reading channel 4 only
   //I2CSequentialReadReg_CAN(0x21, 0xF0,0x08); // reading all channel
    //I2CSequentialSetReadReg(buffer, ADC_AD7993_ID, 0x30, 0x02);
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 2); // debug
//    if(ADC_Alert == 0)
//    {
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 0);
//    }
//    else
//    {
//        I2CSequentialSetReadReg_CAN(0x21, 0x30, 0x04); // reading all channel 
//    }
     
    
   ///////////////////////////////////////////////////////////////////////////// 
   // Read ADC MCP3422A0
   //I2CSequentialReadReg_CAN(0x68, 0x10,0x02); // 
//    if(Mag_flag == 0)
//    {
//        // Config register
//        // Bit 7 == _RDY
//        // Bit 6 -5  == Channel 1(00) or 2 (01) 
//        // Bit 4 == 0 One shot, 1: countinous default
//        // Bit 3 - 2 == 00: 12 bits, 11: 18bits resolution 
//        // Bit 1 - 0 == PGA Gain
//        Write_1_byte_I2C(0x68, 0x88); // channel 1, 16 bits, One shot
//        //Write_1_byte_I2C(0x68, 0x98); // channel 2, 16 bits, One shot
//        Mag_flag = 1; 
//    }
//    else
//    {
//        I2CSequentialReadByte_CAN(0x68, 0x03);
//        Mag_flag = 0; 
//        // reference = 2.048
//        // LSB == 32768 if 16 bits because sign bit
//        // XXX == value read
//        // voltage  = XXX * 2.048 / LSB 
//    }
   /////////////////////////////////////////////////////////////////////////////
   // Magnet MMC5983MA
    //buffer[0] = MAG_MMC5983MA_read_ID();
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 4); // only 1 byte but round up for CAN BS
//    if(Mag_flag == 0)
//    {
//        // take one mag measurement
//        Write_1_reg_I2C(0x30, 0x09, 0x01);
//        Mag_flag = 1; 
//    }
//    else
//    {
//        if((Read_1_reg_I2C(0x30, 0x08) & 0x01) == 0x01)
//        {
//            I2CSequentialReadReg_CAN(0x30, 0x00, 0x09);
//        }
//        Mag_flag = 0; 
//        //Read_1_reg_I2C(Uart_1_data_Received[5], Uart_1_data_Received[6]);
//    }
    
   /////////////////////////////////////////////////////////////////////////////
   // accel ADXL355
   // I2CSequentialReadReg_CAN(0x1D, 0x00, 4);  // read DEVID_AD, DEVID_MST, PARTID, REVID
//    if(Accel_unit == 0)
//    {
//        ADXL355_I2C_Init(0x1D);
//        Accel_unit++; 
//        
//    }
//    else if(Accel_unit == 1)
//    {
//        ADXL355_I2C_Start_Sensor(0x1D);
//        Accel_unit++;
//    }
//    else if(Accel_unit == 2)
//    {
//        ADXL355_I2C_Set_Range(0x1D, 0x03); // Set 8g range
//        Accel_unit++;
//    }
//    else if(Accel_unit == 3)
//    {
//        I2CSequentialReadReg_CAN(0x1D, ACC355_RANGE, 2);
//        Accel_unit++;
//    }
//    else
//    {
//        ADXL355_I2C_Data_Scan(0x1D);
////        if(Accel_unit == 4)
////        {
////            I2CSequentialReadReg_CAN(0x1D, ACC355_POWER_CONTROL, 1);
////            Accel_unit++;
////        }
////        else
////        {
////            ADXL355_I2C_Data_Scan(0x1D);
////            Accel_unit--;
////        }
//        
//  
//    }
   /////////////////////////////////////////////////////////////////////////////
   // 64k Memory
   // if(Sequencer < 100)
//    {
//        Sequencer += 1; 
//    }
//    
//    //Sequencer += 1; 
//    if(Sequencer == 10)
//    {
//        MEM_CY15B064J_Read_Bytes(0x50, 0x00, 16); 
//    }
//    
//    if(Sequencer == 20)
//    {
//        buffer[0] = 0xA0; 
//        buffer[1] = 0xA1; 
//        buffer[2] = 0xA2; 
//        buffer[3] = 0xA3; 
//        buffer[4] = 0xA4; 
//        buffer[5] = 0xA5; 
//        buffer[6] = 0xA6; 
//        buffer[7] = 0xA7; 
//        buffer[8] = 0xA8; 
//        buffer[9] = 0xA9; 
//        buffer[10] = 0xAA; 
//        buffer[11] = 0xAB; 
//        buffer[12] = 0xAC; 
//        buffer[13] = 0xAD; 
//        buffer[14] = 0xAE; 
//        buffer[15] = 0xAF; 
//        //MEM_CY15B064J_Write_Bytes(0x50, 0x00, buffer, 16); 
//        Write_Seq_16bReg_bytes_I2C(0x50, 0x00, buffer, 16); 
//    }
//    
//    if(Sequencer == 30)
//    {
//        MEM_CY15B064J_Read_Bytes(0x50, 0x00, 16); 
//    }
    

   /////////////////////////////////////////////////////////////////////////////
   // Timer 1 for Timer
   // CAN_Send_MSG(uint8_t destination, uint8_t *data, uint8_t length);
//    buffer[0] = Time.year;
//    buffer[1] = Time.month;
//    buffer[2] = Time.days;
//    buffer[3] = Time.hours; 
//    buffer[4] = Time.minutes;
//    buffer[5] = Time.seconds;
//    buffer[6] = (Time.miliseconds & 0xFF00) >> 8;
//    buffer[7] = Time.miliseconds & 0x00FF;
//    //CAN_Send_MSG(0xC4, buffer,7);
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 8);
    ////////////////////////////////////////////////////////////////////////////
    // Accel ADXL373 SPI
    //cmd_buffer[0] = ADXL373_XDATA_H;
//  Buffer_Burst_Status = SPI_2_Routine_Read_(SPI_CS_ACC_HG, cmd_buffer, 1, Buffer_Burst, 6);
    //buffer[0] = ADXL373_SPI_ID(SPI_CS_ACC_HG); 
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//    if(ADXL373_Seguencer == 0)
//    {
//        ADXL373_SPI_Start_Sensor();
//        ADXL373_Seguencer = 1; 
//    }
//    else
//    {
//        cmd[0] = ADXL373_XDATA_H;
//        ADXL373_SPI_Get_Data(cmd, 1, buffer, 6); 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 6);
//    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Accel ADXL355 SPI
    //buffer[0] = Get_Accel_Device_ID();
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//    if(Accel_unit == 0)
//    {
//        buffer[0] = Get_Accel_Device_ID();
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//        Accel_unit += 1; 
//    }
//    else if(Accel_unit == 1)
//    {
//        buffer[0] = Read_Accel_Device_Register(ACC355_DEVID_MST);
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//        Accel_unit += 1; 
//    }
//    else if(Accel_unit == 2)
//    {
//        buffer[0] = Read_Accel_Device_Register(ACC355_PARTID);
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//        Accel_unit += 1; 
//    }
//    else if(Accel_unit == 3)
//    {
//        buffer[0] = Read_Accel_Device_Register(ACC355_REVID);
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//        Accel_unit += 1; 
//    }
//    else if(Accel_unit == 4)
//    {
//        ADXL355_SPI_Start_Sensor(); 
//        Accel_unit += 1; 
//    }
//    else if(Accel_unit == 5)
//    {
//        buffer[0] = Read_Accel_Device_Register(ACC355_POWER_CONTROL);
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 1);
//        Accel_unit += 1; 
//    }
//    else if(Accel_unit == 6)
//    {
//        cmd[0] = (ACC355_DEVID_AD << 1) | 0x01;
//        ADXL355_SPI_Get_Data(cmd, 1, buffer, 4); 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//        Accel_unit += 1;
//    }
//    else
//    {
//        cmd[0] = (ACC355_TEMP2 << 1) | 0x01;
//        ADXL355_SPI_Get_Data(cmd, 1, buffer, 11); 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 11);
//    }
}
 
/*******************************************************************************
 * Function: Start_Timer_3
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Start_Timer_3(uint32_t microSec)
{
    // tick is 200ns 
    // shift by 2 == 800nS ~= 1us assuimg delay function
    uint32_t tempo = microSec << 2; 
    CCP3PRH = (tempo & 0xFFFF0000) >> 16; 
    //CCP3PRH = 0; 
    CCP3PRL = tempo & 0xFFFF; // 
    IFS2bits.CCT3IF = 0; 
    CCP3CON1Lbits.CCPON = 1; // Enable
}

/*******************************************************************************
 * Function: Start_Timer_3
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t Check_Timer_3(void)
{
    if(IFS2bits.CCT3IF == 1) 
    {
        IFS2bits.CCT3IF = 0;
        return 0x01; 
    }
    else
    {
        return 0x00; 
    }
    
    return 0x00; 
}

/*******************************************************************************
 * Function: Stop_Timer_3
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Stop_Timer_3(void)
{
    CCP3CON1Lbits.CCPON = 0; // disable
}

/*******************************************************************************
 * Function: Multiplication
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
int32_t Multiplication(int x, int y)
{

    //volatile register int result asm("A");
    
    int32_t result;
    //const signed int p0, p1;
    //const unsigned int p2, p3;
    result = __builtin_mulss(x,y);
    //result = __builtin_mulss(x,y);
    
    return result;
}

/*******************************************************************************
 * Function: sleep
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Go_To_Sleep(void)
{
    //Debug_PIN_TX1 = 0;
    Enable_Sleep_Interrupt(); // Input for accel
    
    //start_watch_dog(); 
    start_timer_4(); // wake up time interrupt
    
    Sleep(); // Put the device into Sleep mode
    //Idle (); // Put the device into Idle mode
}
/*******************************************************************************
 * Function: Wake_up_Fx
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void Wake_up_Fx(void)
{
    //Debug_PIN_TX1 = 1;
    //stop_timer_4(); // wake up time interrupt
}
 ////////////////////////////////////////////////////////////////////////////////
// Interrupt
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Function: T1Interrupt
 * Parameters: none
 * Return: none
 * Description: interrupt Timer for time update
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
    Time.miliseconds += 1; 
     
    if(Time.miliseconds >= 1000)
    {
        Time.seconds += 1; 
        Time.miliseconds = 0; 
    }

    if(Time.seconds >= 60)
    {
        Time.minutes += 1; 
        Time.seconds = 0; 
    }
    if(Time.minutes >= 60)
    {
        Time.hours += 1; 
        Time.minutes = 0; 
    }
    if(Time.hours >= 24)
    {
        Time.days += 1; 
        Time.hours = 0; 
    }
    if(Time.days >= 32)
    {
        Time.month += 1; 
        Time.days = 0; 
    }
    
    if(Time.month >= 13)
    {
       Time.year += 1; 
        Time.month = 1; 
    }
    
    IFS0bits.T1IF = 0; 
}
/*******************************************************************************
 * Function: U1RXInterrupt
 * Parameters: none
 * Return: none
 * Description: interrupt UART 1 RX
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt(void)
{
    /* Insert ISR Code Here*/
    //uint8_t buffer[1];
    uint8_t uart_data; 
    //uint8_t buffer_full = 1; 

    uart_data = U1RXREG;
    
    write_uart_2(uart_data); // debug
    
    if(State_Flags.Time_Sync_Processing == 0)
    {
        if(Uart_1_Status.RX_Received == 0)
        {
            Uart_1_data_buffer[Uart_1_data_pointer++] = uart_data;
        }
        
        
        if(Uart_1_data_pointer == 16)
        {
            //Uart_1_data_pointer = 0; 
            Uart_1_Status.RX_Received = 1; 
        }
    }
    
//    while(buffer_full == 1)
//    {
//        uart_data = U1RXREG;
//        
//        //write_uart_1(uart_data); // debug
//        read_uart_1(uart_data); 
//        
//        if(U1STAHbits.URXBF == 0)
//        {
//            buffer_full = 0; 
//        }
//    }
    
    
    IFS0bits.U1RXIF = 0; // Clear Uart RX interrupt
}

/*******************************************************************************
 * Function: interrupt UART 1 Error
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _U1EInterrupt(void)
{
    uint8_t buffer[1];
    buffer[0] = U1RXREG; 
    //uart_1_send_message(0xE2, buffer, 0);
    IFS3bits.U1EIF = 0; // Clear Uart 1 Error interrupt
}

/*******************************************************************************
 * Function: U2RXInterrupt
 * Parameters: none
 * Return: none
 * Description: interrupt UART 1 RX
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _U2RXInterrupt(void)
{
    /* Insert ISR Code Here*/
    //uint8_t buffer[1];
    uint8_t uart_data; 
    //uint8_t buffer_full = 1; 

    uart_data = U2RXREG;
    
    write_uart_1(uart_data); // debug
    
    
    
//    while(buffer_full == 1)
//    {
//        uart_data = U1RXREG;
//        
//        //write_uart_1(uart_data); // debug
//        read_uart_1(uart_data); 
//        
//        if(U1STAHbits.URXBF == 0)
//        {
//            buffer_full = 0; 
//        }
//    }
    
    
    IFS1bits.U2RXIF = 0; // Clear Uart RX interrupt
}

/*******************************************************************************
 * Function: U2EInterrupt
 * Parameters: none
 * Return: none
 * Description: interrupt UART 1 Error
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _U2EInterrupt(void)
{
    uint8_t buffer[1];
    buffer[0] = U2RXREG; 
    //uart_1_send_message(0xE2, buffer, 0);
    IFS3bits.U2EIF = 0; // Clear Uart 1 Error interrupt
}

/*******************************************************************************
 * Function: C1RXInterrupt
 * Parameters: none
 * Return: none
 * Description: interrupt CAN RX 
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _C1RXInterrupt(void)
{
    //LEDR = 1;
    // CAN_Received_To_Uart();
    CAN_Decode_Received(); 
    IFS1bits.C1RXIF = 0; 
}
/*******************************************************************************
 * Function: INT0Interrupt
 * Parameters: none
 * Return: none
 * Description: Accel_LG1_Int
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
{
    IFS0bits.INT1IF = 0; 
}

/*******************************************************************************
 * Function: INT2Interrupt
 * Parameters: none
 * Return: none
 * Description: Accel_HG_Int
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
    //Accel_HG_Flag.Interrupt = 1; 
    //Debug_PIN_TX1 = 0;
//    uint8_t buffer[3] = {0};
//    
//    buffer[0] = 0x1E; 
//    buffer[1] = 0xAD; 
//    buffer[2] = 0x01;
//    CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    
    
    IFS1bits.INT2IF = 0; 
    
    if(State_Flags.Sleep_State == 1)
    {
        // wake up interupt + shock 
        //Disable_Sleep_Interrupt(); 
    
        State_Flags.Sleep_State = 0; 
    }
    else
    {
        // shock interrupt
    }
    
    Wake_up_Fx(); 
    
    Accel_HG_Flag.Interrupt = 1; 
    
}

/*******************************************************************************
 * Function: _CCT4Interrupt
 * Parameters: none
 * Return: none
 * Description: timer 4 
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _CCT4Interrupt(void)
{
    if(State_Flags.Sleep_State == 1)
    {
        // wake up interupt + shock 
        //Disable_Sleep_Interrupt(); 
    
        State_Flags.Sleep_State = 0; 
    }
    else
    {
        // shock interrupt
    }
    
    Disable_Sleep_Interrupt(); 
    
    //while(1); 
    Wake_up_Fx(); 
    
    IFS2bits.CCT4IF = 0; // clear flag
}
/*******************************************************************************
 * Function: CNFInterrupt
 * Parameters: none
 * Return: none
 * Description: Accel_HG_Int
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _CNBInterrupt(void)
{
    uint8_t buffer[3] = {0};
    
    //stop_timer_4(); 
    
    buffer[0] = 0x1A; 
    buffer[1] = 0xCE; 
    buffer[2] = 0x02;
    CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
    
    State_Flags.Sleep_State = 1; 
    
    Wake_up_Fx(); 
    
    CNFBbits.CNFB1 = 0; // port flag
    IFS0bits.CNBIF = 0; 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void __attribute__((__interrupt__,no_auto_psv)) _SoftTrapError(void)
{
    if((INTCON3 & 0x8000) == 0x8000) // DMT bit is on
    {
        
    }
}