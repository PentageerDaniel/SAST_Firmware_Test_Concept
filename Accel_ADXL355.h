/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    ADXL355.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include "init.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Function declaration access externally
 ******************************************************************************/

void ADXL355_Data_Scan(void); 
uint8_t Get_Accel_Device_ID(uint8_t chip_select);
uint8_t ADXL355_SPI_Read_Accel_Device_Register(uint8_t register_to_read);
void ADXL355_SPI_Write_Accel_Device_Register(uint8_t register_address, uint8_t register_value);
void ADXL355_Multiple_Reading(void);
void ADXL355_Read_Fifo(uint8_t fifo_count); 
uint8_t ADXL355_Get_Streaming(void);
void ADXL355_Set_Streaming(uint8_t status);
void ADXL355_Get_Data(uint8_t index); 

void ADXL355_SPI_Init(void);
void ADXL355_SPI_Start_Sensor(uint8_t chip_select);
void ADXL355_SPI_Stop_Sensor(uint8_t chip_select); 
uint8_t ADXL355_SPI_Get_Data(uint8_t chip_select, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);

/*******************************************************************************
 * internal Function declaration
 ******************************************************************************/
int32_t ADXL355_Acceleration_Data_Conversion (uint32_t ui32SensorData); 

/*******************************************************************************
 * external Function declaration
 ******************************************************************************/
extern uint8_t write_bytes_SPI_2(uint8_t *data, uint8_t length);
extern uint8_t * read_bytes_SPI_2(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 

extern uint32_t SPI_2_Routine_Ret_32(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len); 
extern uint8_t SPI_2_Routine_Write_ret_UART(uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);

extern uint8_t SPI_1_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_2_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);


/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/


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

/**************************** Configuration parameters **********************/

/* Temperature parameters */
#define ADXL355_TEMP_BIAS       (float)1852.0      /* Accelerometer temperature bias(in ADC codes) at 25 Deg C */
#define ADXL355_TEMP_SLOPE      (float)-9.05       /* Accelerometer temperature change from datasheet (LSB/degC) */

/* Accelerometer parameters */
#define ADXL_RANGE          2     /* ADXL362 sensitivity: 2, 4, 8 [g] */

#define ACT_VALUE          50     /* Activity threshold value */

#define INACT_VALUE        50     /* Inactivity threshold value */

#define ACT_TIMER          100    /* Activity timer value in ms */

#define INACT_TIMER        10     /* Inactivity timer value in seconds */

/****************************** Global Data ***********************************/

extern int32_t i32SensorX;
extern int32_t i32SensorY;
extern int32_t i32SensorZ;
extern uint16_t ui16SensorT;

//extern uint32_t ui32SensorX;
//extern uint32_t ui32SensorY;
//extern uint32_t ui32SensorZ;


extern uint32_t ui32timer_counter;

//float f32temp = 0.0f;
//float adxl355Scale = 0.0f;

/* Temperature parameters */
#define ADXL355_TEMP_BIAS       (float)1852.0      /* Accelerometer temperature bias(in ADC codes) at 25 Deg C */
#define ADXL355_TEMP_SLOPE      (float)-9.05       /* Accelerometer temperature change from datasheet (LSB/degC) */


struct {
    uint16_t Range_2G : 1;
    uint16_t Range_4G : 1;
    uint16_t Range_8G : 1;
    uint16_t Streaming : 1;
}Accel_Flag;


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
