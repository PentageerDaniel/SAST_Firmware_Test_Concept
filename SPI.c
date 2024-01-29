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
#include "SPI.h"

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_SPI_1()
{
    //SPI2CON1L = 0; 
    //SPI2CON1H = 0; 
    SPI1CON1Lbits.SPIEN = 0; 
    // IPC2bits.SPI1TXIP = 4; //Set SPI Interrupt Priorities
    
    //SPI2BRGL = 0x0; // Fbclk = 10Mhz, ==> 5Mhz
    //SPI2BRGL = 0x5; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 2Mhz 
    //SPI2BRGL = 0x2; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 4Mhz 
    
    SPI1BRGL = 0x1; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 2.5Mhz
    //SPI2BRGL = 0x2; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 1.66Mhz
    //SPI2BRGL = 0x3; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 1.25Mhz
    
    SPI1STATLbits.SPIROV = 0; // clear the Overflow
    
    //SPI2CON1L = 0x0420; // 16 bits transfer, Master mode,ckp=0,cke=0,smp=0
    SPI1CON1L = 0x0020; // 8 bits transfer, Master mode,ckp=0,cke=0,smp=0
    //SPI2CON1Lbits.ENHBUF = 0; 
    SPI1CON1Lbits.CKE = 1; // TESTed memory
    //SPI1CON1Lbits.CKE = 0; // Trial new ADC TI
    SPI1CON1Lbits.CKP = 0; // CLK_IDLE_LOW
    //SPI2CON1Lbits.CKP = 1; // Clock reverse polarity
    
    SPI1CON1Hbits.IGNROV = 1; 
    
    //SPI2CON2Lbits.WLENGTH = 3; // NFG
    SPI1CON2Lbits.WLENGTH = 7; // ok, read work at 2nd
    //SPI2CON2Lbits.WLENGTH = 0xF; // nope
    
    
    //SPI2IMSKLbits.SPITBFEN = 1; // SPI1 transmit buffer full generates interrupt event
    
    SPI1CON1Lbits.MSTEN = 1; 
    
    // IEC0bits.SPI2TXIE = 1; // Enable interrupts
          
    SPI1CON1Lbits.SPIEN = 1; 
}


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_SPI_2()
{
    //SPI2CON1L = 0; 
    //SPI2CON1H = 0; 
    SPI2CON1Lbits.SPIEN = 0; 
    // IPC2bits.SPI1TXIP = 4; //Set SPI Interrupt Priorities
    
    //SPI2BRGL = 0x0; // Fbclk = 10Mhz, ==> 5Mhz
    //SPI2BRGL = 0x5; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 2Mhz 
    //SPI2BRGL = 0x2; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 4Mhz 
    
    SPI2BRGL = 0x1; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 2.5Mhz
    //SPI2BRGL = 0x2; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 1.66Mhz
    //SPI2BRGL = 0x3; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 1.25Mhz
    
    SPI2STATLbits.SPIROV = 0; // clear the Overflow
    
    //SPI2CON1L = 0x0420; // 16 bits transfer, Master mode,ckp=0,cke=0,smp=0
    SPI2CON1L = 0x0020; // 8 bits transfer, Master mode,ckp=0,cke=0,smp=0
    //SPI2CON1Lbits.ENHBUF = 0; 
    SPI2CON1Lbits.CKE = 1; // debug memory
    SPI2CON1Lbits.CKP = 0; // CLK_IDLE_LOW
    //SPI2CON1Lbits.CKP = 1; // Clock reverse polarity
    
    SPI2CON1Hbits.IGNROV = 1; 
    
    //SPI2CON2Lbits.WLENGTH = 3; // NFG
    SPI2CON2Lbits.WLENGTH = 7; // ok, read work at 2nd
    //SPI2CON2Lbits.WLENGTH = 0xF; // nope
    
    
    //SPI2IMSKLbits.SPITBFEN = 1; // SPI1 transmit buffer full generates interrupt event
    
    SPI2CON1Lbits.MSTEN = 1; 
    
    // IEC0bits.SPI2TXIE = 1; // Enable interrupts
          
    SPI2CON1Lbits.SPIEN = 1; 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_SPI_3()
{
    //SPI2CON1L = 0; 
    //SPI2CON1H = 0; 
    SPI3CON1Lbits.SPIEN = 0; 
    // IPC2bits.SPI1TXIP = 4; //Set SPI Interrupt Priorities
    
    //SPI2BRGL = 0x0; // Fbclk = 10Mhz, ==> 5Mhz
    //SPI2BRGL = 0x5; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 2Mhz 
    //SPI2BRGL = 0x2; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 4Mhz 
    
    SPI3BRGL = 0x1; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 2.5Mhz
    //SPI2BRGL = 0x2; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 1.66Mhz
    //SPI2BRGL = 0x3; // Fsck == 10Mhz = Fpb /  (2 * (SPIxBRGL + 1 ) == 1.25Mhz
    
    SPI3STATLbits.SPIROV = 0; // clear the Overflow
    
    //SPI2CON1L = 0x0420; // 16 bits transfer, Master mode,ckp=0,cke=0,smp=0
    SPI3CON1L = 0x0020; // 8 bits transfer, Master mode,ckp=0,cke=0,smp=0
    //SPI2CON1Lbits.ENHBUF = 0; 
    SPI3CON1Lbits.CKE = 1; // debug memory
    SPI3CON1Lbits.CKP = 0; // CLK_IDLE_LOW
    //SPI2CON1Lbits.CKP = 1; // Clock reverse polarity
    
    SPI3CON1Hbits.IGNROV = 1; 
    
    //SPI2CON2Lbits.WLENGTH = 3; // NFG
    SPI3CON2Lbits.WLENGTH = 7; // ok, read work at 2nd
    //SPI2CON2Lbits.WLENGTH = 0xF; // nope
    
    
    //SPI2IMSKLbits.SPITBFEN = 1; // SPI1 transmit buffer full generates interrupt event
    
    SPI3CON1Lbits.MSTEN = 1; 
    
    // IEC0bits.SPI2TXIE = 1; // Enable interrupts
          
    SPI3CON1Lbits.SPIEN = 1; 
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_SPI_2_slave()
{
    //SPI2CON1L = 0; 
    //SPI2CON1H = 0; 
    
    // IPC2bits.SPI1TXIP = 4; //Set SPI Interrupt Priorities
    
    //SPI2BRGL = 0x5; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 2Mhz 
    //SPI2BRGL = 0x2; // Fsck = Fpb /  (2 * (SPIxBRGL + 1 ) == 4Mhz 
    
    SPI2STATLbits.SPIROV = 0; // clear the Overflow
    SPI2STATLbits.SPIRBE = 0; // clear the empty butffer
    SPI2STATLbits.SPITUR = 0; // clear the empty butffer
    
    
    //SPI2CON1L = 0x0420; // 16 bits transfer, Master mode,ckp=0,cke=0,smp=0
    //SPI2CON1L = 0x0020; // 8 bits transfer, Master mode,ckp=0,cke=0,smp=0
    SPI2CON1L = 0x0080; // 8 bits transfer, Slave mode,ckp=0,cke=0,smp=0
    SPI2CON1Lbits.SSEN = 1;
    //SPI2CON1Lbits.ENHBUF = 1; 
    SPI2CON1Lbits.CKE = 1; // debug memory
    SPI2CON1Lbits.CKP = 0; // CLK_IDLE_LOW
    //SPI2CON1Lbits.CKP = 1; // Clock reverse polarity
    
    SPI2CON1Hbits.AUDEN = 0; 
    
    //SPI2CON1Hbits.IGNTUR = 1; 
    //SPI2CON1Hbits.URDTEN = 1; 
    //SPI2CON1Lbits.MODE16 = 1; 
    //SPI2CON1Hbits.IGNROV = 1; 
    
    //SPI2CON2Lbits.WLENGTH = 3; // NFG
    SPI2CON2Lbits.WLENGTH = 7; // ok, read work at 2nd
    //SPI2CON2Lbits.WLENGTH = 0xF; // nope
    //SPI2CON2Lbits.WLENGTH = 0; // 
    
    
    //SPI2IMSKLbits.SPITBFEN = 1; // SPI1 transmit buffer full generates interrupt event
    
    //SPI2CON1Lbits.MSTEN = 1; 
    //SPI2IMSKLbits.SPIROVEN = 1; 
    
    SPI2IMSKLbits.SPIRBFEN = 1; // SPIx receive buffer full generates an interrupt event
    
    //SPI2STATLbits.SPIRBE = 0; // clear the empty butffer
    //SPI2BUFL = 0x00; 
    
    //SPI2IMSKLbits.SPIRBEN = 1; // generate event empty buffer
    
    //SPI2IMSKLbits.SPITBEN = 1; //SPIx transmit buffer empty generates an interrupt event
    //SPI2IMSKLbits.SPITUREN = 1; 
    
    SPI2IMSKLbits.BUSYEN = 1; 
    
    //SPI2IMSKLbits.SPITBEN = 1; // too slow, missed the first byte
    
    IEC1bits.SPI2RXIE = 1; // Enable RX interrupts
    IEC7bits.SPI2IE = 1; // Enable error interrupts
    //IEC1bits.SPI2TXIE = 1; 
          
    SPI2CON1Lbits.SPIEN = 1; 
}


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void set_SS_Accel(uint8_t cs_port)
{
    MUX1_ADG732_CHIP_SELECT(cs_port);
//    switch (cs_port)
//    {
//        case 1:
//            CS_MEM1 = 0; 
//            break;
//        case 2:
//            CS_MEM2 = 0; 
//            break;
//#ifndef Debug_Board
//        case 3:
//            CS_MEM3 = 0; 
//            break;
//        case 4:
//            CS_MEM4 = 0; 
//            break;    
//        case 5:
//            CS_MEM5 = 0; 
//            break;    
//        case 6:
//            CS_MEM6 = 0; 
//            break;
//        case 7:
//            CS_MEM7 = 0; 
//            break;    
//        case 8:
//            CS_MEM8 = 0; 
//            break;    
//        case 9:
//            CS_MEM9 = 0; 
//            break;    
//        case 10:
//            CS_MEM10 = 0; 
//            break;    
//        case 11:
//            CS_MEM11 = 0; 
//            break;
//        case 12:
//            CS_MEM12 = 0; 
//            break;
//        case 13:
//            CS_MEM13 = 0; 
//            break;
//        case 14:
//            CS_MEM14 = 0; 
//            break;
//        case 15:
//            CS_MEM15 = 0; 
//            break;    
//        case 16:
//            CS_MEM16 = 0; 
//            break;    
//        case 17:
//            CS_MEM17 = 0; 
//            break;
//        case 18:
//            CS_MEM18 = 0; 
//            break;    
//        case 19:
//            CS_MEM19 = 0; 
//            break;     
//        case 20:
//            CS_MEM20 = 0; 
//            break;        
//#endif
//        case 21:
//            CS_ACC_LG1 = 0; 
//            break;    
//        case 22:
//            CS_ACC_HG = 0; 
//            break;       
//            
//    }
    //PORTAbits.RA0 = 0; 
    //PORTCbits.RC12 = 0; // CS_MEM1
    //PORTCbits.RC13 = 0; // CS_Accel
//    switch(Chip_Select)
//    {
//        case CS_ACC_1:
//            PORTCbits.RC4 = 0; // CS_Accel
//            break;
//        case CS_ACC_2:
//            PORTCbits.RC3 = 0; // CS_Accel
//            break;
//        case CS_ACC_3:
//            PORTCbits.RC2 = 0; // CS_Accel
//            break;
//        default:
//            PORTCbits.RC4 = 1; // CS_Accel
//            break;
}
    

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void disable_SS_Accel(uint8_t cs_port)
{
    MUX1_ADG732_CHIP_DESELECT(0);
    
//    switch (cs_port)
//    {
//        case 1:
//            CS_MEM1 = 1; 
//            break;
//        case 2:
//            CS_MEM2 = 1; 
//            break;
//#ifndef Debug_Board
//        case 3:
//            CS_MEM3 = 1; 
//            break;
//        case 4:
//            CS_MEM4 = 1; 
//            break;    
//        case 5:
//            CS_MEM5 = 1; 
//            break;    
//        case 6:
//            CS_MEM6 = 1; 
//            break;
//        case 7:
//            CS_MEM7 = 1; 
//            break;    
//        case 8:
//            CS_MEM8 = 1; 
//            break;    
//        case 9:
//            CS_MEM9 = 1; 
//            break;    
//        case 10:
//            CS_MEM10 = 1; 
//            break;    
//        case 11:
//            CS_MEM11 = 1; 
//            break;
//        case 12:
//            CS_MEM12 = 1; 
//            break;
//        case 13:
//            CS_MEM13 = 1; 
//            break;
//        case 14:
//            CS_MEM14 = 1; 
//            break;
//        case 15:
//            CS_MEM15 = 1; 
//            break;    
//        case 16:
//            CS_MEM16 = 1; 
//            break;    
//        case 17:
//            CS_MEM17 = 1; 
//            break;
//        case 18:
//            CS_MEM18 = 1; 
//            break;    
//        case 19:
//            CS_MEM19 = 1; 
//            break;     
//        case 20:
//            CS_MEM20 = 1; 
//            break;        
//#endif
//        case 21:
//            CS_ACC_LG1 = 1; 
//            break;    
//        case 22:
//            CS_ACC_HG = 1; 
//            break;       
//            
//    }
    //PORTAbits.RA0 = 1; 
    //PORTCbits.RC12 = 1; // CS_MEM1
    //PORTCbits.RC13 = 1; // CS_Accel
//     switch(Chip_Select)
//    {
//        case CS_ACC_1:
//            PORTCbits.RC4 = 1; // CS_Accel
//            break;
//        case CS_ACC_2:
//            PORTCbits.RC3 = 1; // CS_Accel
//            break;
//        case CS_ACC_3:
//            PORTCbits.RC2 = 1; // CS_Accel
//            break;
//         default:
//             PORTCbits.RC4 = 1; // CS_Accel
//             break;
//    }
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint16_t SPI_1_Write(uint16_t cmd)
{
    SPI1BUFL = cmd; 
    while (!SPI1STATLbits.SPIRBF);
    return SPI1BUFL; 
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint16_t SPI_2_Write(uint16_t cmd)
{
    SPI2BUFL = cmd; 
    while (!SPI2STATLbits.SPIRBF);
    return SPI2BUFL; 
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint16_t SPI_3_Write(uint16_t cmd)
{
    SPI3BUFL = cmd; 
    while (!SPI3STATLbits.SPIRBF);
    return SPI3BUFL; 
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_2_Write_Slave(uint8_t cmd)
{
    //while (SPI2STATLbits.SPIRBF){};// 
    //SPI2BUFL = cmd; 
    while (!SPI2STATLbits.SPIRBF){};// 
    SPI2BUFL = cmd; 
    return SPI2BUFL; 
    //while (SPI2STATLbits.SPITBF){};// 
    //while (SPI2STATLbits.SPIRBF){}; // not work
    //while (SPI2STATLbits.SPIBUSY){}; // wait transmitter is ready
    //while (SPI2STATLbits.SPIRBE);// not work
    //while (!SPI2STATLbits.SPIRBE);
    //while (!SPI2STATLbits.SPIRBE);
    //return SPI2BUFL; 
}


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_1_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len)
{
    uint8_t i; 
    uint8_t byte_read[64]; 
    uint16_t ret;

    set_SS_Accel(cs_port);
    
    for(i=0; i<cmd_len; i++)
    {
        ret = SPI_1_Write(cmd[i]);
    }
    
    for(i=0; i<data_len; i++)
    {
        byte_read[i] = SPI_1_Write(0x0000); // send dummy
    }
    
    while (SPI1STATLbits.SPIBUSY){}; // wait transmitter is ready
    disable_SS_Accel(cs_port); 

    ret = byte_read[0]; 
    return ret; 
    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len)
{
    uint8_t i; 
    uint8_t byte_read[64]; 
    uint16_t ret;

    set_SS_Accel(cs_port);
    
    for(i=0; i<cmd_len; i++)
    {
        ret = SPI_2_Write(cmd[i]);
    }
    
    for(i=0; i<data_len; i++)
    {
        byte_read[i] = SPI_2_Write(0x0000); // send dummy
    }
    
    while (SPI2STATLbits.SPIBUSY){}; // wait transmitter is ready
    disable_SS_Accel(cs_port); 

    ret = byte_read[0]; 
    return ret; 
    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_3_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len)
{
    uint8_t i; 
    uint8_t byte_read[64]; 
    uint16_t ret;

    set_SS_Accel(cs_port);
    
    for(i=0; i<cmd_len; i++)
    {
        ret = SPI_3_Write(cmd[i]);
    }
    
    for(i=0; i<data_len; i++)
    {
        byte_read[i] = SPI_3_Write(0x0000); // send dummy
    }
    
    while (SPI3STATLbits.SPIBUSY){}; // wait transmitter is ready
    disable_SS_Accel(cs_port); 

    ret = byte_read[0]; 
    return ret; 
    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void read_SPI_2_Slave(uint8_t  SPI_2_data_byte)
{
//    //uint8_t buffer[3] = {0x10, 0x11, 0x12};
//    uint16_t length = 0; 
//    /* Format Uart 1 
//     * SOF (1 byte) == 0x0C
//     * Source (1 byte) == 0x1B (Computer)
//     * Destination (1 byte) == 0x1A (Board) 
//     * Command (1 byte)
//     * Length (2 byte) == 
//     * Data (length bytes) == min 1 byte
//     * Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
//     * EOF ((1 byte)     
//     */
//     
//    //write_uart_1(SPI_2_data_byte); // debug
//
//    
//    if(SPI_2_Status.RX_Received == 0)
//    {
//        if(SPI_2_data_pointer == 0)
//        {
//            if(SPI_2_data_byte == 0x0C) // start of file
//            {
//                SPI_2_data_buffer[0] = SPI_2_data_byte; 
//                SPI_2_data_pointer += 1;               // SOF
//                SPI_2_Status.RX_Started = 1;//Data_COM_Status |= Data_RX_Started;
//                SPI_2_data_timeout_counter = 0;
//                 
//            }
//
//        }
//        else
//        {
//            
//            SPI_2_data_buffer[SPI_2_data_pointer] = SPI_2_data_byte; 
//            SPI_2_data_pointer += 1;
//            //LEDR = 1;
//            if(SPI_2_data_byte == 0x0D)
//            {
//                
//                /*
//                * 0 = SOF (1 byte) == 0x0C (Not in checksum)
//                * 1 = Source (1 byte) == 0x1A (Board)
//                * 2 = Destination (1 byte) == 0x1B (Computer)
//                * 3 = Command (1 byte)     
//                * 4-5 = Length (2 byte) == 
//                 */
//                 //Uart_1_Status.RX_Received = 1; // Data_COM_Status |= Data_RX_Received;
//                 //Uart_1_Status.RX_Started = 0; //Data_COM_Status &= ~Data_RX_Started;
//                 //Uart_1_data_timeout_counter = 0; //Data_COM_Timeout_Counter = 0; 
//                 //Uart_1_Status.RX_Timeout = 0; //Data_COM_Flag &= ~Data_COM_Timeout;
//                if(SPI_2_data_pointer >= 6) // length
//                {
//                    length = (SPI_2_data_buffer[4] << 8) + SPI_2_data_buffer[5]; 
//                    if(length == SPI_2_data_pointer)
//                    {
//                        SPI_2_Status.RX_Received = 1; // Data_COM_Status |= Data_RX_Received;
//                        SPI_2_Status.RX_Started = 0; //Data_COM_Status &= ~Data_RX_Started;
//                        SPI_2_data_timeout_counter = 0; //Data_COM_Timeout_Counter = 0; 
//                        SPI_2_Status.RX_Timeout = 0; //Data_COM_Flag &= ~Data_COM_Timeout;
//                        //decode_uart_1_message(); 
//                    }
////                    else
////                    {
////                        write_uart_1(0xEE); //debug
////                        write_uart_1(Uart_1_data_pointer); //debug
////                        write_uart_1(length & 0xFF); //debug
////                    }
//                }
//                 
//            }
//
//            if(SPI_2_data_pointer > 128)
//            {
//                // error overflow
//                reset_SPI_2_registers(); 
//                //SPI_2_send_message(0xE2, buffer, 3);
//            }
//        }
//    }
//    else
//    {
//        // error
//        // message not processed yet
//        //uart_1_send_message(0xE3, buffer, 3);
//    }
}

/*******************************************************************************
 * Function: reset_uart_1_registers
 * Parameters: none
 * Return: none
 * Description: Reset Uart 1 registers after error or end of com
 ******************************************************************************/
void reset_SPI_2_registers(void)
{
//    int i;
//    
//    SPI_2_Status.RX_Received = 0; // Data_COM_Status |= Data_RX_Received;
//    SPI_2_Status.RX_Started = 0; //Data_COM_Status &= ~Data_RX_Started;
//    SPI_2_data_timeout_counter = 0; //Data_COM_Timeout_Counter = 0; 
//    SPI_2_Status.RX_Timeout = 0; //Data_COM_Flag &= ~Data_COM_Timeout;
//    SPI_2_data_pointer = 0; 
//    for (i=0; i < SPI_2_data_pointer; i++)
//    {
//        SPI_2_data_Received[i] = 0; 
//        SPI_2_data_buffer[i] = 0;
//    }
}

/*******************************************************************************
 * Function: decode_uart_1_message
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void decode_SPI_2_message(void)
{
//    int i;
//    uint8_t buffer[20] = {0};
//    uint16_t checksum16 = 0;
//    unsigned char checksum8_2nd = 0;
//
//    
//    for (i=1; i < SPI_2_data_pointer; i++) // remove SOF
//    {
//        if((i != 0) && (i<SPI_2_data_pointer-2))
//        {
//            // remove SOF, checksum and EOF
//            checksum16 += SPI_2_data_buffer[i];
//        }
//    }
//    
//    SPI_2_Status.RX_Received = 0; 
//    
//    /* Format SPI_2 
//     * [0] => SOF (1 byte) == 0x0C (Not in checksum)
//     * [1] => Source (1 byte) == 0x1B (Computer)
//     * [2] => Destination (1 byte) == 0x1A (Board) 
//     * [3] => Command (1 byte)     
//     * [4] => Length (2 byte) == 
//     * [5] => Length
//     * [6] => Data (length bytes) ==  to nBytes
//     * [length + 6] => Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
//     * [length + 7] => EOF ((1 byte) (Not in checksum)     
//     */
//    
//    checksum8_2nd = ~((checksum16 & 0x00FF)) + 1; // get 2nd comp. of 8 bits
//    
//    if(SPI_2_data_pointer >= 6 && (SPI_2_data_buffer[SPI_2_data_pointer-1] == 0x0D))
//    {
//        if(checksum8_2nd == SPI_2_data_buffer[SPI_2_data_pointer-2])
//        {
//            switch(SPI_2_data_buffer[3])
//            {
//                case 0x01: // Test
//                    //SPI_2_send_message(0x02, buffer, 3);
//                    uart_1_send_message(0xC1, buffer, 3);
////                    SPI_2_data_TX[0] = 0x00; 
////                    SPI_2_data_TX[1] = 0x01; 
////                    SPI_2_data_TX[2] = 0x02; 
////                    SPI_2_data_TX[3] = 0x03; 
////                    SPI_2_data_TX[4] = 0x04; 
////                    SPI_2_data_TX[5] = 0x05; 
////                    SPI_2_data_TX[6] = 0x06; 
////                    SPI_2_data_TX[7] = 0x07; 
////                    SPI_2_data_TX_pointer = 0; 
////                    SPI_2_TX_Number_Bytes_To_Send = 0x08; 
////                    Set_GPIO_USB_3(); 
//                    //WriteBuffer(buffer, 0x01, 3); 
//                    //uart_1_send_message(0x02,buffer,0); 
//                    break;
//                case 0x03: // Test
//                    uart_1_send_message(0xBB, buffer, 3);
////                    SPI_2_data_TX[0] = 0x00; 
////                    SPI_2_data_TX[1] = 0x01; 
////                    SPI_2_data_TX[2] = 0x02; 
////                    SPI_2_data_TX[3] = 0x03; 
////                    SPI_2_data_TX[4] = 0x04; 
////                    SPI_2_data_TX[5] = 0x05; 
////                    SPI_2_data_TX[6] = 0x06; 
////                    SPI_2_data_TX[7] = 0x07; 
////                    SPI_2_data_TX_pointer = 0; 
////                    SPI_2_TX_Number_Bytes_To_Send = 0x08; 
////                    Set_GPIO_USB_3(); 
//                    //uart_1_send_message(0xC1, buffer, 3);
//                    //WriteBuffer(buffer, 0x01, 3); 
//                    //Set_GPIO_USB_3(); 
//                    //uart_1_send_message(0x04,buffer,0); 
//                    
//                    break;  
//                case 0x05: // Test
//
//                    break;  
//
//                case 0xB0: // Write to flash    
//                    
//                    
//                    break;
//                case 0xBB: // Enter boot - Ready to write   
//                    //Uart_1_Status.Boot_Request = 1; 
//                    //uart_1_send_message(0xBC, buffer, 0);
//                    break;
//                    ////////////////////////////////////////////////////////////
//                default:
//                    //buffer[0] = 0x03; // command not reconized
//                    //uart_1_send_message(0xE0, buffer, 1);
//                    //PutChar(0xA6); // debug
//                    break;
//            }
//        }
//        else
//        {
//            // error checksum
//            //uart_1_send_message(0xE0, buffer, 3);
//            buffer[0] = 0x02;
//            buffer[1] = checksum8_2nd;
//            buffer[2] = SPI_2_data_buffer[SPI_2_data_pointer-2];
//            uart_1_send_message(0xEE, buffer, 3);
//            //uart_1_send_message(0xEE, buffer, 2);
//            //WriteBuffer(buffer, 0xEE, 2); 
//            //SPI_2_send_message(0xE0,buffer,3); 
//        }
//    }
//    else
//    {
//        // error message length l
//        //buffer[0] = 0x00;
//        //uart_1_send_message(0xE1, buffer, 0);
//        //WriteBuffer(buffer, 0xE1, 0);
//        buffer[0] = 0x03;
//        buffer[1] = SPI_2_data_buffer[SPI_2_data_pointer];
//        buffer[2] = SPI_2_data_pointer;
//        buffer[3] = checksum8_2nd;
//        uart_1_send_message(0xEE, buffer, 3);
//        //WriteBuffer(buffer, 0xEF, 3);
//        //SPI_2_send_message(0xEF,buffer,3); 
//        
//    }
//    
//    reset_SPI_2_registers(); 
}


/*******************************************************************************
 * Function: uart_1_send_message
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void SPI_2_send_message(uint8_t command, uint8_t *data, uint16_t data_len)
{
//    /* Format SPI_2 
//     * SOF (1 byte) == 0x0C (Not in checksum)
//     * Source (1 byte) == 0x1A (Board)
//     * Destination (1 byte) == 0x1B (Computer)
//     * Command (1 byte)     
//     * Length (1 byte) == 
//     * Data (length bytes) == 0 to nBytes
//     * Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
//     * EOF ((1 byte) (Not in checksum)     
//     */
//    uint16_t full_length = 8 + data_len; 
//    uint8_t buffer[full_length]; 
//    uint16_t i; 
//    uint16_t pointer = 0; 
//    uint16_t checksum16 = 0;
//    uint8_t checksum8_2nd = 0;
//    
//    buffer[pointer++] = 0x0C;
//    buffer[pointer++] = 0x1A;
//    buffer[pointer++] = 0x1B;
//    buffer[pointer++] = command;
//    buffer[pointer++] = (full_length & 0xFF00) >> 8;
//    buffer[pointer++] = full_length & 0xFF;
//    
//    for(i=0; i<data_len; i++)
//    {
//        buffer[pointer++] = data[i];
//    }
//    
//    for(i=1; i<pointer; i++) // dont count 0x0C
//    {
//        checksum16 += buffer[i];
//    }
//    
//    checksum8_2nd = ~((checksum16 & 0x00FF)) + 1; // get 2nd comp. of 8 bits
//    
//    buffer[pointer++] = checksum8_2nd;
//    
//    buffer[pointer++] = 0x0D;
//    
//    write_string_uart_1(buffer, 8 + data_len); 
////    for(i=0; i<full_length; i++) // dont count 0x0C
////    {
////        SPI_2_Write(buffer[i]);
////    }
//    
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_1_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len)
{
    uint8_t i; 
    //uint8_t byte_read[64]; 
    uint8_t status = 0; 

    //void set_SS_Accel(SPI_CS cs_port);
    set_SS_Accel(cs_port);
    
    for(i=0; i<cmd_len; i++)
    {
        status  = SPI_1_Write(cmd[i]);
        //ret = SPI_2_Write_Test(cmd[i]);
    }
    
    for(i=0; i<data_len; i++)
    {
        buffer[i] = SPI_1_Write(0x0000); // send dummy
    }
    
    while (SPI1STATLbits.SPIBUSY){}; // wait transmitter is ready
    disable_SS_Accel(cs_port); 
    
    //write_string_uart_1(byte_read,data_len);
    //CAN_Encode_Sending(0x1B,0xC4, buffer, data_len);
    
    return status; 
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_2_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len)
{
    uint8_t i; 
    //uint8_t byte_read[64]; 
    uint8_t status = 0; 

    //void set_SS_Accel(SPI_CS cs_port);
    set_SS_Accel(cs_port);
    
    for(i=0; i<cmd_len; i++)
    {
        status  = SPI_2_Write(cmd[i]);
        //ret = SPI_2_Write_Test(cmd[i]);
    }
    
    for(i=0; i<data_len; i++)
    {
        buffer[i] = SPI_2_Write(0x0000); // send dummy
    }
    
    while (SPI2STATLbits.SPIBUSY){}; // wait transmitter is ready
    disable_SS_Accel(cs_port); 
    
    //write_string_uart_1(byte_read,data_len);
    //CAN_Encode_Sending(0x1B,0xC4, buffer, data_len);
    
    return status; 
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t SPI_3_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len)
{
    uint8_t i; 
    //uint8_t byte_read[64]; 
    uint8_t status = 0; 

    //void set_SS_Accel(SPI_CS cs_port);
    set_SS_Accel(cs_port);
    
    for(i=0; i<cmd_len; i++)
    {
        status  = SPI_3_Write(cmd[i]);
        //ret = SPI_2_Write_Test(cmd[i]);
    }
    
    for(i=0; i<data_len; i++)
    {
        buffer[i] = SPI_3_Write(0x0000); // send dummy
    }
    
    while (SPI3STATLbits.SPIBUSY){}; // wait transmitter is ready
    disable_SS_Accel(cs_port); 
    
    //write_string_uart_1(byte_read,data_len);
    //CAN_Encode_Sending(0x1B,0xC4, buffer, data_len);
    
    return status; 
    
}