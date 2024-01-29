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
#include "ADC_ADS863x.h"


/*******************************************************************************
 * Function: ADC_ADS868x_INIT
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t SET_ADC_ADS863x_POWER_UP(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[1];

   
   cmd_buffer[0] = (ADS863x_POWER_UP << 1) | 0x00;     // write
   //cmd_buffer[0] = 0x08; // write   
   cmd_buffer[1] = 0x00; //  
           
   status = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
  
   return status; 
}

/*******************************************************************************
 * Function: ADS863x_AUX_CONFIG
 * Parameters: chip_select, range
 * Return: status
 * Description: Set the voltage input max range on the ADC
 ******************************************************************************/
uint8_t Get_ADC_ADS863x_AUX_CONFIG(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[1];
   uint8_t data_buffer[1];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = (ADS863x_AUX_CONFIG << 1) | 0x01;     // READ   
   //cmd_buffer[0] = 0x13;     // READ   
   
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 1, data_buffer, 1); 
   
   CAN_Encode_Sending(0x1B,0xC4, data_buffer, 1); // debug only see CAN     
   
   data_read = data_buffer[1]; 
   return data_read; 
}

/*******************************************************************************
 * Function: SET_ADC_ADS863x_AUX_CONFIG
 * Parameters: chip_select, range
 * Return: status
 * Description: Set the voltage input max range on the ADC
 ******************************************************************************/
uint8_t SET_ADC_ADS863x_AUX_CONFIG(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[2];

   
   cmd_buffer[0] = (ADS863x_AUX_CONFIG << 1) | 0x00;     // write
   cmd_buffer[1] = 0x0C; // write   
           
   status = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
  
   return status; 
}

/*******************************************************************************
 * Function: SET_ADC_ADS863x_RANGE
 * Parameters: chip_select, range
 * Return: status
 * Description: Set the voltage input max range on the ADC
 ******************************************************************************/
uint8_t SET_ADC_ADS863x_RANGE(uint8_t chip_select, uint8_t range)
{
    
   uint8_t cmd_buffer[2];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = (ADS863x_CH0_RANGE_CMD << 1) | 0x00;     // write
   cmd_buffer[1] = 0x60; 
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
   
   cmd_buffer[0] = (ADS863x_CH1_RANGE_CMD << 1) | 0x00;     // write
   cmd_buffer[1] = 0x60; 
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
   
   cmd_buffer[0] = (ADS863x_CH2_RANGE_CMD << 1) | 0x00;     // write
   cmd_buffer[1] = 0x60; 
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
   
   cmd_buffer[0] = (ADS863x_CH3_RANGE_CMD << 1) | 0x00;     // write
   cmd_buffer[1] = 0x60; 
   data_read = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
   return data_read; 
}

/*******************************************************************************
 * Function: Get_ADC_ADS863x_RANGE
 * Parameters: chip_select
 * Return: range
 * Description: Read the voltage input max range on the ADC
 ******************************************************************************/
uint8_t Get_ADC_ADS863x_RANGE(uint8_t chip_select)
{
   uint8_t status;
   uint8_t cmd_buffer[1];
   uint8_t data_buffer[1];
   uint8_t data_read = 0; 
   
   cmd_buffer[0] = (ADS863x_CH0_RANGE_CMD << 1) | 0x01;     // READ   
   //cmd_buffer[0] = 0x11;     // READ   
   
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 1, data_buffer, 1); 
   
   CAN_Encode_Sending(0x1B,0xC4, data_buffer, 1); // debug only see CAN     
   
   data_read = data_buffer[1]; 
   return data_read; 
}

/*******************************************************************************
 * Function: SET_ADC_ADS863x_PAGE
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t SET_ADC_ADS863x_PAGE(uint8_t chip_select, uint8_t page)
{
   uint8_t status;
   uint8_t cmd_buffer[1];

   
   cmd_buffer[0] = (ADS863x_PAGE_SELECT_CMD << 1) | 0x00;     // write
   //cmd_buffer[0] = 0x08; // write   
   
   if(page == 0)
   {
       cmd_buffer[1] = 0x00; //
   }
   else
   {
       cmd_buffer[1] = 0x01; //
   } 
           
   status = SPI_1_Routine(chip_select, cmd_buffer, 2, 0); 
  
   return status; 
}

/*******************************************************************************
 * Function: ADC_ADS868x_READ_DATA
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint16_t ADC_ADS863x_READ_DATA(uint8_t chip_select, uint8_t channel)
{
   uint8_t status;
   uint8_t cmd_buffer[2];
   uint8_t data_buffer[2];
   uint16_t data_read = 0; 
   
    //cmd_buffer[0] = (ADS863x_READ_DATA_MANUAL << 1) | 0x01;     // READ
    cmd_buffer[0] = (ADS863x_READ_DATA_MANUAL << 1) | 0x00;     // write  

   switch(channel)
   {
       case 0:
           cmd_buffer[1] = 0x0C;    // CH0 - Range 0 to 5
           break;
           
        case 1:
           cmd_buffer[1] = 0x2C;    // CH1 - Range 0 to 5
           break;
           
        case 2:
           cmd_buffer[1] = 0x4C;    // CH2 - Range 0 to 5
           break;
           
        case 3:
           cmd_buffer[1] = 0x6C;    // CH3 - Range 0 to 5
           break;
           
       default:
           cmd_buffer[1] = 0x0C;    // CH0 - Range 0 to 5
           break;
   }
   
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 0); 


   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 0, data_buffer, 2); 
   
   
   status = SPI_1_Routine_Read(chip_select, cmd_buffer, 0, data_buffer, 2); 
   
   //status = SPI_1_Routine_Read(chip_select, cmd_buffer, 2, data_buffer, 2); 
   
   //CAN_Encode_Sending(0x1B,0xC4, data_buffer, 2); // debug only see CAN     
   
   data_read = data_buffer[0]; 
   data_read = (data_read  << 8) | data_buffer[1]; 
   return data_read; 
}