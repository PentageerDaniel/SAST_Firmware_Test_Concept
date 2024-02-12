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
 *      Init.h
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/

/*************************************************************************
 * Include
 ************************************************************************/

#include <xc.h>
#include <stddef.h>
//#include "Uart.h"


/*************************************************************************
 * Pre processing Definition
 ************************************************************************/
#define CAN_Debug_Message     1 // display CAN debug display message

//#define Uart1_Debug_Message   1 // display CAN debug display message

#define Memory_Data_Sleep_Override  1 // Memory with not go to sleep

#define Test_Only  1 // different setting for vibe test

//#define Debug_Board         1
/*************************************************************************
 * Definition
 ************************************************************************/

#define true    1
#define false   0
//#define SYS_FREQ 8000000 // Running at 8MHz 

//#define Timer2Flag      IFS0bits.T2IF

//#define CS_USB PORTAbits.RA0   

//#define Buffer_Uart_Msg_Flag DMAINT2bits.DBUFWF 
#define Buffer_Uart_Msg_Flag IFS1bits.DMA2IF
//typedef unsigned char  UByte8; 
//typedef short          Word16;
//typedef unsigned short UWord16;
//typedef long           Word32;
//typedef unsigned long  UWord32;



typedef union tuReg32
{
	uint32_t Val32;

	struct
	{
		uint16_t LW;
		uint16_t HW;
	} Word;

	char Val[4];
} uReg32;

/*************************************************************************
 * Definition Ports
 ************************************************************************/
//#ifdef Debug_Board
//#define LEDG            PORTCbits.RC1
//#define LEDR            PORTCbits.RC2
//#endif
#define CTL_CS_A0       PORTAbits.RA0
#define CTL_CS_A1       PORTAbits.RA1
#define CTL_CS_A2       PORTAbits.RA2
#define CTL_CS_A3       PORTAbits.RA3
#define CTL_CS_A4       PORTAbits.RA4
//#define xxx           PORTAbits.RA2
//#define xxx           PORTAbits.RA2
//#define CS_USB          PORTAbits.RA3 
//#define CS_ESP          PORTAbits.RA4 

#define Accel_HG_Int    PORTBbits.RB1 // RP33
//#define Accel_LG1_Int   PORTBbits.RB2 // RP34
#define Gyro_Enable     PORTBbits.RB2 // RP34

//#define Debug_PIN_TX1   PORTBbits.RB4 // 

//#define ADC_Alert       PORTBbits.RB7 // 
//#define Xtal_Enable       PORTBbits.RB7 // 

#define Sleep_CTL       PORTBbits.RB10 // OSC 

#define CTL_CS_WR       PORTBbits.RB13 // CTL_CS_WR

//#define GPIO_USB_3      PORTCbits.RC1 
//#define GPIO_USB_2      PORTCbits.RC2 

#define Debug_PIN_TX1    PORTCbits.RC12 

#define ADC_VOLT_PD     PORTDbits.RD1 
#define CS_CONT         PORTDbits.RD10 

#define CAN_Enable      PORTDbits.RD13 


/////////////////////// SPI Chip Select ///////////////////////////
//#ifdef Debug_Board
//#define CS_MEM1      PORTCbits.RC7
//#define CS_MEM2      PORTBbits.RB13
////#define CS_MEM3      PORTCbits.RC3
////#define CS_MEM4      PORTDbits.RD1
////#define CS_MEM5      PORTCbits.RC13
////#define CS_MEM6      PORTCbits.RC5
////#define CS_MEM7      PORTCbits.RC0
////#define CS_MEM8      PORTCbits.RC2
////#define CS_MEM9      PORTCbits.RC11
////#define CS_MEM10     PORTBbits.RB11
////#define CS_MEM11     PORTAbits.RA2
////#define CS_MEM12     PORTCbits.RC10
////#define CS_MEM13     PORTCbits.RC1
////#define CS_MEM14     PORTCbits.RC6
////#define CS_MEM15     PORTAbits.RA1
////#define CS_MEM16     PORTCbits.RC4
////#define CS_MEM17     PORTAbits.RA0
////#define CS_MEM18     PORTDbits.RD10
////#define CS_MEM19     PORTCbits.RC12
////#define CS_MEM20     PORTBbits.RB12
//#define CS_ACC_LG1   PORTAbits.RA4
//#define CS_ACC_HG    PORTAbits.RA3


//enum SPI_CS
//{
//    SPI_CS_MEM1 = 1,
//    SPI_CS_MEM2,
//    na3,             //    SPI_CS_MEM3,
//    na4,             //    SPI_CS_MEM4,
//    na5,             //    SPI_CS_MEM5,
//    na6,             //    SPI_CS_MEM6,
//    na7,             //    SPI_CS_MEM7,
//    na8,             //    SPI_CS_MEM8,
//    na9,             //    SPI_CS_MEM9,
//    na10,             //    SPI_CS_MEM10,
//    na11,             //    SPI_CS_MEM11,
//    na12,             //    SPI_CS_MEM12,
//    na13,             //    SPI_CS_MEM13,
//    na14,             //    SPI_CS_MEM14,
//    na15,             //    SPI_CS_MEM15,
//    na16,             //    SPI_CS_MEM16,
//    na17,             //    SPI_CS_MEM17,
//    na18,             //    SPI_CS_MEM18,
//    na19,             //    SPI_CS_MEM19,
//    na20,             //    SPI_CS_MEM20,
//    SPI_CS_ACC_LG1,
//    SPI_CS_ACC_HG,
//}; 
//#else
//#define CS_MEM1      PORTCbits.RC7
//#define CS_MEM2      PORTBbits.RB13
//#define CS_MEM3      PORTCbits.RC3
//#define CS_MEM4      PORTDbits.RD1
//#define CS_MEM5      PORTCbits.RC13
//#define CS_MEM6      PORTCbits.RC5
//#define CS_MEM7      PORTCbits.RC0
//#define CS_MEM8      PORTCbits.RC2
//#define CS_MEM9      PORTCbits.RC11
//#define CS_MEM10     PORTBbits.RB11
//#define CS_MEM11     PORTAbits.RA2
//#define CS_MEM12     PORTCbits.RC10
//#define CS_MEM13     PORTCbits.RC1
//#define CS_MEM14     PORTCbits.RC6
//#define CS_MEM15     PORTAbits.RA1
//#define CS_MEM16     PORTCbits.RC4
//#define CS_MEM17     PORTAbits.RA0
//#define CS_MEM18     PORTDbits.RD10
//#define CS_MEM19     PORTCbits.RC12
//#define CS_MEM20     PORTBbits.RB12
//#define CS_ACC_LG1   PORTAbits.RA4
//#define CS_ACC_HG    PORTAbits.RA3


enum SPI_CS
{
    SPI_CS_MEM1 = 1,
    SPI_CS_MEM2,
    SPI_CS_ACC_LG1,
    SPI_CS_ACC_LG2,
    SPI_CS_ACC_HG,
    SPI_CS_GYRO,
    SPI_CS_VOLT,
    SPI_CS_MAG,
    SPI_CS_SRAM1,
    SPI_CS_SRAM2,
}; 
//#endif
/*******************************************************************************
 * Local Function
 ******************************************************************************/
//void init_interrupt(void);
void initialize_mcu(void); 
void init_port(void);    
void init_interrupt(void); 
void set_interrupt_Enable(void);
void init_osc_External(void);
void init_osc_Internal(void);
////void init_osc_low_speed(); 

void init_sleep(void); 
void Enable_Sleep_Interrupt(void);
void Disable_Sleep_Interrupt(void);
void Go_To_Sleep(void);
void Wake_up_Fx(void); 

void init_timer_1(void); 
void init_timer_2(void);
void init_timer_3(void);
void init_timer_4(void);
void start_timer_4(void);
void stop_timer_4(void);

void init_ref_clock(void); 

void init_watch_dog(void);
void start_watch_dog(void);
void stop_watch_dog(void);

void init_Dead_Man_timer(void);
void Reset_Dead_Man_timer(void);

void Get_Version_Firmware(uint8_t *buffer); 

void Start_Timer_3(uint32_t microSec);
uint8_t Check_Timer_3(void);
void Stop_Timer_3(void); 

void IO_Ports_Setting(void); 

void State_Machine_Reset(void);
void Init_Drill_State(void); 
void Init_Idle_State(void); 

void Disabled_All_Sensors(void); 

void Fill_Data_Array(uint8_t *input, uint8_t *output, uint8_t pointer, uint8_t length); 
void Get_Voltage_3V3_5V(void); 
void Voltage_5V_Level_Check(uint16_t volt5V); 
void Voltage_3V3_Level_Check(uint16_t volt3V3); 
void Set_Burst_Array(uint8_t *data, uint8_t length); 
void Read_Sensors(void); 

void Set_Burst_Writing(void);

void RTOS_50us_Routine_250Hz(void); 
void RTOS_50us_Routine_125Hz(void); 

void Fill_Array_For_Writing(void);
void Write_To_Memory(uint8_t *buffer_L, uint8_t *buffer_H); 
void Read_Memory(void); 

void Save_Event_Buffer(uint8_t packetID, uint8_t event, uint8_t *data); 
void Save_Event_Cmd_Buffer(uint8_t packetID, uint8_t event); 
//void Write_Event_I2C_Mem(uint8_t NumberEvenToWrite); 

void Test_Calc_TF(void); 
void Calculation_TF(void); 

void Time_Sync(void); 
int32_t Multiplication(int x, int y); 
signed long __builtin_mulss(const signed int p0, const signed int p1);


void Mag_Rotation_Det_Routine(uint8_t mag_data_MSB,uint8_t mag_data_LSB);
void Mag_Rotation_Det_Reset(void);


void Time_Adjustment(void); 

//void Init(void); 
//void PutChar(unsigned char);
//void GetChar(void);
//void WriteBuffer(unsigned char * ptrData, unsigned char cmd, unsigned char data_len); 
//void Set_GPIO_USB_3(void);
//void Clear_GPIO_USB_3(void);
//void simple_delay(void); 
//void Goto_User_code(void);
//void ReadPM(char *, uReg32);
//void WritePM(uint8_t *, uReg32);
//void Fill_Buffer_Flash(uint8_t *data, uint16_t data_len); 
//void read_uart_1(unsigned char  uart_1_data_byte);
//void reset_uart_1_registers(void); 
//void decode_uart_1_message(void); 
//void write_string_uart_1(unsigned char *str, unsigned char length); 
/*******************************************************************************
 * External Function declaration
 ******************************************************************************/
extern void init_uart_1(void); 
extern void init_uart_1_DMA();
extern void write_uart_1(uint8_t c);
extern void write_string_uart_1(uint8_t *str, uint8_t length);
extern void read_uart_1(uint8_t data); 
extern void reset_uart_1_registers(void); 
extern void uart_1_send_message(uint8_t command, uint8_t *data, uint16_t data_len);
extern void uart_1_send_message_timed(uint8_t command, uint8_t *data, uint8_t data_len);
extern void decode_uart_1_message(void);
extern uint8_t GetChar(void); 
extern void init_uart_2(void); 
extern void init_uart_2_DMA(void); 
extern void write_uart_2(char c);
extern void write_string_uart_2(uint8_t *str, uint8_t length);
extern uint8_t Dtect_MWD_Msg_Decoding(uint8_t *buffer, uint8_t length);

//extern void init_ADC(void); 
//extern int Get_ADC_AN0(void); 
//extern int Get_ADC_AN1(void);
//extern int Get_ADC_AN2(void);
//extern int Get_ADC_AN3(void);
//extern int Get_ADC_Share_4(); 
//extern int read_ADC_Share_4(); 
//extern int read_ADC_AN1();

extern void CRC_Init(void); 
extern uint16_t CRC_ChecksumByte(uint8_t *data, uint8_t Number_of_bytes, uint16_t prev_CRC); 


extern void init_SPI_1(void); 
extern void init_SPI_2(void); 
extern void init_SPI_3(void); 
extern void Set_All_Chip_Select(void); 
extern void init_SPI_2_slave(void); 
extern uint8_t write_bytes_SPI_2(uint8_t *data, uint8_t length);
extern uint8_t read_1_byte_SPI_2(uint8_t *cmd, uint8_t len); 
extern uint8_t * read_bytes_SPI_2(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
extern uint8_t read_SPI_2(uint8_t cmd);
extern uint8_t  read_SPI_2_Debug(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_1_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_3_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern void *malloc(size_t size);
extern uint8_t SPI_2_Routine_Write_ret_UART(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
extern int SPI_2_Write_Test(int);
extern uint8_t SPI_2_Write_Slave(uint8_t cmd);
extern uint32_t SPI_2_Routine_Ret_32(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
extern uint8_t SPI_1_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern uint8_t SPI_2_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern uint8_t SPI_3_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern void read_SPI_2_Slave(uint8_t  SPI_2_data_byte); 
extern void reset_SPI_2_registers(void); 
extern void decode_SPI_2_message(void); 
extern void SPI_2_send_message(uint8_t command, uint8_t *data, uint16_t data_len);

//extern void GD5F2GQ5_Read_ID(void); 
//extern void GD5F2GQ5_Write_Enable(void); 
//extern void GD5F2GQ5_Write_Disable(void); 
//extern void GD5F2GQ5_Write_Bytes(uint8_t *data, uint8_t length); 
//extern uint16_t GD5F2GQ5_Get_Status(void);
//extern void GD5F2GQ5_Read_Routine(void); 
//extern uint8_t GD5F2GQ5_Get_feature_2(void); 


extern void ADXL355_SPI_Init(void);
extern uint8_t Get_Accel_Device_ID(uint8_t chip_select);
extern uint8_t ADXL355_SPI_Read_Accel_Device_Register(uint8_t register_to_read); 
extern void ADXL355_SPI_Write_Accel_Device_Register(uint8_t register_address, uint8_t register_value);
extern void ADXL355_SPI_Start_Sensor(uint8_t chip_select);
extern void ADXL355_SPI_Stop_Sensor(uint8_t chip_select); 
extern uint8_t ADXL355_SPI_Get_Data(uint8_t chip_select, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);


extern void ADXL355_I2C_Init(uint8_t address);
extern uint8_t ADXL355_I2C_ID(uint8_t address); 
extern void ADXL355_I2C_Stop_Sensor(uint8_t address);
extern void ADXL355_I2C_Start_Sensor(uint8_t address);
extern void ADXL355_I2C_Set_Range(uint8_t address, uint8_t range);
extern void ADXL355_I2C_Data_Scan(uint8_t address); 
extern void ADXL355_Get_Data(uint8_t index); 
extern uint8_t ADXL355_I2C_Read_Register(uint8_t address, uint8_t reg); 

extern void ADXL373_SPI_Init(void);
extern void ADXL373_SPI_Init_Wake_Up_Mode(void);
extern uint8_t ADXL373_SPI_ID(uint8_t cs_port);
extern void ADXL373_SPI_Start_Sensor(void);
extern void ADXL373_SPI_Stop_Sensor(void);
extern void ADXL373_Shift_Data(uint8_t *input, uint8_t *output); 
extern uint8_t ADXL373_SPI_Get_Data(uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern void ADXL373_SPI_Check_Level(const uint8_t *buffer);
extern uint8_t ADXL373_SPI_Get_Interrupt(void);
extern void ADXL373_SPI_Get_Max_Peak(void); 
extern uint8_t ADXL373_SPI_Get_Register(uint8_t reg); 
extern uint8_t ADXL373_Read_Fifo(void); 
//
//extern void MT25QL02GCBB_Write_Bytes(uint8_t *data, uint8_t length); 
//extern void MT25QL02GCBB_Read_Bytes(void); 
//
//extern uint8_t Get_ADC_HG_Accel_Streaming_Flag(void);
//extern void Set_ADC_HG_Accel_Streaming_Flag(uint8_t status);
//void HG_Accel_ADC_To_Uart(void); 
//
//extern void init_ISM330(void); 
//extern void ISM330_Get_Data(); 
//

extern void init_CAN_1(void); 
extern void CAN_Send_MSG_Test(void); 
extern void CAN_Send_MSG(uint8_t destination, uint8_t *data, uint8_t length); 
extern void CAN_Received_To_Uart(void); 
extern void CAN_Decode_Received(void); 
extern void CAN_Encode_Sending(uint8_t destination, uint8_t command, uint8_t *data, uint16_t data_len); 

extern void init_MAG_MMC5983MA(void); 
extern uint8_t MAG_MMC5983MA_read_ID(void);
extern void MAG_MMC5983MA_Get_data(void); 
extern void MAG_MMC5983MA_Write_data_SPI(uint8_t *buffer, uint8_t data_len); 
extern uint8_t MAG_MMC5983MA_Get_data_SPI(uint8_t *buffer, uint8_t data_len);
extern void MAG_MMC5983MA_Set_Sampling_Continuous(void);
extern void MAG_MMC5983MA_Disable_Sampling_Continuous(void);

extern void Init_DMA(void); 
extern void DMA_Channel_0(void); 
extern void DMA_Channel_1(void); 
extern void DMA_Channel_2(void); 

extern void MEM_MT25QL01_Init(void); 
extern uint8_t MEM_MT25QL01_Read_ID(uint8_t cs_port, uint8_t *buffer);
extern uint8_t MEM_MT25QL01_Enter_Deep_Power_Down(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Release_Deep_Power_Down(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Enter_4_Bytes_Mode(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Get_Status(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Get_Flag(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Read_Freeze_Bit(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Write_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length); 
extern void MEM_MT25QL01_Write_Enable(uint8_t cs_port);
extern void MEM_MT25QL01_Write_Disable(uint8_t cs_port); 
extern void MEM_MT25QL01_Init_Read(void);
extern uint8_t MEM_MT25QL01_Reading_Swap(void);
extern uint8_t MEM_MT25QL01_Writing_Swap(void); 
extern void MEM_MT25QL01_Read_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length);
extern void MEM_MT25QL01_End_Read(void); 
extern void MEM_MT25QL01_Erase_Memory_Init(void); 
extern uint8_t MEM_MT25QL01_Erase_Memory(uint8_t memory_to_erase);
extern void MEM_MT25QL01_Pointer_Seaching(void); 
extern uint16_t MEM_MT25QL01_Check_Status_Sleep(uint8_t memory_to_check); 
extern void MEM_MT25QL01_Wake_UP_All_Memory(void);
extern void MEM_MT25QL01_Shutdowm_All_Memory(void); 


extern void MUX1_ADG732_INIT(void); 
extern void MUX1_ADG732_CHIP_SELECT(uint8_t port);
extern void MUX1_ADG732_CHIP_DESELECT(uint8_t port);


extern void ADC_ADS868x_INIT(void); 
extern uint8_t Get_ADC_ADS868x_Device_ID(uint8_t chip_select);
extern uint8_t SET_ADC_ADS868x_Device_ID(uint8_t chip_select, uint8_t device_ID);
extern uint8_t SET_ADC_ADS868x_RANGE(uint8_t chip_select, uint8_t range); 
extern uint16_t Get_ADC_ADS868x_RANGE(uint8_t chip_select);
extern uint8_t SET_ALARM_H_TH_REG(uint8_t chip_select, uint8_t INP_ALRM_HYST, uint16_t INP_ALRM_HIGH_TH);
extern uint8_t GET_ALARM_H_TH_REG(uint8_t chip_select);
extern uint16_t ADC_ADS868x_READ_DATA(uint8_t chip_select); 
extern uint8_t SET_ADC_ADS868x_DATAOUT_CTL(uint8_t chip_select); 

extern uint8_t SET_ADC_ADS863x_POWER_UP(uint8_t chip_select);
extern uint8_t Get_ADC_ADS863x_AUX_CONFIG(uint8_t chip_select); 
extern uint8_t SET_ADC_ADS863x_AUX_CONFIG(uint8_t chip_select); 
extern uint8_t SET_ADC_ADS863x_RANGE(uint8_t chip_select, uint8_t range);
extern uint8_t Get_ADC_ADS863x_RANGE(uint8_t chip_select);
extern uint8_t SET_ADC_ADS863x_PAGE(uint8_t chip_select, uint8_t page); 
extern uint16_t ADC_ADS863x_READ_DATA(uint8_t chip_select, uint8_t channel); 
/*******************************************************************************
 * Game over
 ******************************************************************************/
