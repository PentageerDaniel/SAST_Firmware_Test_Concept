/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    ADXL355.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 ******************************************************************************/
#include "Accel_ADXL355.h"


/*******************************************************************************
   @brief Initialization the accelerometer sensor

   @return none

*******************************************************************************/
void ADXL355_SPI_Init(void)
{
    //uint8_t cmd_buffer[2];
    // ADXL_RANGE == 8
    //SPI_Write(RANGE, 0x81, 0x00, SPI_WRITE_ONE_REG);          /* Set sensor range within RANGE register */
    
    //adxl355Scale = 256000.0f;


    // ADXL_RANGE == 4
    //SPI_Write(RANGE, 0x82, 0x00, SPI_WRITE_ONE_REG);          /* Set sensor range within RANGE register */
    //adxl355Scale = 128000.0f;


    // ADXL_RANGE == 8
    //SPI_Write(RANGE, 0x83, 0x00, SPI_WRITE_ONE_REG);          /* Set sensor range within RANGE register */
    //adxl355Scale = 64000.0f;
    
//    uint8_t tempo; 
//    /* Start accelerometer measurement mode */
//   //ADXL355_Start_Sensor();
//   
//   cmd_buffer[0] = (ACC355_DEVID_AD << 1) | 0x01;     // CMD
//   tempo = SPI_2_Routine(cmd_buffer, 1, 1); 
//   //write_uart_1(tempo);
//   
//   cmd_buffer[0] = (ACC355_DEVID_MST << 1) | 0x01;      // CMD
//   tempo = SPI_2_Routine(cmd_buffer, 1, 1); 
//   //write_uart_1(tempo);
//   
//   cmd_buffer[0] = (ACC355_PARTID << 1) | 0x01; 
//   tempo = SPI_2_Routine(cmd_buffer, 1, 1); 
//   //write_uart_1(tempo);
//   
//   cmd_buffer[0] = (ACC355_REVID << 1) | 0x01; 
//   tempo = SPI_2_Routine(cmd_buffer, 1, 1); 
   //write_uart_1(tempo);
    
//   DioPulPin(CSACC_PORT, CSACC_PIN_NUMBER, 0);          /* Disable the internal pull up on CSACC pin */
//   DioOenPin(CSACC_PORT, CSACC_PIN_NUMBER, 1);          /* Set CSACC pin as output */
//
//   DioPulPin(INT1ACC_PORT, INT1ACC_PIN_NUMBER, 0);         /* Disable the internal pull up on INT1ACC pin */
//   DioOenPin(INT1ACC_PORT, INT1ACC_PIN_NUMBER, 0);         /* Set INT1ACC pin as input */
//
//   DioPulPin(INT2ACC_PORT, INT2ACC_PIN_NUMBER, 0);         /* Disable the internal pull up on INT2ACC pin */
//   DioOenPin(INT2ACC_PORT, INT2ACC_PIN_NUMBER, 0);         /* Set INT2ACC pin as input */
//
//   DioPulPin(DATARDYACC_PORT, DATARDYACC_PIN_NUMBER, 0);         /* Disable the internal pull up on INT2ACC pin */
//   DioOenPin(DATARDYACC_PORT, DATARDYACC_PIN_NUMBER, 0);         /* Set INT2ACC pin as input */

   /* Quick verification test for boards */
//   uint32_t volatile ui32test = SPI_Read(DEVID_AD, SPI_READ_ONE_REG);                  /* Read the ID register */
//   uint32_t volatile ui32test2 = SPI_Read(DEVID_MST, SPI_READ_ONE_REG);                  /* Read the ID register */
//   uint32_t volatile ui32test3 = SPI_Read(PARTID, SPI_READ_ONE_REG);                  /* Read the ID register */
//   uint32_t volatile ui32test4 = SPI_Read(REVID, SPI_READ_ONE_REG);                 /* Read the ID register */

}


/*******************************************************************************
 * Function: Get accel Dedvice ID
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t Get_Accel_Device_ID(uint8_t chip_select)
{
//   uint8_t cmd_buffer[1];
//   uint8_t data_read; 
//   cmd_buffer[0] = (ACC355_DEVID_AD << 1) | 0x01;     // CMD
//   data_read = SPI_2_Routine(cmd_buffer, 1, 1); 
//   return data_read; 
   uint8_t cmd_buffer[1];
   uint8_t data_read; 
   cmd_buffer[0] = (ACC355_DEVID_AD << 1) | 0x01;     // CMD
   //cmd_buffer[0] = (ACC355_DEVID_MST << 1) | 0x01;     // CMD
   //cmd_buffer[0] = (ACC355_PARTID << 1) | 0x01;     // CMD
   //cmd_buffer[0] = (ACC355_REVID << 1) | 0x01;     // CMD
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 1, 1); 
   return data_read; 
}

/*******************************************************************************
 * Function: Read_Accel_Device_Register
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t ADXL355_SPI_Read_Accel_Device_Register(uint8_t register_to_read)
{
   uint8_t cmd_buffer[1];
   uint8_t data_read; 
   //cmd_buffer[0] = (ACC355_DEVID_AD << 1) | 0x01;     // CMD
   //cmd_buffer[0] = (ACC355_DEVID_MST << 1) | 0x01;     // CMD
   cmd_buffer[0] = (register_to_read << 1) | 0x01;     // CMD
   //cmd_buffer[0] = (ACC355_REVID << 1) | 0x01;     // CMD
   data_read = SPI_2_Routine(SPI_CS_ACC_LG1, cmd_buffer, 1, 1); 
   return data_read; 
}


/*******************************************************************************
 * Function: Write accel Dedvice ID
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
void ADXL355_SPI_Write_Accel_Device_Register(uint8_t register_address, uint8_t register_value)
{
   uint8_t cmd_buffer[3];
   
   cmd_buffer[0] = (register_address << 1) | 0x00;     // CMD
   cmd_buffer[1] = register_value;     // CMD
   cmd_buffer[2] = 0x00;                // dummy
   SPI_2_Routine(SPI_CS_ACC_LG1, cmd_buffer, 3, 0); 

}


/*******************************************************************************
   @brief Turns on accelerometer measurement mode.

   @return none

*******************************************************************************/
void ADXL355_SPI_Start_Sensor(uint8_t chip_select)
{
   uint8_t ui8temp;
   uint8_t cmd_buffer[2];
   uint8_t buffer[1] = {0};
   uint8_t data_read;
   //ui8temp = (uint8_t)SPI_Read(POWER_CTL, SPI_READ_ONE_REG);       /* Read POWER_CTL register, before modifying it */
   //uint8_t * read_byte = read_bytes_SPI_2(POWER_CTL, 1, 1);
   
   cmd_buffer[0] = (ACC355_POWER_CONTROL << 1) | 0x01;
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 1, 1); 
   //status = SPI_2_Routine_Read_(SPI_CS_ACC_HG,  cmd,      cmd_len, buffer, data_len);
   ui8temp = buffer[0] & 0xFE;                                          /* Set measurement bit in POWER_CTL register */

   //SPI_Write(POWER_CTL, ui8temp, 0x00, SPI_WRITE_ONE_REG);                    /* Write the new value to POWER_CTL register */
  
   cmd_buffer[0] = (ACC355_POWER_CONTROL << 1) | 0x00;     // CMD 
   cmd_buffer[1] = buffer[0]; 
   cmd_buffer[2] = 0x00; 
   
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 3, 0); 
   
   
}


/*******************************************************************************
   @brief Puts the accelerometer into standby mode.

   @return none

*******************************************************************************/
void ADXL355_SPI_Stop_Sensor(uint8_t chip_select)
{
   //uint8_t ui8temp;

//   ui8temp = (uint8_t)SPI_Read(POWER_CTL, SPI_READ_ONE_REG);        /*Read POWER_CTL register, before modifying it */
//
//   ui8temp = ui8temp | 0x01;                                      /* Clear measurement bit in POWER_CTL register */
//
//   SPI_Write(POWER_CTL, ui8temp, 0x00, SPI_WRITE_ONE_REG);                 /* Write the new value to POWER_CTL register */

    uint8_t ui8temp;
    uint8_t cmd_buffer[2];
    uint8_t read_byte;

    //ui8temp = (uint8_t)SPI_Read(POWER_CTL, SPI_READ_ONE_REG);       /* Read POWER_CTL register, before modifying it */
    cmd_buffer[0] = (ACC355_POWER_CONTROL << 1) | 0x01;
    read_byte = SPI_1_Routine(chip_select, cmd_buffer, 1, 1); 
    
    ui8temp = read_byte & 0x01;                                          /* Set measurement bit in POWER_CTL register */

    //SPI_Write(POWER_CTL, ui8temp, 0x00, SPI_WRITE_ONE_REG);                    /* Write the new value to POWER_CTL register */
    
    cmd_buffer[0] = (ACC355_POWER_CONTROL << 1) | 0x00;     // CMD 
    cmd_buffer[1] = ui8temp; 
    cmd_buffer[2] = 0x00; 
    SPI_1_Routine(chip_select, cmd_buffer, 3, 0); 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 0x6B
 * Description: 
 ******************************************************************************/
uint8_t ADXL355_SPI_Get_Data(uint8_t chip_select, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len)
{
    uint8_t status; 
    status = SPI_1_Routine_Read(chip_select, cmd, cmd_len, buffer, data_len);
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 11); // debug
    return status; 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL355_Multiple_Reading(void)
{
    uint8_t cmd_buffer[1];
    cmd_buffer[0] = (ACC355_DEVID_AD << 1) | 0x01;
    //SPI_2_Routine_Write_ret_UART(cmd_buffer, 1, 4); 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL355_Read_Fifo(uint8_t fifo_count)
{
    uint8_t cmd_buffer[1];
    cmd_buffer[0] = (ACC355_FIFO_DATA << 1) | 0x01;
    //SPI_2_Routine_Write_ret_UART(cmd_buffer, 1, fifo_count); 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t ADXL355_Get_Streaming(void)
{
    return (Accel_Flag.Streaming);
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL355_Set_Streaming(uint8_t status)
{
    if(status == 1)
    {
        Accel_Flag.Streaming = true; 
    }
    else
    {
        Accel_Flag.Streaming = false;
    }
}
/*******************************************************************************
   @brief Reads the accelerometer data.

   @return none

*******************************************************************************/
void ADXL355_Data_Scan(void)
{
    uint8_t cmd_buffer[2];
//    uint8_t buffer[4];
//    
//    ////////////////////////////////////////////////////////
//    uint32_t read_byte_X = 0;
//    uint32_t read_byte_Y = 0;
//    uint32_t read_byte_Z = 0;
//    
//    uint32_t Temp_raw;
    
    // return all TEMP - X - Y - Z
    cmd_buffer[0] = (ACC355_TEMP2 << 1) | 0x01;
    //SPI_2_Routine_Write_ret_UART(cmd_buffer, 1, 11); 
    

}


/*******************************************************************************
   @brief Convert the two's complement data in X,Y,Z registers to signed integers

   @param ui32SensorData - raw data from register

   @return int32_t - signed integer data

*******************************************************************************/
int32_t ADXL355_Acceleration_Data_Conversion (uint32_t ui32SensorData)
{
   int32_t i32Conversion = 0;

   ui32SensorData = (ui32SensorData  >> 4);
   ui32SensorData = (ui32SensorData & 0x000FFFFF);

   if((ui32SensorData & 0x00080000)  == 0x00080000){

         i32Conversion = (ui32SensorData | 0xFFF00000);

   }
   else{
         i32Conversion = ui32SensorData;
   }

   return i32Conversion;
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL355_Get_Data(uint8_t index)
{
//    uint8_t cmd_buffer[2];
//    uint32_t tempo;
//    uint8_t pointer=0; 
//    uint32_t ui32SensorX;
//    uint32_t ui32SensorY;
//    uint32_t ui32SensorZ;
//    
//    Chip_Select = index;
//    
//    
//    // return all TEMP - X - Y - Z
//    cmd_buffer[0] = (TEMP2 << 1) | 0x01;
//    //SPI_2_Routine_Write_ret_UART(cmd_buffer, 1, 11); 
//    
//    uint8_t *data_read = read_bytes_SPI_2(cmd_buffer, 1, 11);
//    
//    tempo = data_read[pointer++]; 
//    ui16SensorT = (tempo << 8) | data_read[pointer++];
//    
//    
//    tempo = data_read[pointer++];
//    ui32SensorX = tempo << 16; 
//    tempo = data_read[pointer++];
//    ui32SensorX |= (tempo << 8) | data_read[pointer++];
//    
//    tempo = data_read[pointer++];
//    ui32SensorY = tempo << 16; 
//    tempo = data_read[pointer++];
//    ui32SensorY |= (tempo << 8) | data_read[pointer++];
//    
//    tempo = data_read[pointer++];
//    ui32SensorZ = tempo << 16; 
//    tempo = data_read[pointer++];
//    ui32SensorZ |= (tempo << 8) | data_read[pointer++];
//
//    i32SensorX = ADXL355_Acceleration_Data_Conversion(ui32SensorX);
//    i32SensorY = ADXL355_Acceleration_Data_Conversion(ui32SensorY);
//    i32SensorZ = ADXL355_Acceleration_Data_Conversion(ui32SensorZ);
//    
//    free(data_read);
    

}
////////////////////////////////////////////////////////////////////////////////
