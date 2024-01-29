/*******************************************************************************
 * 
 * @Company
 *      Pentageer
 * 
 * @Designer
 *      Daniel St-Pierre
 * 
 * @Date
 *      Jan 8 2023
 * 
 * @File Name
 *      Uart.c
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/
#include "Uart.h"
//#include "ADXL373.h"

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_uart_1()
{
    //UxBRG = (Fp / (16 * Baudrate)) - 1
    //int pbClk = SYS_FREQ / 4; // 
    
    U1MODE = 0;                 // Set UART 1 off prior to setting it up
    U1MODEHbits.BCLKSEL = 0;    // FOSC/2 (FP)
    U1MODEbits.MOD = 0;         // Asynchronous 8-bit UART
    U1MODEbits.BRGH = 0;        // Low Speed: Baud rate is baudclk/16
    
    U1MODEHbits.RUNOVF = 1;     // receiver continue receive data overwrite RX shifter.
    
    //U1MODEHbits.BCLKMOD = 1;    // Uses fractional Baud Rate Generation
    
        ////////////////////////////////////////////////////////////////////////////
    U1MODEHbits.BCLKMOD = 0;    // Uses fractional Baud Rate Generation 
    // BGR = (FP / baudrate / 16) - 1
    //9600	10	64.10416667
    //9600	20	129.2083333
    //9600	24	155.25
    //9600	40	259.4166667
    //9600	80	519.8333333
    U1BRG = 64;
    
    // BGR = FP / baudrate
    //U1BRG = 208;                // BGR = 24Mhz / 115200 
    //U1BRG = 347;                // BGR = 40Mhz / 115200 
    //U1BRG = 694;                // BGR = 80Mhz / 115200
    //U1BRG = 1389;                // BGR = 160Mhz / 115200

    //U1STAHbits.URXISEL = 0;     // trigger RX interrupt when 1 byte is in the buffer
    
    IEC0bits.U1RXIE = 1;        // enable Uart 1 RX interupt
    
    U1MODEbits.UARTEN = 1; 
    U1MODEbits.UTXEN = 1; 
    U1MODEbits.URXEN = 1; 
    
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 9600
 ******************************************************************************/
void init_uart_1_DMA(void)
{
    U1MODE = 0;                 // Set UART 1 off prior to setting it up
    U1MODEHbits.BCLKSEL = 0;    // FOSC/2 (FP)
    U1MODEbits.MOD = 0;         // Asynchronous 8-bit UART
    U1MODEbits.BRGH = 0;        // Low Speed: Baud rate is baudclk/16
    U1MODEHbits.RUNOVF = 1;     // receiver continue receive data overwrite RX shifter.
    ////////////////////////////////////////////////////////////////////////////
    U1MODEHbits.BCLKMOD = 0;    // Uses fractional Baud Rate Generation 
    // BGR = (FP / baudrate / 16) - 1
    //9600	10	64.10416667
    //9600	20	129.2083333
    //9600	24	155.25
    //9600	40	259.4166667
    //9600	80	519.8333333
    U1BRG = 64;
    ////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////
    //U1MODEHbits.BCLKMOD = 1;    // Uses fractional Baud Rate Generation
    // BGR = FP / baudrate
    //U1BRG = 208;                // BGR = 24Mhz / 115200 
    //U1BRG = 347;                // BGR = 40Mhz / 115200 
    //U1BRG = 694;                // BGR = 80Mhz / 115200
    //U1BRG = 1389;                // BGR = 160Mhz / 115200
    ////////////////////////////////////////////////////////////////////////////

    U1STA = 0;
    U1STAHbits.URXISEL = 0;     // trigger RX interrupt when 1 byte is in the buffer
    U1MODEbits.UARTEN = 1; 
    U1MODEbits.UTXEN = 1; 
    U1MODEbits.URXEN = 1; 
    
    //IFS0bits.U1RXIF = 0;        // Clear Uart RX interrupt
    //IEC0bits.U1RXIE = 1;        // enable Uart 1 RX interupt
   
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void write_uart_1(uint8_t c)
 {
   while (U1STAHbits.UTXBF); // Wait til current transmission is complete
   U1TXREG = c;
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void write_string_uart_1(uint8_t *str, uint8_t length)
{
    uint8_t i;
    for(i=0; i< length; i++)
    {
        write_uart_1(str[i]); 
    }

}

/*******************************************************************************
 * Function: read_uart_1
 * Parameters: uint8_t  data
 * Return: none
 * Description: Received Uart byte from interrupt
 ******************************************************************************/
void read_uart_1(uint8_t  uart_1_data_byte)
{
    uint8_t buffer[3] = {0x10, 0x11, 0x12};
    uint16_t length = 0; 
    /* Format Uart 1 
     * SOF (1 byte) == 0x0C
     * Source (1 byte) == 0x1B (Computer)
     * Destination (1 byte) == 0x1A (Board) 
     * Command (1 byte)
     * Length (2 byte) == 
     * Data (length bytes) == min 1 byte
     * Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
     * EOF ((1 byte)     
     */
    
    /* Registers Uart 1:
     * volatile uint8_t   Uart_1_data_pointer == indicate how many byte received
     * volatile uint8_t*  Uart_1_data_buffer == array of data 
     */
    
    if(Uart_1_Status.RX_Received == 0)
    {
        if(Uart_1_data_pointer == 0)
        {
            if(uart_1_data_byte == 0x0C) // start of file
            {
                Uart_1_data_buffer[0] = uart_1_data_byte; 
                Uart_1_data_pointer += 1;               // SOF
                Uart_1_Status.RX_Started = 1;//Data_COM_Status |= Data_RX_Started;
                Uart_1_data_timeout_counter = 0;

            }

        }
        else
        {
            Uart_1_data_buffer[Uart_1_data_pointer] = uart_1_data_byte; 
            Uart_1_data_pointer += 1;
            
            if(uart_1_data_byte == 0x0D)
            {
                /*
                * 0 = SOF (1 byte) == 0x0C (Not in checksum)
                * 1 = Source (1 byte) == 0x1A (Board)
                * 2 = Destination (1 byte) == 0x1B (Computer)
                * 3 = Command (1 byte)     
                * 4-5 = Length (2 byte) == 
                 */
                 //Uart_1_Status.RX_Received = 1; // Data_COM_Status |= Data_RX_Received;
                 //Uart_1_Status.RX_Started = 0; //Data_COM_Status &= ~Data_RX_Started;
                 //Uart_1_data_timeout_counter = 0; //Data_COM_Timeout_Counter = 0; 
                 //Uart_1_Status.RX_Timeout = 0; //Data_COM_Flag &= ~Data_COM_Timeout;
                if(Uart_1_data_pointer >= 6) // length
                {
                    length = (Uart_1_data_buffer[4] << 8) + Uart_1_data_buffer[5]; 
                    if(length == Uart_1_data_pointer)
                    {
                        Uart_1_Status.RX_Received = 1; // Data_COM_Status |= Data_RX_Received;
                        Uart_1_Status.RX_Started = 0; //Data_COM_Status &= ~Data_RX_Started;
                        Uart_1_data_timeout_counter = 0; //Data_COM_Timeout_Counter = 0; 
                        Uart_1_Status.RX_Timeout = 0; //Data_COM_Flag &= ~Data_COM_Timeout;
                    }
//                    else
//                    {
//                        write_uart_1(0xEE); //debug
//                        write_uart_1(Uart_1_data_pointer); //debug
//                        write_uart_1(length & 0xFF); //debug
//                    }
                }
                 
            }

            if(Uart_1_data_pointer > 128)
            {
                // error overflow
                reset_uart_1_registers(); 
                uart_1_send_message(0xE2, buffer, 3);
            }
        }
    }
    else
    {
        // error
        // message not processed yet
        //uart_1_send_message(0xE3, buffer, 3);
    }
    
}

/*******************************************************************************
 * Function: reset_uart_1_registers
 * Parameters: none
 * Return: none
 * Description: Reset Uart 1 registers after error or end of com
 ******************************************************************************/
void reset_uart_1_registers(void)
{
    int i;
    
    Uart_1_Status.RX_Received = 0; // Data_COM_Status |= Data_RX_Received;
    Uart_1_Status.RX_Started = 0; //Data_COM_Status &= ~Data_RX_Started;
    Uart_1_data_timeout_counter = 0; //Data_COM_Timeout_Counter = 0; 
    Uart_1_Status.RX_Timeout = 0; //Data_COM_Flag &= ~Data_COM_Timeout;
    Uart_1_data_pointer = 0; 
    for (i=0; i < Uart_1_data_pointer; i++)
    {
        Uart_1_data_Received[i] = 0; 
        Uart_1_data_buffer[i] = 0;
    }
}

/*******************************************************************************
 * Function: decode_uart_1_message
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void decode_uart_1_message(void)
{
    int i;
    uint8_t buffer[20] = {0};
    uint16_t checksum16 = 0;
    unsigned char checksum8_2nd = 0;
    uint16_t crc = 0;
    
    for (i=1; i < Uart_1_data_pointer; i++) // remove SOF
    {
        if((i != 0) && (i<Uart_1_data_pointer-2))
        {
            // remove SOF, checksum and EOF
            checksum16 += Uart_1_data_buffer[i];
        }
    }
    
    //Uart_1_Status.RX_Received = 0; 
    
    /* Format Uart 1 
     * [0] => SOF (1 byte) == 0x0C (Not in checksum)
     * [1] => Source (1 byte) == 0x1B (Computer)
     * [2] => Destination (1 byte) == 0x1A (Board) 
     * [3] => Command (1 byte)     
     * [4] => Length (2 byte) == 
     * [5] => Length
     * [6] => Data (length bytes) ==  to nBytes
     * [length + 6] => Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
     * [length + 7] => EOF ((1 byte) (Not in checksum)     
     */
    
    checksum8_2nd = ~((checksum16 & 0x00FF)) + 1; // get 2nd comp. of 8 bits
    
    if(Uart_1_data_pointer >= 6 && (Uart_1_data_buffer[Uart_1_data_pointer-1] == 0x0D))
    {
        if(checksum8_2nd == Uart_1_data_buffer[Uart_1_data_pointer-2])
        {
            switch(Uart_1_data_buffer[3])
            {
                case 0x01: // Test
                    //uart_1_send_message(0xC1, buffer, 3);
                    //WriteBuffer(buffer, 0x01, 3); 
                    uart_1_send_message(0x02,buffer,0); 
                    break;
                case 0x03: // Test
                    //uart_1_send_message(0xC1, buffer, 3);
                    //WriteBuffer(buffer, 0x01, 3); 
                    //Set_GPIO_USB_3(); 
//                    SPI_2_data_TX[0] = 0x11; 
//                    SPI_2_data_TX[1] = 0x22; 
//                    SPI_2_data_TX[2] = 0x33; 
//                    SPI_2_data_TX[3] = 0x44; 
//                    SPI_2_data_TX[4] = 0x55; 
//                    SPI_2_data_TX[5] = 0x66; 
//                    SPI_2_data_TX[6] = 0x77; 
//                    SPI_2_data_TX[7] = 0x88; 
//                    SPI_2_data_TX_pointer = 0; 
//                    SPI_2_TX_Number_Bytes_To_Send = 0x08; 
//                    Set_GPIO_USB_3(); 
//                    uart_1_send_message(0x04,SPI_2_data_TX,8); 
//                    //SPI2BUFL = SPI_2_data_TX_pointer++; 
//                    SPI2IMSKLbits.SPIRBFEN = 0; // disable RX interrupt
//                    IEC1bits.SPI2RXIE = 0; // Enable RX interrupts
//                    SPI2BUFL = SPI_2_data_TX[SPI_2_data_TX_pointer++];
//                    //SPI2URDTL = SPI_2_data_TX[SPI_2_data_TX_pointer];
//                    while (!SPI2STATLbits.SPITBF){};// 
//                    //asm volatile ("nop");
//                    //asm volatile ("nop");
//                    SPI_2_Status.TX_Send = 1; 
                    break;  
                case 0x05: // Test
                    //uart_1_send_message(0xC1, buffer, 3);
                    //WriteBuffer(buffer, 0x01, 3); 
//                    Clear_GPIO_USB_3(); 
//                    SPI_2_Status.TX_Send = 0; 
//                    uart_1_send_message(0x06,buffer,0); 
                    
                    break;  
                case 0x09: // Test
                    //LEDR = 1; 
                    buffer[0] = 0x01; 
                    buffer[1] = 0x02; 
                    buffer[2] = 0x03; 
                    buffer[3] = 0x04; 
                    buffer[4] = 0x05; 
                    buffer[5] = 0x06; 
                    buffer[6] = 0x07; 
                    buffer[7] = 0x08;
                    buffer[8] = 0x09; 
                    buffer[9] = 0x0A; 
                    buffer[10] = 0x0B; 
                    buffer[11] = 0x0C; 
                    buffer[12] = 0x0D; 
                    buffer[13] = 0x0E; 
                    buffer[14] = 0x0F; 
                    //buffer[15] = 0x10; 
                    crc = CRC_ChecksumByte(buffer, 15, 0x00); 
                    buffer[0] = (crc & 0xFF00) >>8; 
                    buffer[1] = crc & 0xFF; 
                    //LEDR = 0; 
                    uart_1_send_message(0x0A,buffer,2); 
                    break; 
//                case 0xA9: // Enter bootloader
//                    //WriteBuffer(buffer, 0xB9, 0); 
//                    uart_1_send_message(0xB9,buffer,0); 
//                    Uart_1_Status.Boot_Request = 1; 
//                    break;
                    
                case 0xB0: // Write to flash    
                    //uart_1_send_message(0xB3,buffer,0); // received
                    for (i=0; i < 20; i++)
                    {
                        buffer[i] = Uart_1_data_buffer[6+i];
                    }
                    //Fill_Buffer_Flash(buffer, 20);
                    break;
                case 0xBB: // Enter boot - Ready to write   
                    //Uart_1_Status.Boot_Request = 1; 
                    uart_1_send_message(0xBC, buffer, 0);
                    break;
                    ////////////////////////////////////////////////////////////
                default:
                    buffer[0] = 0x03; // command not reconized
                    uart_1_send_message(0xE0, buffer, 1);
                    //PutChar(0xA6); // debug
                    break;
            }
        }
        else
        {
            // error checksum
            //uart_1_send_message(0xE0, buffer, 3);
            buffer[0] = 0x02;
            buffer[1] = checksum8_2nd;
            buffer[2] = Uart_1_data_buffer[Uart_1_data_pointer-2];
            //uart_1_send_message(0xEE, buffer, 2);
            //WriteBuffer(buffer, 0xEE, 2); 
            uart_1_send_message(0xE0,buffer,3); 
        }
    }
    else
    {
        // error message length l
        //buffer[0] = 0x00;
        //uart_1_send_message(0xE1, buffer, 0);
        //WriteBuffer(buffer, 0xE1, 0);
        buffer[0] = Uart_1_data_buffer[Uart_1_data_pointer];
        buffer[1] = Uart_1_data_pointer;
        buffer[2] = checksum8_2nd;
        //WriteBuffer(buffer, 0xEF, 3);
        uart_1_send_message(0xEF,buffer,3); 
        
    }
    
    reset_uart_1_registers(); 
}


/*******************************************************************************
 * Function: uart_1_send_message
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void uart_1_send_message(uint8_t command, uint8_t *data, uint16_t data_len)
{
    /* Format Uart 1 
     * SOF (1 byte) == 0x0C (Not in checksum)
     * Source (1 byte) == 0x1A (Board)
     * Destination (1 byte) == 0x1B (Computer)
     * Command (1 byte)     
     * Length (1 byte) == 
     * Data (length bytes) == 0 to nBytes
     * Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
     * EOF ((1 byte) (Not in checksum)     
     */
    uint16_t full_length = 8 + data_len; 
    uint8_t buffer[full_length]; 
    uint16_t i; 
    uint16_t pointer = 0; 
    uint16_t checksum16 = 0;
    uint8_t checksum8_2nd = 0;
    
    buffer[pointer++] = 0x0C;
    buffer[pointer++] = 0x1A;
    buffer[pointer++] = 0x1B;
    buffer[pointer++] = command;
    buffer[pointer++] = (full_length & 0xFF00) >> 8;
    buffer[pointer++] = full_length & 0xFF;
    
    for(i=0; i<data_len; i++)
    {
        buffer[pointer++] = data[i];
    }
    
    for(i=1; i<pointer; i++) // dont count 0x0C
    {
        checksum16 += buffer[i];
    }
    
    checksum8_2nd = ~((checksum16 & 0x00FF)) + 1; // get 2nd comp. of 8 bits
    
    buffer[pointer++] = checksum8_2nd;
    
    buffer[pointer++] = 0x0D;
    
    write_string_uart_1(buffer, 8 + data_len); 
    
    
}


/*******************************************************************************
 * Function: uart_1_send_message
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void uart_1_send_message_timed(uint8_t command, uint8_t *data, uint8_t data_len)
{
    /* Format Uart 1 
     * SOF (1 byte) == 0x0C (Not in checksum)
     * Source (1 byte) == 0x1A (Board)
     * Destination (1 byte) == 0x1B (Computer)
     * Command (1 byte)     
     * Length (1 byte) == Time + data length
     * Time == 7 bytes
     * Data (length bytes) == 0 to nBytes
     * Checksum (1 byte) == 2nd complement of sum truncated of Src + dst + length + Data
     * EOF ((1 byte) (Not in checksum)     
     */
    
//    uint8_t full_length = 7 + data_len;
//    uint8_t buffer[7 + full_length]; // format msg + time bytes + array input
//    //uint8_t buffer[64]; 
//    uint8_t i; 
//    uint8_t pointer = 0; 
//    uint16_t checksum16 = 0;
//    uint8_t checksum8_2nd = 0;
//    
//    buffer[pointer++] = 0x0C;
//    buffer[pointer++] = 0x1A;
//    buffer[pointer++] = 0x1B;
//    buffer[pointer++] = command;
//    buffer[pointer++] = full_length;
//    
//    buffer[pointer++] = (Time.days & 0xFF00) << 8;
//    buffer[pointer++] = Time.days & 0x00FF;
//    buffer[pointer++] = Time.hours; 
//    buffer[pointer++] = Time.minutes;
//    buffer[pointer++] = Time.seconds;
//    buffer[pointer++] = (Time.miliseconds & 0xFF00) >> 8;
//    buffer[pointer++] = Time.miliseconds & 0x00FF;
//
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
//    write_string_uart_1(buffer, 7 + full_length); 
//    
    
}

/*******************************************************************************
 * Function: GetChar
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t GetChar(void)
{
    uint8_t bytes_status = 0; 
    //UByte8 buffer_full = 1; 
    //UByte8 uart_data = 0; 
		/* if timer expired, signal to application to jump to user code */
//		if(IFS0bits.CCT1IF == 1)
//		{
//			//* ptrChar = COMMAND_NACK;
//			break;
//		}
		/* check for receive errors */
    
    if(U1STAbits.FERR == 1)
    {
        //write_uart_1(0xE2); 
        //continue;
    }

    /* must clear the overrun error to keep uart receiving */
    if(U1STAbits.OERR == 1)
    {
        U1STAbits.OERR = 0;
        //write_uart_1(0xE1);
        //continue;
    }

    /* get the data */
    /////////////////////////////////////////////////
    /* works
    if(!U1STAHbits.URXBE)           
    {                               
        uart_data = U1RXREG;        
        PutChar(uart_data);             
        while(!U1STAHbits.URXBE)
        {
            uart_data = U1RXREG;
            PutChar(uart_data);
        }
    }*/
    ////////////////////////////////////////////////
    if(!U1STAHbits.URXBE)            
    {      
        read_uart_1(U1RXREG);        
        //write_uart_1(0x03);          
        while(!U1STAHbits.URXBE)
        {
            read_uart_1(U1RXREG);
            bytes_status = 1; 
        }
    }
        
    return bytes_status;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_uart_2()
{
    //UxBRG = (Fp / (16 * Baudrate)) - 1
    //int pbClk = SYS_FREQ / 4; // 
    
    U2MODE = 0;                 // Set UART 1 off prior to setting it up
    U2MODEHbits.BCLKSEL = 0;    // FOSC/2 (FP)
    U2MODEbits.MOD = 0;         // Asynchronous 8-bit UART
    U2MODEbits.BRGH = 0;        // Low Speed: Baud rate is baudclk/16
    
    U2MODEHbits.RUNOVF = 1;     // receiver continue receive data overwrite RX shifter.
    
       ////////////////////////////////////////////////////////////////////////////
    U2MODEHbits.BCLKMOD = 0;    // Uses fractional Baud Rate Generation 
    // BGR = (FP / baudrate / 16) - 1
    //9600	10	64.10416667
    //9600	20	129.2083333
    //9600	24	155.25
    //9600	40	259.4166667
    //9600	80	519.8333333
    U2BRG = 64;
    ////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////
    //U1MODEHbits.BCLKMOD = 1;    // Uses fractional Baud Rate Generation
    // BGR = FP / baudrate
    //U2BRG = 208;                // BGR = 24Mhz / 115200 
    //U2BRG = 347;                // BGR = 40Mhz / 115200 
    //U2BRG = 694;                // BGR = 80Mhz / 115200
    //U2BRG = 1389;                // BGR = 160Mhz / 115200
    ////////////////////////////////////////////////////////////////////////////

    //U2STAHbits.URXISEL = 0;     // trigger RX interrupt when 1 byte is in the buffer
    
    IEC1bits.U2RXIE = 1;        // enable Uart 2 RX interupt
    
    U2MODEbits.UARTEN = 1; 
    U2MODEbits.UTXEN = 1; 
    U2MODEbits.URXEN = 1; 
    
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 9600
 ******************************************************************************/
void init_uart_2_DMA()
{
    U2MODE = 0;                 // Set UART 1 off prior to setting it up
    U2MODEHbits.BCLKSEL = 0;    // FOSC/2 (FP)
    U2MODEbits.MOD = 0;         // Asynchronous 8-bit UART
    U2MODEbits.BRGH = 0;        // Low Speed: Baud rate is baudclk/16
    U2MODEHbits.RUNOVF = 1;     // receiver continue receive data overwrite RX shifter.
    ////////////////////////////////////////////////////////////////////////////
    U2MODEHbits.BCLKMOD = 0;    // Uses fractional Baud Rate Generation 
    // BGR = (FP / baudrate / 16) - 1
    //9600	10	64.10416667
    //9600	20	129.2083333
    //9600	24	155.25
    //9600	40	259.4166667
    //9600	80	519.8333333
    U2BRG = 64;
    ////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////
    //U1MODEHbits.BCLKMOD = 1;    // Uses fractional Baud Rate Generation
    // BGR = FP / baudrate
    //U2BRG = 208;                // BGR = 24Mhz / 115200 
    //U2BRG = 347;                // BGR = 40Mhz / 115200 
    //U2BRG = 694;                // BGR = 80Mhz / 115200
    //U2BRG = 1389;                // BGR = 160Mhz / 115200
    ////////////////////////////////////////////////////////////////////////////

    U2STA = 0;
    U2STAHbits.URXISEL = 0;     // trigger RX interrupt when 1 byte is in the buffer
    U2MODEbits.UARTEN = 1; 
    U2MODEbits.UTXEN = 1; 
    U2MODEbits.URXEN = 1; 
    
    //IFS1bits.U2RXIF = 0;        // 
    //IEC1bits.U2RXIE = 1;        // enable Uart 1 RX interupt
   
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void write_uart_2(char c)
 {
   while (U2STAHbits.UTXBF); // Wait til current transmission is complete
   U2TXREG = c;
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void write_string_uart_2(uint8_t *str, uint8_t length)
{
    uint8_t i;
    for(i=0; i< length; i++)
    {
        write_uart_2(str[i]); 
    }

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
uint8_t Dtect_MWD_Msg_Decoding(uint8_t *buffer, uint8_t length)
{
    /* 17 10 10 13 17 04 0C 0D 28 09 32 00 00 D2 17 B3
     * 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
     * [byte 0]  => address
     * [byte 1]  => Length
     * [byte 2]  => Length (copy as byte 1)
     * [byte 3]  => ID message
     * [byte 4]  => Data[0]
     * [byte 5]  => Data[1]
     * [byte 6]  => Data[2]
     * [byte 7]  => Data[3]
     * [byte 8]  => Data[4]
     * [byte 9]  => Data[5]
     * [byte 10] => Data[6]
     * [byte 11] => Data[7]
     * [byte 12] => Data[8]
     * [byte 13] => Data[9]
     * [byte 14] => address (copy as byte 0)
     * [byte 15] => checksum of all byte from 0 to 14
     */
    
    /* Status
     * [bit 0]  => Length not right
     * [bit 1]  => wrong Address
     * [bit 2]  => 
     * [bit 3]  => 
     * [bit 4]  => 
     * [bit 5]  => 
     * [bit 6]  => 
     * [bit 7]  => wrong Checksum 
     */
    
    uint8_t status = 0x00; 
    uint8_t i;
    uint16_t  checksum16 = 0;
    uint8_t checksum8 = 0;
    // check length
    if((length != 16) || (buffer[1] != 0x10) || (buffer[2] != 0x10))
    {
        status = 0x01;
        return status; 
    }
    
    if((buffer[0] != 0x17) || ((buffer[15] != 0x17)))
    {
        status = 0x02;
        return status; 
    }
    

    for (i = 0; i < 16; i++) // All bytes
    {
        checksum16 += buffer[i];
    }
    
    checksum8 = checksum16 & 0xFF; 
    
    if(checksum8 != buffer[15])
    {
        status = 0x80;
        return status;
    }
    
    
    
    return status; 
    
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void init_uart_3()
{
    //UxBRG = (Fp / (16 * Baudrate)) - 1
    //int pbClk = SYS_FREQ / 4; // 
    
    U3MODE = 0;                 // Set UART 1 off prior to setting it up
    U3MODEHbits.BCLKSEL = 0;    // FOSC/2 (FP)
    U3MODEbits.MOD = 0;         // Asynchronous 8-bit UART
    U3MODEbits.BRGH = 0;        // Low Speed: Baud rate is baudclk/16
    
    U3MODEHbits.RUNOVF = 1;     // receiver continue receive data overwrite RX shifter.
    
    ////////////////////////////////////////////////////////////////////////////
    U3MODEHbits.BCLKMOD = 1;    // Uses fractional Baud Rate Generation 
    // BGR = (FP / baudrate / 16) - 1
    //9600	10	64.10416667
    //9600	20	129.2083333
    //9600	24	155.25
    //9600	40	259.4166667
    //9600	80	519.8333333
    //U3BRG = 64;
    
    U1BRG = 313;                // BGR = 80Mhz / 256000
    ////////////////////////////////////////////////////////////////////////////

    //U2STAHbits.URXISEL = 0;     // trigger RX interrupt when 1 byte is in the buffer
    
    //IEC1bits.U2RXIE = 1;        // enable Uart 2 RX interupt
    
    U3MODEbits.UARTEN = 1; 
    U3MODEbits.UTXEN = 1; 
    U3MODEbits.URXEN = 1; 
    
    
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void write_uart_3(char c)
 {
   while (U3STAHbits.UTXBF); // Wait til current transmission is complete
   U3TXREG = c;
}
/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void write_string_uart_3(uint8_t *str, uint8_t length)
{
    uint8_t i;
    for(i=0; i< length; i++)
    {
        write_uart_3(str[i]); 
    }

}