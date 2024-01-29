/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    MAG_MMC5983MA.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
#include "init.h"

#define MMC5983MA_addr 0x30

/*******************************************************************************
 * Internal Function declaration 
 ******************************************************************************/
void init_MAG_MMC5983MA(void); 
uint8_t MAG_MMC5983MA_read_ID(void);
void MAG_MMC5983MA_Get_data(void); 

void MAG_MMC5983MA_Write_data_SPI(uint8_t *buffer, uint8_t data_len); 
uint8_t MAG_MMC5983MA_Get_data_SPI(uint8_t *buffer, uint8_t data_len); 

/*******************************************************************************
 * external Variable and Function declaration
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
extern uint8_t SPI_3_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
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
#define MMC5983MA_Write_Bit     0x00
#define MMC5983MA_Read_Bit      0x80

/* MMC5983MA registers addresses */
#define MMC5983MA_X_OUT_0       0x00
#define MMC5983MA_X_OUT_1       0x01
#define MMC5983MA_Y_OUT_0       0x02
#define MMC5983MA_Y_OUT_1       0x03
#define MMC5983MA_Z_OUT_0       0x04
#define MMC5983MA_Z_OUT_1       0x05
#define MMC5983MA_XYZ_18_BIT    0x06
#define MMC5983MA_TEMP_OUT      0x07
#define MMC5983MA_STATUS        0x08
#define MMC5983MA_INT_CTL_0     0x09
#define MMC5983MA_INT_CTL_1     0x0A
#define MMC5983MA_INT_CTL_2     0x0B
#define MMC5983MA_INT_CTL_3     0x0C
#define MMC5983MA_ID            0x2F

