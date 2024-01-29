/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 ******************************************************************************/
#include "MAG_MMC5983MA.h"

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_MAG_MMC5983MA(void)
{
    /*******************************************************************
    * MMC5983MA                                          
    *******************************************************************/
    //Write_1_reg_I2C(MMC5983MA_addr,0x0A,0x01); //  2ms 400Hz
    //Write_1_reg_I2C(MMC5983MA_addr,0x0A,0x02); //  4ms 200Hz
    
    //Write_1_reg_I2C(MMC5983MA_addr,0x0A,0x06); //  2ms 400Hz - disabled X

    
    //Write_1_reg_I2C(MMC5983MA_addr,0x0A,0x03); //  0.5ms 800Hz
    
    

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: Get the ID for the Magnetometer, it should return 0x30;
 ******************************************************************************/
uint8_t MAG_MMC5983MA_read_ID(void)
{
    uint8_t data_ID; 
    uint8_t cmd_buffer[1];
    cmd_buffer[0] = MMC5983MA_ID | MMC5983MA_Read_Bit;    // CMD
    data_ID = SPI_3_Routine(SPI_CS_MAG, cmd_buffer, 1, 1); 
    // Should return 0x30; 
    return data_ID; 

}


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void MAG_MMC5983MA_Get_data(void)
{
    /*******************************************************************
    * MMC5983MA     // address is 0x30 (shifted once == 0x60)                                     
    *******************************************************************/
    //Write_1_reg_I2C(MMC5983MA_addr,0x09,0x01); // initiate data acquisition
    

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void MAG_MMC5983MA_Write_data_SPI(uint8_t *buffer, uint8_t data_len)
{
    /*******************************************************************
    * MMC5983MA     // address is 0x30 (shifted once == 0x60)                                     
    *******************************************************************/
    //Write_1_reg_I2C(MMC5983MA_addr,0x09,0x01); // initiate data acquisition
    uint8_t data_read; 
    buffer[0] = buffer[0] | MMC5983MA_Write_Bit;    // CMD
    data_read = SPI_3_Routine(SPI_CS_MAG, buffer, data_len, 0);
    // data_read = SPI_1_Routine(SPI_CS_MAG, cmd_buffer, 1, 1); 
    return data_read; 

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t MAG_MMC5983MA_Get_data_SPI(uint8_t *buffer, uint8_t data_len)
{
    /*******************************************************************
    * MMC5983MA     // address is 0x30 (shifted once == 0x60)                                     
    *******************************************************************/
    //Write_1_reg_I2C(MMC5983MA_addr,0x09,0x01); // initiate data acquisition
    uint8_t cmd_buffer[1];
    uint8_t data_read; 
    cmd_buffer[0] = MMC5983MA_X_OUT_0 | MMC5983MA_Read_Bit;    // CMD
    data_read = SPI_3_Routine_Read(SPI_CS_MAG, cmd_buffer, 1, buffer, data_len);
    // data_read = SPI_1_Routine(SPI_CS_MAG, cmd_buffer, 1, 1); 
    return data_read; 

}
