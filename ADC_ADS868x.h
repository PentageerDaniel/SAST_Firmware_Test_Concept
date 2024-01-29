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
void ADC_ADS868x_INIT(void); 
uint8_t Get_ADC_ADS868x_Device_ID(uint8_t chip_select);
uint8_t SET_ADC_ADS868x_Device_ID(uint8_t chip_select, uint8_t device_ID);

uint8_t SET_ADC_ADS868x_RANGE(uint8_t chip_select, uint8_t range); 
uint16_t Get_ADC_ADS868x_RANGE(uint8_t chip_select);

uint8_t SET_ALARM_H_TH_REG(uint8_t chip_select, uint8_t INP_ALRM_HYST, uint16_t INP_ALRM_HIGH_TH);
uint8_t GET_ALARM_H_TH_REG(uint8_t chip_select);

uint16_t ADC_ADS868x_READ_DATA(uint8_t chip_select); 
uint8_t SET_ADC_ADS868x_DATAOUT_CTL(uint8_t chip_select); 
////////////////////////////////////////////////////////////////////////////////

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


/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
#define ADS868x_NOP_CMD             0x00  // 
#define ADS868x_CLEAR_HWORD_CMD     0xC0 
#define ADS868x_READ_HWORD_CMD      0xC8 
#define ADS868x_READ_CMD            0x48 
#define ADS868x_WRITE_2BYTES_CMD    0xD0 
#define ADS868x_WRITE_1BYTE_MS_CMD  0xD2 
#define ADS868x_WRITE_1BYTE_LS_CMD  0xD4 
#define ADS868x_SET_HWORD_CMD       0xD8


#define ADS868x_DEVICE_ID_REG       0x00 
#define ADS868x_RST_PWRCTL_REG      0x04 
#define ADS868x_SDI_CTL_REG         0x08 
#define ADS868x_SDO_CTL_REG         0x0C 
#define ADS868x_DATAOUT_CTL_REG     0x10 
#define ADS868x_RANGE_SEL_REG       0x14 
#define ADS868x_ALARM_REG           0x20 
#define ADS868x_ALARM_H_TH_REG      0x24
#define ADS868x_ALARM_L_TH_REG      0x28



/* *****************************************************************************
 End of File
 */