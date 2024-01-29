/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
#include "Init.h"
#include <stdio.h>
#include <stdlib.h>


//#define CS_USB PORTAbits.RA0  


/*******************************************************************************
 * Function declaration access externally
 ******************************************************************************/
void init_SPI_1(void); 
void init_SPI_2(void); 
void init_SPI_3(void); 
void Set_All_Chip_Select(void); 
void init_SPI_2_slave(void); 
uint8_t write_bytes_SPI_2(uint8_t *data, uint8_t length);
uint8_t read_1_byte_SPI_2(uint8_t *cmd, uint8_t len); 
uint8_t * read_bytes_SPI_2(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
uint8_t read_SPI_2(uint8_t cmd);
uint8_t  read_SPI_2_Debug(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
uint8_t SPI_1_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
uint8_t SPI_3_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
void *malloc(size_t size);
uint8_t SPI_2_Routine_Write_ret_UART(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
int SPI_2_Write_Test(int);
uint8_t SPI_2_Write_Slave(uint8_t cmd);
uint32_t SPI_2_Routine_Ret_32(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 

uint8_t SPI_1_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
uint8_t SPI_2_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
uint8_t SPI_3_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);

void read_SPI_2_Slave(uint8_t  SPI_2_data_byte); 
void reset_SPI_2_registers(void); 
void decode_SPI_2_message(void); 
void SPI_2_send_message(uint8_t command, uint8_t *data, uint16_t data_len);

/*******************************************************************************
 * internal Function declaration
 ******************************************************************************/
void set_SS_Accel(uint8_t cs_port);
void disable_SS_Accel(uint8_t cs_port);

/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/

extern uint8_t Last_MEM_Status; 
extern void DelayUs(uint16_t us); 

extern const uint8_t SPI_2_data_timeout_max_count; 
extern volatile uint8_t SPI_2_data_timeout_counter; 

extern const uint8_t SPI_2_TX_timeout_max_count; 
extern volatile uint8_t SPI_2_TX_timeout_counter; 

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

extern void MUX1_ADG732_INIT(void); 
extern void MUX1_ADG732_CHIP_SELECT(uint8_t port);
extern void MUX1_ADG732_CHIP_DESELECT(uint8_t port);

/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
#define CS_ACC_1    1
#define CS_ACC_2    2
#define CS_ACC_3    4
// 1 == CS_ACC_1
// 2 == CS_ACC_2
// 4 == CS_ACC_3
extern uint8_t Chip_Select; 

/* *****************************************************************************
 End of File
 */