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
 *      variable.h
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/

/*******************************************************************************
 * main variable
 ******************************************************************************/

uint16_t Pointer_Block_Flash_test = 0; 
uint32_t Pointer_Entire_Flash_test = 0;

//uint8_t TimerCounter50us = 0; 	// counter
uint8_t TimerCounter100us = 0; 		// counter
uint8_t TimerCounter200us = 0; 		// counter
uint8_t TimerCounter250us = 0; 		// counter 
uint8_t TimerCounter400us = 0; 		// counter
uint8_t TimerCounter1ms = 0; 		// counter 
uint8_t TimerCounter250ms = 0;      // counter
uint8_t TimerCounter1s = 0; 		// counter
uint8_t TimerCounter1m = 0; 		// counter

//#define Uart_RX_Buffer_Length 528 // max should 512 + 7
//unsigned char Uart_1_data_buffer[Uart_RX_Buffer_Length] = {0};
////unsigned char Uart_1_data_Received[Uart_RX_Buffer_Length] = {0};
//unsigned char Uart_1_data_pointer = 0; 
//
//const unsigned char Uart_1_data_timeout_max_count = 50; 
//unsigned char Uart_1_data_timeout_counter = 0; 


#define I2C_Accel_LG2_Error         0x01
#define I2C_Accel_LG3_Error         0x02
#define I2C_ADC_Gyro_Error          0x04
#define I2C_Volt_Write_Error        0x08
#define I2C_Volt_Read_3V3_Error     0x10
#define I2C_Volt_Read_5V_Error      0x20
#define I2C_Magnetometer_Error      0x40

uint8_t I2C_Errors_Flags = 0; 

uint32_t I2C_Errors_Counter = 0; 

const unsigned char Heartbeat_max_count = 10; 
unsigned char Heartbeat_counter = 0; 

uint8_t test_Xtall = 0; 

const unsigned char Boot_Timeout_max_count = 15; 
unsigned char Boot_Timeout_counter = 0; 

const unsigned char Time_Sync_max_count = 15; 
unsigned char Time_Sync_Timeout_counter = 0; 

#ifndef Test_Only 
const unsigned char Time_Stamp_max_count = 30; 
unsigned char Time_Stamp_Timeout_counter = 0; 
#else
const unsigned char Time_Stamp_max_count = 5; 
unsigned char Time_Stamp_Timeout_counter = 0; 
#endif


const unsigned char Init_max_count = 20; 
unsigned char Init_counter = 0; 
uint8_t Init_Flag = 0; 


const uint8_t Go_To_Sleep_max_count = 15; // tick 1 sec
uint8_t Go_To_Sleep_counter = 0; 

const uint8_t debug_LED_Burst_Fast_max_count = 10; // tick 8ms
const uint8_t debug_LED_Burst_max_count = 50; // tick 8ms
const uint8_t debug_LED_max_count = 125; // tick 8ms
uint8_t debug_LED_counter = 0; 
//uint8_t Buffer_Uart_Msg[16] = {0}; 
//volatile unsigned int Buffer_Uart_Msg[16] = {0}; 

//uint8_t __attribute__((aligned(4)))Buffer_Uart_Msg[16];


//struct {
//   unsigned char RX_Started : 1;
//   unsigned char RX_Received : 1;
//   unsigned char RX_Decoded : 1;
//   unsigned char RX_Error : 1;
//   unsigned char RX_Timeout : 1;
//   unsigned char TX_Send : 1;
//   unsigned char Boot_Request : 1;
//} Uart_1_Status;
/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
//uint8_t __attribute__((aligned(4)))Buffer_RAM[16384] = {0xFF}; // used to work
uint8_t __attribute__((aligned(4)))Buffer_RAM_Before[12288] = {0xFF};
uint8_t __attribute__((aligned(4)))Buffer_RAM_After[12288] = {0xFF};
//uint8_t __attribute__((aligned(4)))Buffer_RAM_2[8192] = {0xFF}; // used to work
//uint8_t __attribute__((aligned(4)))Buffer_RAM[20000] = {0xFF}; // used to work

//uint8_t __attribute__((aligned(2)))BufferRAM[16384]; // nope
//uint8_t __attribute__((aligned))BufferRAM[16384]; // nope
//uint8_t __attribute__((aligned))BufferRAM[16384]; // nope
//uint8_t __attribute__(aligned (4),address(0x8000))BufferRAM[16384]; // error syntax
//uint8_t __attribute__((aligned, packed))BufferRAM[16384]; // nope

//uint8_t __attribute__((aligned(4)))BufferRAM[2048]; // works
const uint16_t Buffer_Write_Pointer_Max = 12288;

uint16_t Buffer_RAM_Before_Pointer = 0;    // to write to ram
uint16_t Buffer_RAM_After_Pointer = 0;    // to write to ram

uint16_t Buffer_Write_Before_Pointer = 0;  // to write to memory
uint16_t Buffer_Write_After_Pointer = 0;  // to write to memory

uint16_t Buffer_Read_Pointer = 0;  // to write to memory

const uint8_t Burst_Pointer_Max = 0; 
uint8_t Burst_Before_Pointer = 0; 
uint8_t Burst_After_Pointer = 0;

const uint32_t Burst_Pause_Delay_max_count = 1500000; // 10m at 4ms tick 
uint32_t Burst_Pause_Delay_counter = 0; 

//const uint16_t Buffer_Write_Counter_Max = 32768; 
//uint16_t Buffer_Write_Counter = 0; 

uint16_t Test_BufferRAM_Pointer = 0;

uint16_t TestRAM_Pointer = 0;

const uint16_t BurstBuffer256_Slice_Max = 48; // 12288 / 256
const uint16_t BurstBuffer256_Pointer_Max = 256;
uint16_t BurstBuffer256_Before_Pointer = 0;
uint16_t BurstBuffer256_After_Pointer = 0;

#define Burst_Array_Length 16
uint8_t Buffer_Burst[Burst_Array_Length] ={0}; // Max size 16

uint8_t Burst_Sequencer = 0; 
////////////////////////////////////////////////////////////////////////////////


uint8_t Sequencer = 0; 
uint8_t ADC_MCP3422_Sequencer = 0; 

////////////////////////////
// Drilling packet
uint8_t Drill_Pointer = 0;
//uint8_t Drill_Packet[48] ={0}; 
//uint8_t Drill_Packet_Pointer = 0; 
///////////////////////////

#define Uart_RX_Buffer_Length 16
uint8_t volatile Uart_1_data_buffer[Uart_RX_Buffer_Length] = {0};
uint8_t volatile Uart_1_data_Received[Uart_RX_Buffer_Length] = {0};
uint8_t volatile Uart_1_data_pointer = 0; 
volatile struct {
   uint8_t RX_Started : 1;
   uint8_t RX_Received : 1;
   uint8_t RX_Decoded : 1;
   uint8_t RX_Error : 1;
   uint8_t RX_Timeout : 1;
   uint8_t TX_Send : 1;
   uint8_t TX_Error : 1;
   uint8_t Boot_Request : 1;
} Uart_1_Status;

const uint8_t Uart_1_data_timeout_max_count = 50; 
volatile uint8_t Uart_1_data_timeout_counter = 0; 

volatile uint8_t TimeFlag = 0; 


volatile struct {
  uint8_t year;         // calendar year - 2000
  uint8_t month;        // calendar month, January = 1, February = 2, December = 12
  uint8_t days;         // 0 to 31
  uint8_t hours;        // 0 to 23
  uint8_t minutes;      // 0 to 59
  uint8_t seconds;      // 0 00 59
  uint16_t miliseconds; // 0 to 999
} Time;


struct {
  uint8_t Init_State : 1;         
  uint8_t Idle_State : 1; 
  uint8_t Sleep_State : 1; 
  uint8_t Uart_COM_only : 1;   // Save power, COM only
  uint8_t CAN_COM: 1; 
  uint8_t Drill_Init_State : 1; 
  uint8_t Drill_State : 1; 
  uint8_t Drill_125Hz_State : 1; 
  uint8_t Drill_250Hz_State : 1; 
  uint8_t Burst_State : 1; 
  uint8_t Burst_State_Old : 1; 
  uint8_t Burst_State_New : 1; 
  uint8_t Burst_Paused : 1; 
  uint8_t Super_Burst_Rec : 1; 
  uint8_t Super_Burst_Saved : 1;
  uint8_t Burst_Init_State : 1; 
  uint8_t Time_Sync_Set : 1; 
  uint8_t Time_Sync_Processing : 1; 
  uint8_t Mem_Data_Pointer_Seek_Init : 1;
  uint8_t Mem_Data_Pointer_Seek : 1;
  uint8_t Mem_Event_Pointer_Seek : 1;
} State_Flags;

/*******************************************************************************
 * RTOS 
 ******************************************************************************/
#define RTOS_50us_Step_1ms  0
#define RTOS_50us_Step_2ms  1
#define RTOS_50us_Step_3ms  2
#define RTOS_50us_Step_4ms  3
#define RTOS_50us_Step_5ms  4
#define RTOS_50us_Step_6ms  5
#define RTOS_50us_Step_7ms  6
#define RTOS_50us_Step_8ms  7
uint8_t RTOS_50us_Seguencer = 0; 

uint8_t RTOS_50us_Counter = 0; 

/*******************************************************************************
 * debug
 ******************************************************************************/
uint8_t Burst_To_CAN_Skipper = 0; 



struct {
  uint16_t Test_Burst_Out : 1;    
  uint16_t Read_Burst_Out : 1;
  uint16_t Test_Data_Out:1; 
  uint16_t Read_Data_Out:1; 
  uint16_t Accel_HG_Spit_Out:1; 
} Debug_Flags;

/*******************************************************************************
 * SuperBurst
 ******************************************************************************/

//uint8_t __attribute__((aligned(4)))SuperBurst[1024];

//const uint16_t SuperBurst_Pointer_Max = 1024;
//uint16_t SuperBurst_Pointer = 0;

//#define FIFO_SIZE               7      // Number sample per axis
//#define FIFO_SIZE_3X            42      // 3 x FIFO_SIZE
//uint8_t ADXL373_FIFO[FIFO_SIZE_3X] = {0}; 

//uint8_t __attribute__((aligned(4)))Testo2[512];
/*******************************************************************************
 * SPI
 ******************************************************************************/

//const uint8_t SPI_2_data_timeout_max_count = 5; 
//volatile uint8_t SPI_2_data_timeout_counter = 0; 
//
//const uint8_t SPI_2_TX_timeout_max_count = 5; 
//volatile uint8_t SPI_2_TX_timeout_counter = 0; 
//
//#define SPI_2_RX_Buffer_Length 128
//volatile uint8_t SPI_2_data_buffer[SPI_2_RX_Buffer_Length];
//volatile uint8_t SPI_2_data_Received[SPI_2_RX_Buffer_Length];
//volatile uint8_t SPI_2_data_pointer;
//volatile uint8_t SPI_2_data_TX[SPI_2_RX_Buffer_Length];
//volatile uint8_t SPI_2_data_TX_pointer;
//volatile uint8_t SPI_2_TX_Number_Bytes_To_Send = 0;

//volatile struct
//{
//  uint8_t RX_Started : 1;
//  uint8_t RX_Received : 1;
//  uint8_t RX_Decoded : 1;
//  uint8_t RX_Error : 1;
//  uint8_t RX_Timeout : 1;
//  uint8_t TX_Send : 1;
//  uint8_t TX_Started : 1;
//  uint8_t Boot_Request : 1;
//} SPI_2_Status;



/*******************************************************************************
 * Mag
 ******************************************************************************/
uint8_t Mag_flag = 0; 
uint8_t Magneto_Data[7] = {0}; 

/*******************************************************************************
 * ADXL355
 ******************************************************************************/
//uint8_t ACC355_Seguencer = 0; 
uint8_t Accel_unit = 0; 


/* Accel_LG1_Data[0]  = Temp MSB
 * Accel_LG1_Data[1]  = Temp LSB
 * Accel_LG1_Data[2]  = X
 * Accel_LG1_Data[3]  = X
 * Accel_LG1_Data[4]  = X upper half only 
 * Accel_LG1_Data[5]  = Y
 * Accel_LG1_Data[6]  = Y
 * Accel_LG1_Data[7]  = Y upper half only
 * Accel_LG1_Data[8]  = Z
 * Accel_LG1_Data[9]  = Z
 * Accel_LG1_Data[10] = Z upper half only
 * 
 */

uint8_t Accel_LG1_Data[11] = {0}; 
uint8_t Accel_LG2_Data[11] = {0}; 
uint8_t Accel_LG3_Data[11] = {0}; 



/* ADXL355 registers addresses */
#define ACC355_DEVID_AD                 0x00
#define ACC355_DEVID_MST                0x01
#define ACC355_PARTID                   0x02
#define ACC355_REVID                    0x03
#define ACC355_STATUS                   0x04
#define ACC355_FIFO_ENTRIES             0x05
#define ACC355_TEMP2                    0x06
#define ACC355_TEMP1                    0x07
#define ACC355_XDATA3                   0x08
#define ACC355_XDATA2                   0x09
#define ACC355_XDATA1                   0x0A
#define ACC355_YDATA3                   0x0B
#define ACC355_YDATA2                   0x0C
#define ACC355_YDATA1                   0x0D
#define ACC355_ZDATA3                   0x0E
#define ACC355_ZDATA2                   0x0F
#define ACC355_ZDATA1                   0x10
#define ACC355_FIFO_DATA                0x11
#define ACC355_OFFSET_X_H               0x1E
#define ACC355_OFFSET_X_L               0x1F
#define ACC355_OFFSET_Y_H               0x20
#define ACC355_OFFSET_Y_L               0x21
#define ACC355_OFFSET_Z_H               0x22
#define ACC355_OFFSET_Z_L               0x23
#define ACC355_ACT_EN                   0x24
#define ACC355_ACT_THRESH_H             0x25
#define ACC355_ACT_THRESH_L             0x26
#define ACC355_ACT_COUNT                0x27
#define ACC355_FILTER                   0x28
#define ACC355_FIFO_SAMPLES             0x29
#define ACC355_INT_MAP                  0x2A
#define ACC355_SYNC                     0x2B
#define ACC355_RANGE                    0x2C
#define ACC355_POWER_CONTROL            0x2D
#define ACC355_SELF_TEST                0x2E
#define ACC355_RESET                    0x2F

/*******************************************************************************
 * ADXL373
 ******************************************************************************/
//extern struct {
//    uint16_t Streaming_400g : 1;
//}Accel_400g_Flag;

volatile struct {
    uint8_t Interrupt : 1;
    uint8_t Act_Interrupt : 1;
    uint8_t Inact_Interrupt : 1;
    uint8_t HG_Max_Peak : 1;
}Accel_HG_Flag;
    
uint8_t Accel_HG_Sequencer = 0; 

#define ACC373_Int_Act_Mask             0x20
#define ACC373_Int_Inact_Mask           0x10

#define BURST_TRIGGER_SAMPLE_TIME 4 // 1 ms step
uint8_t Burst_Trigger_Sample_Counter = 0; 

//union
//{
//    struct 
//    {
//        uint8_t Level_25g : 1;
//        uint8_t Level_50g : 1;
//        uint8_t Level_75g : 1;
//        uint8_t Level_100g : 1;
//        uint8_t Level_150g : 1;
//        uint8_t Level_200g : 1;
//        uint8_t Level_250g : 1;
//        uint8_t Level_300g : 1;
//        uint8_t Level_350g : 1;
//        uint8_t Level_400g : 1;
//    };
//    uint8_t All_Level_Flags;
//    
//}Burst_Flag;


struct 
{
    uint8_t Level_25g : 1;
    uint8_t Level_50g : 1;
    uint8_t Level_75g : 1;
    uint8_t Level_100g : 1;
    uint8_t Level_150g : 1;
    uint8_t Level_200g : 1;
    uint8_t Level_250g : 1;
    uint8_t Level_300g : 1;
    uint8_t Level_350g : 1;
    uint8_t Level_400g : 1;
}Burst_Flag;



uint8_t Accel_HG_Max_Peak[5] = {0};

//uint8_t Chip_Select = 0; 
//uint8_t ADXL373_Seguencer = 0; 
//uint16_t Accel_HG_X = 0; 
//uint16_t Accel_HG_Y = 0; 
//uint16_t Accel_HG_Z = 0; 
uint8_t Accel_HG_Data[5] = {0};

#define	ACC373_DEVID_AD         0x00
#define	ACC373_DEVID_MST        0x01
#define	ACC373_PARTID           0x02
#define	ACC373_REVID            0x03
#define	ACC373_STATUS           0x04
#define	ACC373_STATUS2          0x05
#define	ACC373_XDATA_H          0x08
#define	ACC373_XDATA_L          0x09
#define	ACC373_YDATA_H          0x0A
#define	ACC373_YDATA_L          0x0B
#define	ACC373_ZDATA_H          0x0C
#define	ACC373_ZDATA_L          0x0D
#define	ACC373_MAXPEAK_X_H      0x15 
#define	ACC373_MAXPEAK_X_L      0x16 
#define	ACC373_MAXPEAK_Y_H      0x17 
#define	ACC373_MAXPEAK_Y_L      0x18 
#define	ACC373_MAXPEAK_Z_H      0x19 
#define	ACC373_MAXPEAK_Z_L      0x1A 
#define	ACC373_OFFSET_X         0x20
#define	ACC373_OFFSET_Y         0x21
#define	ACC373_OFFSET_Z         0x22
#define	ACC373_THRESH_ACT_X_H	0x23
#define	ACC373_THRESH_ACT_X_L	0x24
#define	ACC373_THRESH_ACT_Y_H	0x25
#define	ACC373_THRESH_ACT_Y_L	0x26
#define	ACC373_THRESH_ACT_Z_H	0x27
#define	ACC373_THRESH_ACT_Z_L	0x28
#define	ACC373_TIME_ACT         0x29
#define	ACC373_THRESH_INACT_X_H	0x2A
#define	ACC373_THRESH_INACT_X_L	0x2B
#define	ACC373_THRESH_INACT_Y_H	0x2C
#define	ACC373_THRESH_INACT_Y_L	0x2D
#define	ACC373_THRESH_INACT_Z_H	0x2E
#define	ACC373_THRESH_INACT_Z_L	0x2F
#define	ACC373_TIME_INACT_H     0x30
#define	ACC373_TIME_INACT_L     0x31
#define	ACC373_THRESH_ACT2_X_H	0x32
#define	ACC373_THRESH_ACT2_X_L	0x33
#define	ACC373_THRESH_ACT2_Y_H	0x34
#define	ACC373_THRESH_ACT2_Y_L	0x35
#define	ACC373_THRESH_ACT2_Z_H	0x36
#define	ACC373_THRESH_ACT2_Z_L	0x37
#define	ACC373_HPF              0x38
#define	ACC373_FIFO_SAMPLES     0x39 
#define	ACC373_FIFO_CTL         0x3A 
#define	ACC373_INT1_MAP         0x3B
#define	ACC373_INT2_MAP         0x3C
#define	ACC373_TIMING           0x3D
#define	ACC373_MEASURE          0x3E
#define	ACC373_POWER_CTL        0x3F
#define	ACC373_SELF_TEST        0x40
#define	ACC373_RESET            0x41
#define ACC373_FIFO_DATA        0x42
/*******************************************************************************
 * ADC_MCP3422
 ******************************************************************************/
// Step 0: convert Ch1
// Step 1: read Ch1
// Step 2: convert Ch2
// Step 3: read Ch2
// Step 4: Roll back
uint8_t ADC_MCP3422_Alt = 0; 

uint16_t Voltage_3V3 = 0; 
uint16_t Voltage_5V = 0; 

#define CAN_VOLTAGE_ABOVE_THRESH            7500
#define DRILLING_VOLTAGE_MAX_THRESH         6500
#define DRILLING_VOLTAGE_ABOVE_THRESH       4300
#define DRILLING_VOLTAGE_BELOW_THRESH       3500
//#define BAT_3V3_VOLTAGE_OVERRIDED_THRESH    4500 // 4500 ???
//#define BAT_3V3_VOLTAGE_HIGH_THRESH         4000
#define BAT_3V3_VOLTAGE_OVERRIDED_THRESH    5500 // debug
#define BAT_3V3_VOLTAGE_HIGH_THRESH         5000 // debug
#define BAT_3V3_VOLTAGE_LOW_THRESH          2900
#define BAT_3V3_VOLTAGE_MIN_THRESH          2800

// Average over 8 samples
//#define NumberSampleVoltAwg  8
//#define NumberSampleVoltDivisor 3

// Average over 4 samples
#define NumberSampleVoltAwg  4
#define NumberSampleVoltDivisor 2

// Average over 2 samples
//#define NumberSampleVoltAwg  2
//#define NumberSampleVoltDivisor 1



uint8_t Avg_Voltage_5V_Pointer = 0;
uint8_t Avg_Voltage_3V3_Pointer = 0; 
uint16_t Sum_Voltage_3V3 = 0; 
uint16_t Sum_Voltage_5V = 0; 
uint16_t Avg_Voltage_5V = 0; 
uint16_t Avg_Voltage_3V3 = 0;  

//union
//{
//    struct 
//    {
//        uint8_t Vol_CAN_Above_Sent : 1;
//        uint8_t Vol_Drill_Above_Sent : 1;
//        uint8_t Vol_Drill_Below_Sent : 1;
//    };
//    uint8_t All_Flags;
//    
//}Volt_5V_Flags;

struct 
{
    uint8_t Vol_CAN_Above_Sent : 1;
    uint8_t Vol_Drill_Above_Sent : 1;
    uint8_t Vol_Drill_Below_Sent : 1;
}Volt_5V_Flags;

//union
//{
//    struct 
//    {
//        uint8_t Vol_3V3_CAN_Sent : 1;
//        uint8_t Vol_3V3_Over_Sent : 1;
//        uint8_t Vol_3V3_Normal_Sent : 1;
//        uint8_t Vol_3V3_Below_Sent : 1;
//    };
//    uint8_t All_Flags;
//    
//}Volt_3V3_Flags;

struct 
{
    uint8_t Vol_3V3_CAN_Sent : 1;
    uint8_t Vol_3V3_Over_Sent : 1;
    uint8_t Vol_3V3_Normal_Sent : 1;
    uint8_t Vol_3V3_Below_Sent : 1;
}Volt_3V3_Flags;



/*******************************************************************************
 * ADC_AD7994
 ******************************************************************************/
#define Gyro_Vol_Min_Threshold 1500

int16_t Gyro_value = 0; 
uint16_t Gyro_temp = 0; 
uint16_t Gyro_Vol_Ref_Unsigned = 0 ;

//uint16_t Current_3V3 = 0; 
//uint16_t Current_5V = 0; 

/*******************************************************************************
 * Memory MT25QL01
 ******************************************************************************/
//const uint8_t MT25QL01_Number_Max = 20; 
const uint8_t MT25QL01_Number_Max = 1; 

const uint16_t MT25QL01_Sector_Max = 2048; // Sector size = 64kB
//const uint16_t MT25QL01_Sector_Max = 256; // Sector size = 64kB

const uint32_t MT25QL01_bytes_Max = 134217728; // 0x08000000
//const uint32_t    MT25QL01_bytes_Max = 16777216; // 0x08000000


uint8_t MT25QL01_In_Used = 1; // show which memory is in
uint32_t MT25QL01_bytes_pointer = 0; 

uint8_t MT25QL01_Read_In_Used = 1; // show which memory is in 
//uint8_t MT25QL01_Read_segment_pointer = 0; 
uint32_t MT25QL01_Read_bytes_pointer = 0; 

uint8_t MT25QL01_Erase_In_Used = 1; // show which memory is in 
uint8_t MT25QL01_To_Erase = 1; // 
//uint8_t MT25QL01_Erase_segment_pointer = 0; 
uint32_t MT25QL01_Erase_bytes_pointer = 0; 

uint8_t MT25QL01_Seek_In_Used = 1; // show which memory is in 
uint32_t MT25QL01_Seek_bytes_pointer = 0; 
uint32_t MT25QL01_Seek_bytes_Start_Reference = 0; 
uint32_t MT25QL01_Seek_bytes_End_Reference = 0; 

#define Memory_2_bytes MT25QL01_bytes_Max >> 1 
#define Memory_4_bytes MT25QL01_bytes_Max >> 2 
#define Memory_8_bytes MT25QL01_bytes_Max >> 3 
#define Memory_16_bytes MT25QL01_bytes_Max >> 4 
#define Memory_32_bytes MT25QL01_bytes_Max >> 5 
#define Memory_64_bytes MT25QL01_bytes_Max >> 6 
#define Memory_128_bytes MT25QL01_bytes_Max >> 7 
#define Memory_256_bytes MT25QL01_bytes_Max >> 8 
#define Memory_512_bytes MT25QL01_bytes_Max >> 9 
#define Memory_1024_bytes MT25QL01_bytes_Max >> 10
#define Memory_2048_bytes MT25QL01_bytes_Max >> 11
#define Memory_4096_bytes MT25QL01_bytes_Max >> 12
#define Memory_8192_bytes MT25QL01_bytes_Max >> 13
#define Memory_16384_bytes MT25QL01_bytes_Max >> 14

uint8_t Memory_Search_Sequencer = 0; 

enum Memory_Search_Step
{
    Memory_X = 0,
    Memory_By_2 = 0,
    Memory_By_4 = 0,
    Memory_By_8 = 0,
    Memory_By_16 = 0,
    Memory_By_32 = 0,
};

//struct {
//    uint8_t Memory_Select : 1;
//    uint8_t Memory_2 : 1;
//    uint8_t Memory_4 : 1;
//    uint8_t Memory_8 : 1;
//    uint8_t Memory_16 : 1;
//    uint8_t Memory_32 : 1;
//    uint8_t Memory_Byte : 1;
//    
//}MT25QL01_Search_Flag;

struct {
    uint16_t Mem_Overflow : 1;
    uint16_t Mem_Fail : 1;
    uint16_t Mem_Busy : 1;
    uint16_t Mem_WEP : 1;
    uint16_t Mem_Wait_Write : 1;  // wait finish to write to clear WEP
    uint16_t Mem_Write : 1;  //
    uint16_t Mem_Test_Write : 1; 
    uint16_t Mem_Test_Read : 1;
    uint16_t Mem_Read : 1;
    uint16_t Mem_Pointer_Set : 1;
    uint16_t Mem_Erase_Request : 1;
    uint16_t Mem_Erase_Pass : 1;
    uint16_t Mem_Erase : 1;
    uint16_t Mem_All_Sleep : 1;
}MT25QL01_Flag;


/*******************************************************************************
 * ToolFace
 ******************************************************************************/
double Tool_Face_phy_float = 0;
double Tool_Face_Old_float = 0;
int32_t Tool_Face_Int32 = 0;
int32_t Tool_Face_Old_Int32 = 0;

/*******************************************************************************
 * Memory Event  - MEM_CY15B064J
 ******************************************************************************/
// memory event buffer
//uint8_t __attribute__((aligned(4)))MemoryEventBuffer[8192];
//uint8_t __attribute__((aligned(4)))MemoryEventBuffer[4096];
//uint8_t __attribute__((aligned(4)))MemoryEventBuffer[3072];
uint8_t __attribute__((aligned(4)))MemoryEventBuffer[2048];
const uint16_t NumberEventMax = 128; // event are 16 bytes
uint8_t NumberEventSaved = 0; // event are 16 bytes
//const uint16_t EventPointerMax = 3072; 
const uint16_t EventPointerMax = 2048; 
uint16_t EventPointerBuffer = 0;
uint16_t EventPointerWriting = 0;

// 4 memories of 8000 bytes
const uint16_t MEM_CY15B064J_64_Slices_Max = 128;
const uint16_t MEM_CY15B064J_bytes_Max = 8192;
const uint8_t MEM_CY15B064J_Number_Max = 3; 

uint8_t MEM_CY15B064J_Write_In_Used = 1; // show which memory is in 
uint16_t MEM_CY15B064J_Write_bytes_pointer = 0; 

uint8_t MEM_CY15B064J_Read_In_Used = 1; // show which memory is in 
uint16_t MEM_CY15B064J_Read_bytes_pointer = 0; 

uint8_t MEM_CY15B064J_Erase_In_Used = 1; // show which memory is in 
//uint32_t MEM_CY15B064J_Erase_bytes_pointer = 0; 

uint8_t MEM_CY15B064J_Seek_In_Used = 1; // show which memory is in 
uint16_t MEM_CY15B064J_Seek_bytes_pointer = 0; 

volatile struct {
    uint16_t Mem_Overflow : 1;
    uint16_t Mem_Fail : 1;
    uint16_t Mem_Busy : 1;
    uint16_t Mem_WEP : 1;
    uint16_t Mem_Wait_Write : 1;  // wait finish to write to clear WEP
    uint16_t Mem_Write : 1;  //
    uint16_t Mem_Test_Write : 1; 
    uint16_t Mem_Test_Read : 1;
    uint16_t Mem_Read : 1;
    uint16_t Mem_End_Read : 1;
    uint16_t Mem_Pointer_Set : 1;
    uint16_t Mem_Erase_Request : 1;
    uint16_t Mem_Erase_Pass : 1;
    uint16_t Mem_Erase : 1;
    uint16_t Mem_All_Sleep : 1;
}MEM_CY15B064J_Flag;

/*******************************************************************************
 * CAN
 ******************************************************************************/
//#define MAX_WORDS 100
//unsigned int __attribute__((aligned(4)))CanTxBuffer[MAX_WORDS];
//
///*Data structure to implement a CANFD message buffer. */
///* CANFD Message Time Stamp */
//typedef unsigned long CANFD_MSG_TIMESTAMP;
//
///* CAN TX Message Object Control*/
//typedef struct _CANFD_TX_MSGOBJ_CTRL {
//    unsigned DLC:4;
//    unsigned IDE:1;
//    unsigned RTR:1;
//    unsigned BRS:1;
//    unsigned FDF:1;
//    unsigned ESI:1;
//    unsigned SEQ:23;
//    unsigned unimplemented1:16;
//} CANFD_TX_MSGOBJ_CTRL;
//
///* CANFD TX Message ID*/
//typedef struct _CANFD_MSGOBJ_ID {
//    unsigned SID:11;
//    unsigned long EID:18;
//    unsigned SID11:1;
//    unsigned unimplemented1:2;
//} CANFD_MSGOBJ_ID;
//
///* CAN TX Message Object*/
//typedef union _CANFD_TX_MSGOBJ {
//    struct {
//        CANFD_MSGOBJ_ID id;
//        CANFD_TX_MSGOBJ_CTRL ctrl;
//        CANFD_MSG_TIMESTAMP timeStamp;
//    } bF;
//    unsigned int word[4];
//    unsigned char byte[8];
//} CANFD_TX_MSGOBJ;

////////////////////////////////////////////////////////////////////

//uint8_t volatile SPI_2_data_buffer_test[128] = {0};
//uint8_t volatile SPI_2_data_pointer_test = 0; 
//uint8_t volatile SPI_2_RX_Flag = 0; 

/*******************************************************************************
 End of File
 */