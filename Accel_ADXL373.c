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
#include "Accel_ADXL373.h"
//#include "variable.h"
//#include "variable.h"


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Init(void)
{
	uint8_t cmd_buffer[16];
	
    
    
    // enable Peak dedect and fifo
    /*
    1. Configure the FIFO_CTL register for peak detect mode (b0011101x to 
        Register 0x3A).
    2. Set the desired activity threshold and time settings (Register
        0x23 to Register 0x29).
    3. Set the desired inactivity threshold and time settings (Register
        0x2A to Register 0x31).
    4. Set the activity mode to linked or loop mode (Register 0x3E).
     */
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // set Fifo 
//    cmd_buffer[0] = (ACC373_FIFO_SAMPLES << 1) | 0x00; 
//    cmd_buffer[1] = 0x0F; // FIFO_SAMPLES program the number of samples to be 
//    // saved after the trigger is detected
//    cmd_buffer[2] = 0x3D; // FIFO stores peak acceleration (x, y, and z), 
//    // FIFO operates in trigger mode
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0);
    
    // disable fifo
    cmd_buffer[0] = (ACC373_FIFO_SAMPLES << 1) | 0x00; 
    cmd_buffer[1] = FIFO_SIZE_3X; // FIFO_SAMPLES program the number of samples to be 
    // saved after the trigger is detected
    cmd_buffer[2] = 0x38; // FIFO stores  (x, y, and z), // FIFO bypass
    
    //cmd_buffer[2] = 0x3A; // FIFO stores (x, y, and z), // FIFO Stream
    //cmd_buffer[2] = 0x3B; // FIFO stores (x, y, and z), // FIFO Stream/ 256+ sample bit
    SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0);
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
//    // Activity threshold is 60g => 300 (60/0.2mg/LSB) ==> 9600 or 0x2580 
//    // (shift by 5) since it is left justified. Add 1 to enable channel 2581 
//    // TIME (@ODR 2560) = TIME_ACT × 8.25 ms per code ==> 
//    // TIME_ACT = Time / 8.25ms == 40ms / 8.25 ~= 5
//    // Inactivity threshold is 30g => 150 (30/0.2mg/LSB) ==> 4800 or 0x12C0 
//    // (shift by 5) since it is left justified. Add 1 to enable channel 12C1 
//    // Inactivity ==> Time = TIME_INACT × 32.5 ms per code
//    // TIME_INACT = Time / 32.5ms == 250ms / 32.5 ~= 7
//    cmd_buffer[0] = (ACC373_THRESH_ACT_X_H << 1) | 0x00; // 
//    cmd_buffer[1] = 0x25; // ACC373_THRESH_ACT_X_H
//    cmd_buffer[2] = 0x81; // ACC373_THRESH_ACT_X_L
//    cmd_buffer[3] = 0x25; // ACC373_THRESH_ACT_Y_H
//    cmd_buffer[4] = 0x81; // ACC373_THRESH_ACT_Y_L
//    cmd_buffer[5] = 0x25; // ACC373_THRESH_ACT_Z_H
//    cmd_buffer[6] = 0x81; // ACC373_THRESH_ACT_Z_L
//    //cmd_buffer[7] = 0x05; // ACC373_TIME_ACT >> 40ms
//    cmd_buffer[7] = 0x01; // ACC373_TIME_ACT >> 8.25ms
//    cmd_buffer[8] = 0x12; // ACC373_THRESH_INACT_X_H
//    cmd_buffer[9] = 0xC1; // ACC373_THRESH_INACT_X_L
//    cmd_buffer[10] = 0x12; // ACC373_THRESH_INACT_Y_H
//    cmd_buffer[11] = 0xC1; // ACC373_THRESH_INACT_Y_L
//    cmd_buffer[12] = 0x12; // ACC373_THRESH_INACT_Z_H
//    cmd_buffer[13] = 0xC1; // ACC373_THRESH_INACT_Z_L
//    cmd_buffer[14] = 0x00; // ACC373_TIME_INACT_H
//    cmd_buffer[15] = 0x07; // ACC373_TIME_INACT_L
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 16, 0); 
    
    
    // Activity threshold is 5g => 25 (5/0.2mg/LSB) ==> 25 or 0x0019 
    // (shift by 5) since it is left justified. Add 1 to enable channel 001A 
    // TIME (@ODR 2560) = TIME_ACT × 8.25 ms per code ==> 0x341
    // TIME_ACT = Time / 8.25ms == 40ms / 8.25 ~= 5
    // Inactivity threshold is 4g => 20 (3/0.2mg/LSB) ==> 15 or 0x000A 
    // (shift by 5) since it is left justified. Add 1 to enable channel 0x281
    // Inactivity ==> Time = TIME_INACT × 32.5 ms per code
    // TIME_INACT = Time / 32.5ms == 250ms / 32.5 ~= 7
//    cmd_buffer[0] = (ACC373_THRESH_ACT_X_H << 1) | 0x00; // 
//    cmd_buffer[1] = 0x03; // ACC373_THRESH_ACT_X_H
//    cmd_buffer[2] = 0x41; // ACC373_THRESH_ACT_X_L
//    cmd_buffer[3] = 0x03; // ACC373_THRESH_ACT_Y_H
//    cmd_buffer[4] = 0x41; // ACC373_THRESH_ACT_Y_L
//    cmd_buffer[5] = 0x03; // ACC373_THRESH_ACT_Z_H
//    cmd_buffer[6] = 0x41; // ACC373_THRESH_ACT_Z_L
//    //////////////////////////////////////////////////
//    //cmd_buffer[7] = 0x05; // ACC373_TIME_ACT >> 40ms
//    cmd_buffer[7] = 0x01; // ACC373_TIME_ACT >> 8.25ms
//    ////////////////////////////////////////////////////
//    cmd_buffer[8] = 0x02; // ACC373_THRESH_INACT_X_H
//    cmd_buffer[9] = 0x81; // ACC373_THRESH_INACT_X_L
//    cmd_buffer[10] = 0x02; // ACC373_THRESH_INACT_Y_H
//    cmd_buffer[11] = 0x81; // ACC373_THRESH_INACT_Y_L
//    cmd_buffer[12] = 0x02; // ACC373_THRESH_INACT_Z_H
//    cmd_buffer[13] = 0x81; // ACC373_THRESH_INACT_Z_L
//    ////////////////////////////////////////////////////
//    cmd_buffer[14] = 0x00; // ACC373_TIME_INACT_H
//    cmd_buffer[15] = 0x07; // ACC373_TIME_INACT_L
//    ////////////////////////////////////////////////////
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 16, 0); 
    
    ////////////////////////////////////////////////////////////////////////////
    // set bandwidth and mode
	cmd_buffer[0] = (ACC373_TIMING << 1) | 0x00;     // write CMD 
    //cmd_buffer[1] = 0x80; // Set ODR to 5120
    //cmd_buffer[1] = 0x60; // Set ODR to 2560
    cmd_buffer[1] = 0x20; // Set ODR to 1280
    //cmd_buffer[2] = 0x03; // defailt mode, Set 1280 Hz BW 
	//cmd_buffer[2] = 0x23; // Loop mode, Set 1280 Hz BW 
    //cmd_buffer[2] = 0x13; // linked, Set 1280 Hz BW ==> BW = 1/2 ODR
    cmd_buffer[2] = 0x02; // default, Set 640 Hz BW ==> BW = 1/2 ODR
    //cmd_buffer[2] = 0x03; // default, Set 1280 Hz BW ==> BW = 1/2 ODR
    //cmd_buffer[2] = 0x04; // default, Set 2560 Hz BW ==> BW = 1/2 ODR
	SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0); 

    ////////////////////////////////////////////////////////////////////////////
//    // set interrupt 
//    cmd_buffer[0] = (ACC373_INT1_MAP << 1) | 0x00; 
//    //cmd_buffer[1] = 0x80; // disable
//    //cmd_buffer[1] = 0x20; // ACT_INT1 active high
//    //cmd_buffer[1] = 0xA0; // ACT_INT1
//    cmd_buffer[1] = 0xB0; // ACT_INT1 and INACT_INT1
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 2, 0);
    
    ////////////////////////////////////////////////////////////////////////////
    
    if(ADXL373_SPI_ID(SPI_CS_ACC_HG) == 0xAD)
    {
        ADXL373_SPI_Start_Sensor(); 
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB1; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
        
    }
    else
    {
        // error
        cmd_buffer[0] = 0xEE;
        cmd_buffer[1] = 0xEE;       
        cmd_buffer[2] = 0xE1; 
        CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); // debug
    }
    
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Init_Wake_Up_Mode(void)
{
    uint8_t cmd_buffer[16];
      ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // set Fifo 
//    cmd_buffer[0] = (ACC373_FIFO_SAMPLES << 1) | 0x00; 
//    cmd_buffer[1] = 0x0F; // FIFO_SAMPLES program the number of samples to be 
//    // saved after the trigger is detected
//    cmd_buffer[2] = 0x3D; // FIFO stores peak acceleration (x, y, and z), 
//    // FIFO operates in trigger mode
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0);
    
    // disable fifo
    cmd_buffer[0] = (ACC373_FIFO_SAMPLES << 1) | 0x00; 
    cmd_buffer[1] = FIFO_SIZE_3X; // FIFO_SAMPLES program the number of samples to be 
    // saved after the trigger is detected
    cmd_buffer[2] = 0x38; // FIFO stores  (x, y, and z), // FIFO bypass
    
    //cmd_buffer[2] = 0x3A; // FIFO stores (x, y, and z), // FIFO Stream
    //cmd_buffer[2] = 0x3B; // FIFO stores (x, y, and z), // FIFO Stream/ 256+ sample bit
    SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0);
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
//    // Activity threshold is 60g => 300 (60/0.2mg/LSB) ==> 9600 or 0x2580 
//    // (shift by 5) since it is left justified. Add 1 to enable channel 2581 
//    // TIME (@ODR 2560) = TIME_ACT × 8.25 ms per code ==> 
//    // TIME_ACT = Time / 8.25ms == 40ms / 8.25 ~= 5
//    // Inactivity threshold is 30g => 150 (30/0.2mg/LSB) ==> 4800 or 0x12C0 
//    // (shift by 5) since it is left justified. Add 1 to enable channel 12C1 
//    // Inactivity ==> Time = TIME_INACT × 32.5 ms per code
//    // TIME_INACT = Time / 32.5ms == 250ms / 32.5 ~= 7
//    cmd_buffer[0] = (ACC373_THRESH_ACT_X_H << 1) | 0x00; // 
//    cmd_buffer[1] = 0x25; // ACC373_THRESH_ACT_X_H
//    cmd_buffer[2] = 0x81; // ACC373_THRESH_ACT_X_L
//    cmd_buffer[3] = 0x25; // ACC373_THRESH_ACT_Y_H
//    cmd_buffer[4] = 0x81; // ACC373_THRESH_ACT_Y_L
//    cmd_buffer[5] = 0x25; // ACC373_THRESH_ACT_Z_H
//    cmd_buffer[6] = 0x81; // ACC373_THRESH_ACT_Z_L
//    //cmd_buffer[7] = 0x05; // ACC373_TIME_ACT >> 40ms
//    cmd_buffer[7] = 0x01; // ACC373_TIME_ACT >> 8.25ms
//    cmd_buffer[8] = 0x12; // ACC373_THRESH_INACT_X_H
//    cmd_buffer[9] = 0xC1; // ACC373_THRESH_INACT_X_L
//    cmd_buffer[10] = 0x12; // ACC373_THRESH_INACT_Y_H
//    cmd_buffer[11] = 0xC1; // ACC373_THRESH_INACT_Y_L
//    cmd_buffer[12] = 0x12; // ACC373_THRESH_INACT_Z_H
//    cmd_buffer[13] = 0xC1; // ACC373_THRESH_INACT_Z_L
//    cmd_buffer[14] = 0x00; // ACC373_TIME_INACT_H
//    cmd_buffer[15] = 0x07; // ACC373_TIME_INACT_L
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 16, 0); 
    
    
    // Activity threshold is 5g => 25 (5/0.2mg/LSB) ==> 25 or 0x0019 
    // (shift by 5) since it is left justified. Add 1 to enable channel 001A 
    // TIME (@ODR 2560) = TIME_ACT × 8.25 ms per code ==> 0x341
    // TIME_ACT = Time / 8.25ms == 40ms / 8.25 ~= 5
    // Inactivity threshold is 4g => 20 (3/0.2mg/LSB) ==> 15 or 0x000A 
    // (shift by 5) since it is left justified. Add 1 to enable channel 0x281
    // Inactivity ==> Time = TIME_INACT × 32.5 ms per code
    // TIME_INACT = Time / 32.5ms == 250ms / 32.5 ~= 7
    cmd_buffer[0] = (ACC373_THRESH_ACT_X_H << 1) | 0x00; // 
    cmd_buffer[1] = 0x03; // ACC373_THRESH_ACT_X_H
    cmd_buffer[2] = 0x41; // ACC373_THRESH_ACT_X_L
    cmd_buffer[3] = 0x03; // ACC373_THRESH_ACT_Y_H
    cmd_buffer[4] = 0x41; // ACC373_THRESH_ACT_Y_L
    cmd_buffer[5] = 0x03; // ACC373_THRESH_ACT_Z_H
    cmd_buffer[6] = 0x41; // ACC373_THRESH_ACT_Z_L
    //////////////////////////////////////////////////
    //cmd_buffer[7] = 0x05; // ACC373_TIME_ACT >> 40ms
    cmd_buffer[7] = 0x01; // ACC373_TIME_ACT >> 8.25ms
    ////////////////////////////////////////////////////
    cmd_buffer[8] = 0x02; // ACC373_THRESH_INACT_X_H
    cmd_buffer[9] = 0x81; // ACC373_THRESH_INACT_X_L
    cmd_buffer[10] = 0x02; // ACC373_THRESH_INACT_Y_H
    cmd_buffer[11] = 0x81; // ACC373_THRESH_INACT_Y_L
    cmd_buffer[12] = 0x02; // ACC373_THRESH_INACT_Z_H
    cmd_buffer[13] = 0x81; // ACC373_THRESH_INACT_Z_L
    ////////////////////////////////////////////////////
    cmd_buffer[14] = 0x00; // ACC373_TIME_INACT_H
    cmd_buffer[15] = 0x07; // ACC373_TIME_INACT_L
    ////////////////////////////////////////////////////
    SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 16, 0); 
//    
//    ////////////////////////////////////////////////////////////////////////////
    // set bandwidth and mode
	cmd_buffer[0] = (ACC373_TIMING << 1) | 0x00;     // write CMD 
    //cmd_buffer[1] = 0x80; // Set ODR to 5120
    //cmd_buffer[1] = 0x60; // Set ODR to 2560
    cmd_buffer[1] = 0x20; // Set ODR to 1280
    //cmd_buffer[2] = 0x03; // defailt mode, Set 1280 Hz BW 
	//cmd_buffer[2] = 0x23; // Loop mode, Set 1280 Hz BW 
    //cmd_buffer[2] = 0x62; // Loop mode, Set 640 Hz BW + autosleep 
    //cmd_buffer[2] = 0x13; // linked, Set 1280 Hz BW ==> BW = 1/2 ODR
    cmd_buffer[2] = 0x52; // Auto sleep linked, Set 640 Hz BW ==> BW = 1/2 ODR
    //cmd_buffer[2] = 0x02; // default mode, Set 640 Hz BW ==> BW = 1/2 ODR
    //cmd_buffer[2] = 0x03; // default, Set 1280 Hz BW ==> BW = 1/2 ODR
    //cmd_buffer[2] = 0x04; // default, Set 2560 Hz BW ==> BW = 1/2 ODR
	SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0); 

    ////////////////////////////////////////////////////////////////////////////
    // set interrupt 
    cmd_buffer[0] = (ACC373_INT1_MAP << 1) | 0x00; 
    //cmd_buffer[1] = 0x80; // 
    //cmd_buffer[1] = 0x20; // ACT_INT1 active high
    //cmd_buffer[1] = 0xA0; // ACT_INT1
    //cmd_buffer[1] = 0xB0; // ACT_INT1 and INACT_INT1
    cmd_buffer[1] = 0xF0; // Awake and ACT_INT1 and INACT_INT1
    SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 2, 0);
    
    
    
    ////////////////////////////////////////////////////////////////////////////
    
    if(ADXL373_SPI_ID(SPI_CS_ACC_HG) == 0xAD)
    {
        // set wake up mode
        cmd_buffer[0] = (ACC373_POWER_CTL << 1) | 0x00;     // write CMD 
        //cmd_buffer[0] = ACC373_POWER_CTL;     // write CMD 
        //cmd_buffer[1] = 0x01; // wake up mode
        cmd_buffer[1] = 0x02; // instant mode
        //cmd_buffer[1] = 0x11; // filter settle wake up mode
        SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 2, 0); 
        //ADXL373_SPI_Start_Sensor(); 
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB1; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
        
    }
    else
    {
        // error
        cmd_buffer[0] = 0xEE;
        cmd_buffer[1] = 0xEE;       
        cmd_buffer[2] = 0xE1; 
        CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); // debug
    }
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Init_Instant_On_Impact(void)
{
    uint8_t cmd_buffer[16];
     // enable Peak dedect and no fifo
    /*
    1. Configure the FIFO_CTL register for peak detect mode (b0011101x to 
        Register 0x3A).
    2. Set the desired activity threshold and time settings (Register
        0x23 to Register 0x29).
    3. Set the desired inactivity threshold and time settings (Register
        0x2A to Register 0x31).
    4. Set the activity mode to linked or loop mode (Register 0x3E).
     */
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // set Fifo 
//    cmd_buffer[0] = (ACC373_FIFO_SAMPLES << 1) | 0x00; 
//    cmd_buffer[1] = 0x0F; // FIFO_SAMPLES program the number of samples to be 
//    // saved after the trigger is detected
//    cmd_buffer[2] = 0x3D; // FIFO stores peak acceleration (x, y, and z), 
//    // FIFO operates in trigger mode
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0);
    
    // disable fifo
    cmd_buffer[0] = (ACC373_FIFO_SAMPLES << 1) | 0x00; 
    cmd_buffer[1] = FIFO_SIZE_3X; // FIFO_SAMPLES program the number of samples to be 
    // saved after the trigger is detected
    cmd_buffer[2] = 0x38; // FIFO stores  (x, y, and z), // FIFO bypass
    
    //cmd_buffer[2] = 0x3A; // FIFO stores (x, y, and z), // FIFO Stream
    //cmd_buffer[2] = 0x3B; // FIFO stores (x, y, and z), // FIFO Stream/ 256+ sample bit
    SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0);
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
//    // Activity threshold is 60g => 300 (60/0.2mg/LSB) ==> 9600 or 0x2580 
//    // (shift by 5) since it is left justified. Add 1 to enable channel 2581 
//    // TIME (@ODR 2560) = TIME_ACT × 8.25 ms per code ==> 
//    // TIME_ACT = Time / 8.25ms == 40ms / 8.25 ~= 5
//    // Inactivity threshold is 30g => 150 (30/0.2mg/LSB) ==> 4800 or 0x12C0 
//    // (shift by 5) since it is left justified. Add 1 to enable channel 12C1 
//    // Inactivity ==> Time = TIME_INACT × 32.5 ms per code
//    // TIME_INACT = Time / 32.5ms == 250ms / 32.5 ~= 7
//    cmd_buffer[0] = (ACC373_THRESH_ACT_X_H << 1) | 0x00; // 
//    cmd_buffer[1] = 0x25; // ACC373_THRESH_ACT_X_H
//    cmd_buffer[2] = 0x81; // ACC373_THRESH_ACT_X_L
//    cmd_buffer[3] = 0x25; // ACC373_THRESH_ACT_Y_H
//    cmd_buffer[4] = 0x81; // ACC373_THRESH_ACT_Y_L
//    cmd_buffer[5] = 0x25; // ACC373_THRESH_ACT_Z_H
//    cmd_buffer[6] = 0x81; // ACC373_THRESH_ACT_Z_L
//    //cmd_buffer[7] = 0x05; // ACC373_TIME_ACT >> 40ms
//    cmd_buffer[7] = 0x01; // ACC373_TIME_ACT >> 8.25ms
//    cmd_buffer[8] = 0x12; // ACC373_THRESH_INACT_X_H
//    cmd_buffer[9] = 0xC1; // ACC373_THRESH_INACT_X_L
//    cmd_buffer[10] = 0x12; // ACC373_THRESH_INACT_Y_H
//    cmd_buffer[11] = 0xC1; // ACC373_THRESH_INACT_Y_L
//    cmd_buffer[12] = 0x12; // ACC373_THRESH_INACT_Z_H
//    cmd_buffer[13] = 0xC1; // ACC373_THRESH_INACT_Z_L
//    cmd_buffer[14] = 0x00; // ACC373_TIME_INACT_H
//    cmd_buffer[15] = 0x07; // ACC373_TIME_INACT_L
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 16, 0); 
    
    
    // Activity threshold is 5g => 25 (5/0.2mg/LSB) ==> 25 or 0x0019 
    // (shift by 5) since it is left justified. Add 1 to enable channel 001A 
    // TIME (@ODR 2560) = TIME_ACT × 8.25 ms per code ==> 0x341
    // TIME_ACT = Time / 8.25ms == 40ms / 8.25 ~= 5
    // Inactivity threshold is 4g => 20 (3/0.2mg/LSB) ==> 15 or 0x000A 
    // (shift by 5) since it is left justified. Add 1 to enable channel 0x281
    // Inactivity ==> Time = TIME_INACT × 32.5 ms per code
    // TIME_INACT = Time / 32.5ms == 250ms / 32.5 ~= 7
//    cmd_buffer[0] = (ACC373_THRESH_ACT_X_H << 1) | 0x00; // 
//    cmd_buffer[1] = 0x03; // ACC373_THRESH_ACT_X_H
//    cmd_buffer[2] = 0x41; // ACC373_THRESH_ACT_X_L
//    cmd_buffer[3] = 0x03; // ACC373_THRESH_ACT_Y_H
//    cmd_buffer[4] = 0x41; // ACC373_THRESH_ACT_Y_L
//    cmd_buffer[5] = 0x03; // ACC373_THRESH_ACT_Z_H
//    cmd_buffer[6] = 0x41; // ACC373_THRESH_ACT_Z_L
//    //////////////////////////////////////////////////
//    //cmd_buffer[7] = 0x05; // ACC373_TIME_ACT >> 40ms
//    cmd_buffer[7] = 0x01; // ACC373_TIME_ACT >> 8.25ms
//    ////////////////////////////////////////////////////
//    cmd_buffer[8] = 0x02; // ACC373_THRESH_INACT_X_H
//    cmd_buffer[9] = 0x81; // ACC373_THRESH_INACT_X_L
//    cmd_buffer[10] = 0x02; // ACC373_THRESH_INACT_Y_H
//    cmd_buffer[11] = 0x81; // ACC373_THRESH_INACT_Y_L
//    cmd_buffer[12] = 0x02; // ACC373_THRESH_INACT_Z_H
//    cmd_buffer[13] = 0x81; // ACC373_THRESH_INACT_Z_L
//    ////////////////////////////////////////////////////
//    cmd_buffer[14] = 0x00; // ACC373_TIME_INACT_H
//    cmd_buffer[15] = 0x07; // ACC373_TIME_INACT_L
//    ////////////////////////////////////////////////////
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 16, 0); 
//    
//    ////////////////////////////////////////////////////////////////////////////
//    // set bandwidth and mode
//	cmd_buffer[0] = (ACC373_TIMING << 1) | 0x00;     // write CMD 
//    //cmd_buffer[1] = 0x80; // Set ODR to 5120
//    //cmd_buffer[1] = 0x60; // Set ODR to 2560
//    cmd_buffer[1] = 0x20; // Set ODR to 1280
//    //cmd_buffer[2] = 0x03; // defailt mode, Set 1280 Hz BW 
//	//cmd_buffer[2] = 0x23; // Loop mode, Set 1280 Hz BW 
//    //cmd_buffer[2] = 0x13; // linked, Set 1280 Hz BW ==> BW = 1/2 ODR
//    cmd_buffer[2] = 0x02; // default, Set 640 Hz BW ==> BW = 1/2 ODR
//    //cmd_buffer[2] = 0x03; // default, Set 1280 Hz BW ==> BW = 1/2 ODR
//    //cmd_buffer[2] = 0x04; // default, Set 2560 Hz BW ==> BW = 1/2 ODR
//	SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 3, 0); 

    ////////////////////////////////////////////////////////////////////////////
//    // set interrupt 
//    cmd_buffer[0] = (ACC373_INT1_MAP << 1) | 0x00; 
//    //cmd_buffer[1] = 0x80; // disable
//    //cmd_buffer[1] = 0x20; // ACT_INT1 active high
//    //cmd_buffer[1] = 0xA0; // ACT_INT1
//    cmd_buffer[1] = 0xB0; // ACT_INT1 and INACT_INT1
//    SPI_2_Routine(SPI_CS_ACC_HG, cmd_buffer, 2, 0);
    
    ////////////////////////////////////////////////////////////////////////////
    
    if(ADXL373_SPI_ID(SPI_CS_ACC_HG) == 0xAD)
    {
        ADXL373_SPI_Start_Sensor(); 
//        buffer[0] = 0xBB;
//        buffer[1] = 0xBB;       
//        buffer[2] = 0xB1; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 3); // debug
        
    }
    else
    {
        // error
        cmd_buffer[0] = 0xEE;
        cmd_buffer[1] = 0xEE;       
        cmd_buffer[2] = 0xE1; 
        CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); // debug
    }
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 0x6B
 * Description: 
 ******************************************************************************/
uint8_t ADXL373_SPI_ID(uint8_t cs_port)
{
   uint8_t cmd_buffer[1];
   uint8_t data_read; 
   cmd_buffer[0] = (ACC373_DEVID_AD << 1) | 0x01;     // return 0xAD
   //cmd_buffer[0] = (ACC373_DEVID_MST << 1) | 0x01;  // return 0x1D
   //cmd_buffer[0] = (ACC373_PARTID << 1) | 0x01;     // return 0xFA
   //cmd_buffer[0] = (ACC373_REVID << 1) | 0x01;      // return 0x02
   data_read = SPI_3_Routine(cs_port, cmd_buffer, 1, 1); 
   return data_read; 

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 0x6B
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Start_Sensor(void)
{
   uint8_t cmd_buffer[2];

   cmd_buffer[0] = (ACC373_POWER_CTL << 1) | 0x00;     // write CMD 
   //cmd_buffer[0] = ACC373_POWER_CTL;     // write CMD 
   cmd_buffer[1] = 0x03; // Full bandwidth measurement mode.
   SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 2, 0); 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 0x6B
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Stop_Sensor(void)
{
    uint8_t cmd_buffer[2];

    cmd_buffer[0] = (ACC373_POWER_CTL << 1) | 0x00;     // write CMD 
    //cmd_buffer[0] = ACC373_POWER_CTL;      // write CMD 
    cmd_buffer[1] = 0x00; // Standby
    SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 2, 0); 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 0x6B
 * Description: 
 ******************************************************************************/
void ADXL373_Shift_Data(uint8_t *input, uint8_t *output)
{
    // input is left justified
    // Compress the 6 bytes to 5 bytes by removing the 4 LSB bits created
    
    //X ==  input[0] + (input[1] & 0xF0)
    
    //Y ==  input[2] + (input[3] & 0xF0)
    
    //Z ==  input[4] + (input[5] & 0xF0)
    
//    output[0] = input[0]; 
//    output[1] = (input[1] & 0xF0) | ((input[2] & 0xF0) >> 4); 
//    output[2] = ((input[2] & 0x0F) << 4) | ((input[3] & 0xF0) >> 4); 
//    output[3] = ((input[3] & 0x0F) << 4) | ((input[4] & 0xF0) >> 4); 
//    output[4] = ((input[4] & 0x0F) << 4) | ((input[5] & 0xF0) >> 4); 
    
    output[0] = input[0]; 
    output[1] = (input[1] & 0xF0) | ((input[2] & 0xF0) >> 4); 
    output[2] = ((input[2] & 0x0F) << 4) | ((input[3] & 0xF0) >> 4); 
    output[3] = input[4];
    output[4] = ((input[5] & 0xF0) >> 4); 
    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 
 * Description:
 ******************************************************************************/
uint8_t ADXL373_SPI_Get_Data(uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len)
{
    uint8_t status; 
    status = SPI_3_Routine_Read(SPI_CS_ACC_HG, cmd, cmd_len, buffer, data_len);
    
    
    
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6); // debug
    return status; 
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
uint16_t ADXL373_SPI_Format_Level(const uint8_t *buffer)
{
    int16_t accel_X_HG;
    int16_t accel_Y_HG;
    int16_t accel_Z_HG;
    //uint8_t data[3];
    uint16_t sum_accel_axis_HG;
    
    accel_X_HG = buffer[0] & 0xFF;
    accel_X_HG = accel_X_HG << 4;
    accel_X_HG += ((buffer[1] & 0xF0) >> 4); 
//    if((accel_X_HG & 0x0800) == 0x0800)
//    {
//        accel_X_HG = 0xF000 | accel_X_HG; 
//    }
    
    accel_Y_HG = buffer[2] & 0xFF;
    accel_Y_HG = accel_Y_HG << 4;
    accel_Y_HG += ((buffer[3] & 0xF0) >> 4); 
//    if((accel_Y_HG & 0x0800) == 0x0800)
//    {
//        accel_Y_HG = 0xF000 | accel_Y_HG; 
//    }
    
    accel_Z_HG = buffer[4] & 0xFF;
    accel_Z_HG = accel_Z_HG << 4;
    accel_Z_HG += ((buffer[5] & 0xF0) >> 4); 
//    if((accel_Z_HG & 0x0800) == 0x0800)
//    {
//        accel_Z_HG = 0xF000 | accel_Z_HG; 
//    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Absolute function
    if((accel_X_HG & 0x0800) == 0x0800)
    {
        accel_X_HG = (~(accel_X_HG & 0x7FFF) + 1); 
    }
    
    if((accel_Y_HG & 0x0800) == 0x0800)
    {
        accel_Y_HG = (~(accel_Y_HG & 0x7FFF) + 1); 
    }
    
    if((accel_Z_HG & 0x0800) == 0x0800)
    {
        accel_Z_HG = (~(accel_Z_HG & 0x7FFF) + 1); 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // find approx magnitude

    // sum_accel_axis_HG = accel_X_HG * accel_X_HG +
    //                     accel_Y_HG * accel_Y_HG + 
    //                     accel_Z_HG * accel_Z_HG; 
    
    sum_accel_axis_HG = accel_X_HG + accel_Y_HG + accel_Z_HG; 
    
    return sum_accel_axis_HG; 
}


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Check_Level(const uint8_t *buffer)
{
    int16_t accel_X_HG;
    int16_t accel_Y_HG;
    int16_t accel_Z_HG;
    uint8_t data[4];
    uint32_t sum_accel_axis_HG;
    uint8_t flag_Value = 0; 
    uint8_t buffer_in[6];
    uint8_t buffer_out[5];
    //uint8_t buffer_temp[16];
//    int *xmemory;
//    int *ymemory;
//    int xVal, yVal;
    int32_t result_X2 = 0;
    int32_t result_Y2 = 0;
    int32_t result_Z2 = 0;
    //volatile register int result_X2 asm("A");
    //volatile register int result_Y2 asm("A");
    //volatile register int result_Z2 asm("A");
    
    accel_X_HG = buffer[0] & 0xFF;
    accel_X_HG = accel_X_HG << 4;
    accel_X_HG += ((buffer[1] & 0xF0) >> 4); 
    if((accel_X_HG & 0x0800) == 0x0800)
    {
        accel_X_HG = 0xF000 | accel_X_HG; 
        accel_X_HG = ~accel_X_HG + 1; 
    }
    
    accel_Y_HG = buffer[2] & 0xFF;
    accel_Y_HG = accel_Y_HG << 4;
    accel_Y_HG += ((buffer[3] & 0xF0) >> 4); 
    if((accel_Y_HG & 0x0800) == 0x0800)
    {
        accel_Y_HG = 0xF000 | accel_Y_HG; 
        accel_Y_HG = ~accel_Y_HG + 1; 
    }
    
    accel_Z_HG = buffer[4] & 0xFF;
    accel_Z_HG = accel_Z_HG << 4;
    accel_Z_HG += ((buffer[5] & 0xF0) >> 4); 
    if((accel_Z_HG & 0x0800) == 0x0800)
    {
        accel_Z_HG = 0xF000 | accel_Z_HG; 
        accel_Z_HG = ~accel_Z_HG + 1; 
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Multiplication

    result_X2 = Multiplication(accel_X_HG,accel_X_HG); // 2.6us
    
    result_Y2 = Multiplication(accel_Y_HG,accel_Y_HG); // 2.6us
    
    result_Z2 = Multiplication(accel_Z_HG,accel_Z_HG); // 2.6us
    
    
    sum_accel_axis_HG = result_X2 + result_Y2 + result_Z2; 
    
    // 25g = 15625
    // 50g = 62500
    // 75g = 140625
    // 100g = 250000
    // 150g = 562500
    // 200g = 1000000
    // 250g = 1562500
    // 300g = 2250000
    // 350g = 3062500
    // 400g = 4000000


    
    if((flag_Value == 0) && (sum_accel_axis_HG > 4000000)) // 400g
    {
        if(Burst_Flag.Level_400g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 10;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_400g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 3062500)) // 350g
    {
        if(Burst_Flag.Level_350g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 9;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_350g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 2250000)) // 300g
    {
        if(Burst_Flag.Level_300g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 8;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_300g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 1562500)) // 250g
    {
        if(Burst_Flag.Level_250g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 7;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0;  
            Burst_Flag.Level_250g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        } 
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 1000000)) // 200g
    {
        if(Burst_Flag.Level_200g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 6;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_200g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 562500)) // 150g
    {
        if(Burst_Flag.Level_150g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 5;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0;  
            Burst_Flag.Level_150g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 250000)) // 100g
    {
        if(Burst_Flag.Level_100g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 4;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_100g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 140625)) // 75g
    {
        if(Burst_Flag.Level_75g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 3;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_75g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 62500)) // 50g
    {
        if(Burst_Flag.Level_50g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 2;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0;  
            Burst_Flag.Level_50g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
    if((flag_Value == 0) && (sum_accel_axis_HG > 15625)) // 25g
    {
        if(Burst_Flag.Level_25g == 1)
        {
            Burst_Trigger_Sample_Counter++; 
            if(Burst_Trigger_Sample_Counter >= BURST_TRIGGER_SAMPLE_TIME)
            {
                State_Flags.Burst_State = 1; 
                //Save_Event_Cmd_Buffer(0xAA, 0x0A); 
                flag_Value = 1;
                //return; 
            }
        }
        else
        {
            Burst_Flag.Level_25g = 0; 
            Burst_Flag.Level_50g = 0; 
            Burst_Flag.Level_75g = 0; 
            Burst_Flag.Level_100g = 0; 
            Burst_Flag.Level_150g = 0; 
            Burst_Flag.Level_200g = 0; 
            Burst_Flag.Level_250g = 0; 
            Burst_Flag.Level_300g = 0; 
            Burst_Flag.Level_350g = 0; 
            Burst_Flag.Level_400g = 0; 
            //Burst_Flag.All_Level_Flags = 0; 
            Burst_Flag.Level_25g = 1; 
            Burst_Trigger_Sample_Counter = 1; 
        }
        
    }
 
    ////////////////////////////////////////////////////////////////////////////
 
    if((flag_Value > 0) && (State_Flags.Burst_Paused == 0))
    {
        buffer_in[0] = buffer[0];
        buffer_in[1] = buffer[1];
        buffer_in[2] = buffer[2];
        buffer_in[3] = buffer[3];
        buffer_in[4] = buffer[4];
        buffer_in[5] = buffer[5];
        
        ADXL373_Shift_Data(buffer_in,buffer_out); 
    
        data[0] = buffer_out[1];
        data[1] = buffer_out[2];
        data[2] = buffer_out[3];
        data[3] = (buffer_out[4] & 0xF0) | (flag_Value & 0x0F);

        Save_Event_Buffer(0xAD, buffer_out[0], data); 
        
//        data[0] = sum_accel_axis_HG>>24;
//        data[1] = sum_accel_axis_HG>>16;
//        data[2] = sum_accel_axis_HG>>8;
//        data[3] = sum_accel_axis_HG;
//        
//        Save_Event_Buffer(0xAE, flag_Value, data); 
        
//        buffer_temp[0]  = result_X2 >> 24; 
//        buffer_temp[1]  = result_X2 >> 16; 
//        buffer_temp[2]  = result_X2 >> 8; 
//        buffer_temp[3]  = result_X2; 
//        buffer_temp[4]  = result_Y2 >> 24; 
//        buffer_temp[5]  = result_Y2 >> 16; 
//        buffer_temp[6]  = result_Y2 >> 8; 
//        buffer_temp[7]  = result_Y2; 
//        buffer_temp[8]  = result_Z2 >> 24; 
//        buffer_temp[9]  = result_Z2 >> 16; 
//        buffer_temp[10] = result_Z2 >> 8; 
//        buffer_temp[11] = result_Z2; 
//        buffer_temp[12] = sum_accel_axis_HG>>24; 
//        buffer_temp[13] = sum_accel_axis_HG>>16; 
//        buffer_temp[14] = sum_accel_axis_HG>>8; 
//        buffer_temp[15] = sum_accel_axis_HG; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer_temp, 16);
    }
    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t ADXL373_SPI_Get_Register(uint8_t reg)
{
    uint8_t cmd_buffer[2];

    //cmd_buffer[0] = (ACC373_STATUS << 1) | 0x01;
    cmd_buffer[0] = (reg << 1) | 0x01;
    
    return SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 1, 1); 
   

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t ADXL373_SPI_Get_Interrupt(void)
{
    uint8_t cmd_buffer[2];

    //cmd_buffer[0] = (ACC373_STATUS << 1) | 0x01;
    cmd_buffer[0] = (ACC373_STATUS2 << 1) | 0x01;
    
    return SPI_3_Routine(SPI_CS_ACC_HG, cmd_buffer, 1, 1); 
   

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: 
 * Description: 
 ******************************************************************************/
void ADXL373_SPI_Get_Max_Peak(void)
{
    uint8_t cmd_buffer[2];
    uint8_t buffer[6];
    uint8_t buffer_out[5];
    
    cmd_buffer[0] = (ACC373_MAXPEAK_X_H << 1) | 0x01;
    
    ADXL373_SPI_Get_Data(cmd_buffer, 1, buffer, 6); 
    
    //CAN_Encode_Sending(0x1B,0xC4, buffer, 6);
    
    ADXL373_Shift_Data(buffer,buffer_out); 
    
    buffer[0] = buffer_out[1];
    buffer[1] = buffer_out[2];
    buffer[2] = buffer_out[3];
    buffer[3] = buffer_out[4];

    
    Save_Event_Buffer(0xAC, buffer_out[0], buffer); 
}

/*******************************************************************************
 * Function: Check_Fifo_Full
 * Parameters: none
 * Return: uint8_t
 * Description:
 ******************************************************************************/
uint8_t ADXL373_Check_Fifo_Full(void)
{
    uint8_t status = 0; 
    
    status = ADXL373_SPI_Get_Register(ACC373_STATUS); 
    
    if(status & 0x04) // fifo full
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: uint8_t
 * Description: 
 ******************************************************************************/
uint8_t ADXL373_Read_Fifo(void)
{
//    uint8_t fifoEntries = 0; 
//    uint8_t cmd_buffer[3];
//    uint8_t buffer[FIFO_SIZE_3X];
//    uint8_t buffer_tempo[6];
//    uint8_t buffer_in[6];
//    uint8_t buffer_out[5];
//    uint8_t data[4];
//    uint8_t i,j; 
//    uint8_t pointer = 0;
    uint8_t flag_peak = 0;
//    uint16_t sum_accel_axis_HG;
//    uint16_t sum_accel_axis_HG_Peak;
//    
//    //cmd_buffer[0] = (ACC373_FIFO_DATA << 1) | 0x01;
//    
////    fifoEntries = ADXL373_SPI_Get_Register(ACC373_FIFO_ENTRIES); 
////    
////    if(fifoEntries > FIFO_SIZE_3X)
////    {
////        fifoEntries = FIFO_SIZE_3X; 
////    }
////    
////    cmd_buffer[0] = (ACC373_XDATA_H << 1) | 0x01;
////    
////    ADXL373_SPI_Get_Data(cmd_buffer, 1, buffer, fifoEntries); 
////    
////    if(fifoEntries % 3 == 0)
////    {
////        return;
////    }
//    
//
//    if(ADXL373_Check_Fifo_Full())
//    {
//        //flag_return = 1;
//        // ADXL373_SPI_Check_Level(const uint8_t *buffer)
//
//        cmd_buffer[0] = (ACC373_FIFO_DATA << 1) | 0x01;
//    
//        ADXL373_SPI_Get_Data(cmd_buffer, 1, buffer, FIFO_SIZE_3X); 
//        
//        
//        for(j=0; j < FIFO_SIZE; j++)
//        {
//            for(i=0; i < 6; i++)
//            {
//                buffer_tempo[i] = buffer[pointer++]; 
//            }
//            sum_accel_axis_HG = ADXL373_SPI_Format_Level(cmd_buffer); 
//            
//            if(sum_accel_axis_HG > Shock_Threshold)
//            {
//                if(sum_accel_axis_HG > sum_accel_axis_HG_Peak)
//                {
//                    flag_peak++;
//                    sum_accel_axis_HG_Peak = sum_accel_axis_HG; 
//                    for(i=0; i < 6; i++)
//                    {
//                        buffer_in[i] = buffer_tempo[i]; // save highest peak
//                    }
//                }
//
//            }
//        }
//        
//        
//    }
//    else
//    {
//        flag_peak = 0;
//    }
//    
//    if(flag_peak > 3)
//    {
//        ADXL373_Shift_Data(buffer_in,buffer_out); 
//
//        data[0] = buffer_out[1];
//        data[1] = buffer_out[2];
//        data[2] = buffer_out[3];
//        data[3] = buffer_out[4];
//
//        Save_Event_Buffer(0xAC, buffer_out[0], data); 
//    }

    return flag_peak;
}