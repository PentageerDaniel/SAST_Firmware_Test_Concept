/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Pentageer

  @File Name
    ADC_ADS868x.h

  @Summary
 

  @Description
    Describe the purpose of this file.
*/
/* ************************************************************************** */

/*************************************************************************
 * Include
 ************************************************************************/
#include "Init.h"

/*******************************************************************************
 * Internal Function declaration 
 ******************************************************************************/
uint8_t SET_ADC_ADS863x_POWER_UP(uint8_t chip_select);
uint8_t Get_ADC_ADS863x_AUX_CONFIG(uint8_t chip_select);
uint8_t SET_ADC_ADS863x_AUX_CONFIG(uint8_t chip_select); 
uint8_t SET_ADC_ADS863x_RANGE(uint8_t chip_select, uint8_t range);
uint8_t Get_ADC_ADS863x_RANGE(uint8_t chip_select);
uint8_t SET_ADC_ADS863x_PAGE(uint8_t chip_select, uint8_t page); 
uint16_t ADC_ADS863x_READ_DATA(uint8_t chip_select, uint8_t channel); 
/*******************************************************************************
 * External Function declaration 
 ******************************************************************************/

extern void init_SPI_2(void); 
extern void Set_All_Chip_Select(void); 
extern void init_SPI_2_slave(void); 
extern uint8_t write_bytes_SPI_2(uint8_t *data, uint8_t length);
extern uint8_t read_1_byte_SPI_2(uint8_t *cmd, uint8_t len); 
extern uint8_t * read_bytes_SPI_2(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
extern uint8_t read_SPI_2(uint8_t cmd);
extern uint8_t  read_SPI_2_Debug(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_1_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern void *malloc(size_t size);
extern uint8_t SPI_2_Routine_Write_ret_UART(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
extern int SPI_2_Write_Test(int);
extern uint8_t SPI_2_Write_Slave(uint8_t cmd);
extern uint32_t SPI_2_Routine_Ret_32(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 

extern uint8_t SPI_1_Routine_Read_(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern uint8_t SPI_2_Routine_Read_(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern uint8_t SPI_3_Routine_Read_(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);

extern void set_SS_Accel(uint8_t cs_port);
extern void disable_SS_Accel(uint8_t cs_port);
/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
#define ADS863x_POWER_UP                      0x02
#define ADS863x_READ_DATA_MANUAL              0x04
#define ADS863x_AUX_CONFIG                    0x06
#define ADS863x_CH0_RANGE_CMD                 0x10  // 
#define ADS863x_CH1_RANGE_CMD                 0x11  // 
#define ADS863x_CH2_RANGE_CMD                 0x12  // 
#define ADS863x_CH3_RANGE_CMD                 0x13  // 
#define ADS863x_PAGE_SELECT_CMD               0x7F  // 
