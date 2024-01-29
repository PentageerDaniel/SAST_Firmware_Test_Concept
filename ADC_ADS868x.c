/******************************************************************************/
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    ADC_ADS868x.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 ******************************************************************************/
#include "ADC_ADS868x.h"


/*******************************************************************************
 * Function: ADC_ADS868x_INIT
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/



/*******************************************************************************
 * Function: Get_ADC_ADS868x_Device_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t Get_ADC_ADS868x_Device_ID(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[2];
   uint8_t data_buffer[2];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = ADS868x_READ_CMD;        // READ 
   cmd_buffer[1] = 0x02;            
   //cmd_buffer[2] = 0x00;
   //cmd_buffer[3] = 0x00;

   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 1, data_buffer, 4);
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 2);
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 0, data_buffer, 4);
   

   //CAN_Encode_Sending(0x1B,0xC4, data_buffer, 2); // debug
                
   
   data_read = data_buffer[1]; 
   
   return data_read; 
}

/*******************************************************************************
 * Function: SET_ADC_ADS868x_Device_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t SET_ADC_ADS868x_Device_ID(uint8_t chip_select, uint8_t device_ID)
{
    
   uint8_t cmd_buffer[4];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = ADS868x_WRITE_1BYTE_LS_CMD;  // 
   cmd_buffer[1] = 0x02;   // 
   cmd_buffer[2] = 0x0F;        // 0x0x == x is address
   cmd_buffer[3] = 0x0F;                    // n/a
   //cmd_buffer[3] = 0x0F & device_ID;                    // n/a
//   cmd_buffer[2] = 0xFF;        // 0x0x == x is address
//   cmd_buffer[3] = 0xFF;  
   
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 4, 0); 
   

   return data_read; 
}

/*******************************************************************************
 * Function: SET_ADC_ADS868x_RANGE
 * Parameters: chip_select, range
 * Return: status
 * Description: Set the voltage input max range on the ADC
 ******************************************************************************/
uint8_t SET_ADC_ADS868x_RANGE(uint8_t chip_select, uint8_t range)
{
    
   uint8_t cmd_buffer[4];
   uint8_t data_read = 0; 
   
//    cmd_buffer[0] = 0xD4;
//    cmd_buffer[1] = 0x14;
//    cmd_buffer[2] = 0x00;
//    cmd_buffer[3] = 0x01;  
   
   
   
   //cmd_buffer[0] = ADS868x_WRITE_2BYTES_CMD;    // 0xD0
   cmd_buffer[0] = ADS868x_WRITE_1BYTE_LS_CMD; // 0xD4 
   //cmd_buffer[0] = ADS868x_SET_HWORD_CMD;    // 0xD8
   cmd_buffer[1] = ADS868x_RANGE_SEL_REG;       // 0x14
   cmd_buffer[2] = 0x00;                        // 0x00
   //cmd_buffer[3] = 0b0001011;                   // 0x0B - 1.25 x Vref
   cmd_buffer[3] = range & 0x0F;              // Set range & 0x0F
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 4, 0); 
   return data_read; 
}

/*******************************************************************************
 * Function: Get_ADC_ADS868x_Device_ID
 * Parameters: chip_select
 * Return: range
 * Description: Read the voltage input max range on the ADC
 ******************************************************************************/
uint16_t Get_ADC_ADS868x_RANGE(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[2];
   uint8_t data_buffer[2];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = ADS868x_READ_HWORD_CMD;     // 0xC8
   cmd_buffer[1] = ADS868x_RANGE_SEL_REG;      // 0x14 
   cmd_buffer[2] = 0x00;
   cmd_buffer[3] = 0x00;   
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 0); 
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 0, data_buffer, 2); 
   
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 2);
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 4, data_buffer, 4);
   
   //CAN_Encode_Sending(0x1B,0xC4, data_buffer, 2); // debug only see CAN     
   
   data_read = (data_buffer[1] << 8) | data_buffer[0];  
   return data_read; 
}

/*******************************************************************************
 * Function: SET_ADC_ADS868x_Device_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t SET_ALARM_H_TH_REG(uint8_t chip_select, uint8_t INP_ALRM_HYST, uint16_t INP_ALRM_HIGH_TH)
{
    
   uint8_t cmd_buffer[4];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = ADS868x_WRITE_2BYTES_CMD;  // D2
   cmd_buffer[1] = ADS868x_ALARM_H_TH_REG;       // 
   cmd_buffer[2] = 0xA5;                        // 
   cmd_buffer[3] = 0x5A;                        // 0x03
   
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 4, 0); 
   return data_read; 
}

/*******************************************************************************
 * Function: Get_ADC_ADS868x_Device_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t GET_ALARM_H_TH_REG(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[2];
   uint8_t data_buffer[2];
   uint8_t data_read = 0; 
   
   //cmd_buffer[0] = ADS868x_READ_CMD; 
   cmd_buffer[0] = ADS868x_READ_HWORD_CMD;     // READ 
   cmd_buffer[1] = ADS868x_ALARM_H_TH_REG;     
   //cmd_buffer[1] = 0x26;    
   //cmd_buffer[2] = 0x00;
   //cmd_buffer[3] = 0x00;

   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 1, data_buffer, 4);
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 2);
   
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 0, data_buffer, 2);
   

   CAN_Encode_Sending(0x1B,0xC4, data_buffer, 2); // debug
                
   
   data_read = data_buffer[1]; 
   
   return data_read; 
}

/*******************************************************************************
 * Function: Get_ADC_ADS868x_Device_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint16_t ADC_ADS868x_READ_DATA(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[2];
   uint8_t data_buffer[2];
   uint8_t data_read = 0; 
   
   //cmd_buffer[0] = ADS868x_READ_HWORD_CMD;     // READ   
   //cmd_buffer[1] = ADS868x_DATAOUT_CTL_REG; 
//   set_SS_Accel(chip_select);
//   asm volatile ("nop");
//   asm volatile ("nop");
//   asm volatile ("nop");
//   asm volatile ("nop");
//   disable_SS_Accel(chip_select);
//          
//   asm volatile ("nop");
//   asm volatile ("nop");
//   asm volatile ("nop");
//   asm volatile ("nop");
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 0); 

   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 0, data_buffer, 4); 
   
   //CAN_Encode_Sending(0x1B,0xC4, data_buffer, 4); // debug only see CAN     
   
   data_read = data_buffer[0]; 
   data_read = (data_read  << 8) | data_buffer[1];  
   return data_read; 
}

/*******************************************************************************
 * Function: Get_ADC_ADS868x_Device_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t SET_ADC_ADS868x_DATAOUT_CTL(uint8_t chip_select)
{
    
   uint8_t cmd_buffer[4];
   uint8_t data_read = 0; 
   
//    cmd_buffer[0] = 0xD4;
//    cmd_buffer[1] = 0x14;
//    cmd_buffer[2] = 0x00;
//    cmd_buffer[3] = 0x01;  
   
   
   
//   cmd_buffer[0] = ADS868x_WRITE_2BYTES_CMD;    // 0xD0
//   //cmd_buffer[0] = ADS868x_WRITE_1BYTE_LS_CMD  // 0xD4 
    cmd_buffer[0] = ADS868x_SET_HWORD_CMD;      // 0xD8
    cmd_buffer[1] = ADS868x_DATAOUT_CTL_REG;    // 0x10
    cmd_buffer[2] = 0x41;                        // Device address, Range
    cmd_buffer[3] = 0x00;                   // 
//   cmd_buffer[3] = range & 0x0F;              // Set range & 0x0F
    data_read = SPI_1_Routine(chip_select, cmd_buffer, 4, 0); 
    return data_read; 
}