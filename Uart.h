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

/******************************************************************************
 * Local Function
 ******************************************************************************/

void init_uart_1(void);
void init_uart_1_DMA();
void write_uart_1(uint8_t c);
void write_string_uart_1(uint8_t *str, uint8_t length);
void read_uart_1(uint8_t data);
void reset_uart_1_registers(void);
void uart_1_send_message(uint8_t command, uint8_t *data, uint16_t data_len);
void uart_1_send_message_timed(uint8_t command, uint8_t *data, uint8_t data_len);
void decode_uart_1_message(void);
uint8_t GetChar(void); 

void init_uart_2(void); 
void init_uart_2_DMA(void); 
void write_uart_2(char c);
void write_string_uart_2(uint8_t *str, uint8_t length);

void init_uart_3(void); 
void write_uart_3(char c);
void write_string_uart_3(uint8_t *str, uint8_t length);

uint8_t Dtect_MWD_Msg_Decoding(uint8_t *buffer, uint8_t length); 
/******************************************************************************
 * External Function
 ******************************************************************************/
extern void Set_GPIO_USB_3(void);
extern void Clear_GPIO_USB_3(void);
extern uint16_t CRC_ChecksumByte(uint8_t *data, uint8_t Number_of_bytes, uint16_t prev_CRC); 
/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
#define Uart_RX_Buffer_Length 128
extern volatile uint8_t Uart_1_data_buffer[Uart_RX_Buffer_Length];
extern volatile uint8_t Uart_1_data_Received[Uart_RX_Buffer_Length];
extern volatile uint8_t Uart_1_data_pointer;
extern volatile struct
{
  uint8_t RX_Started : 1;
  uint8_t RX_Received : 1;
  uint8_t RX_Decoded : 1;
  uint8_t RX_Error : 1;
  uint8_t RX_Timeout : 1;
  uint8_t TX_Send : 1;
  uint8_t TX_Error : 1;
  uint8_t Boot_Request : 1;
} Uart_1_Status;

// extern struct Uart_1_Status;

// extern const uint8_t Uart_1_data_timeout_max_count = 50;
extern volatile uint8_t Uart_1_data_timeout_counter;

extern volatile struct
{
  uint16_t days;        // 0 to 365
  uint8_t hours;        // 0 to 24
  uint8_t minutes;      // 0 to 60
  uint8_t seconds;      // 0 00 60
  uint16_t miliseconds; // 0 to 1000
} Time;

extern struct
{
  uint16_t Mem_Overflow : 1;
  uint16_t Mem_Fail : 1;
  uint16_t Mem_Busy : 1;
  uint16_t Mem_WEP : 1;
  uint16_t Mem_Wait_Write : 1; // wait finish to write to clear WEP
  uint16_t Mem_Test : 1;
} Memory_Flag;

extern struct
{
  uint16_t Streaming_400g : 1;
} Accel_400g_Flag;


#define SPI_2_RX_Buffer_Length 128
extern volatile uint8_t SPI_2_data_buffer[SPI_2_RX_Buffer_Length];
extern volatile uint8_t SPI_2_data_Received[SPI_2_RX_Buffer_Length];
extern volatile uint8_t SPI_2_data_pointer;
extern volatile uint8_t SPI_2_data_TX[SPI_2_RX_Buffer_Length];
extern volatile uint8_t SPI_2_data_TX_pointer;
extern volatile uint8_t SPI_2_TX_Number_Bytes_To_Send;
extern volatile struct
{
  uint8_t RX_Started : 1;
  uint8_t RX_Received : 1;
  uint8_t RX_Decoded : 1;
  uint8_t RX_Error : 1;
  uint8_t RX_Timeout : 1;
  uint8_t TX_Send : 1;
  uint8_t TX_Started : 1;
  uint8_t TX_Ready : 1;
  uint8_t Boot_Request : 1;
  uint8_t Output_USB_2 : 1;
  uint8_t Output_USB_3 : 1;
} SPI_2_Status;
/*******************************************************************************
 * ISM330_
 ******************************************************************************/
extern struct
{
  uint16_t Streaming_ACCLD : 1;
  uint16_t Streaming_GyroLD : 1;
} ISM330_Flags;
/* *****************************************************************************
 End of File
 */