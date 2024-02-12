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
 *      CAN.c
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/

#include "CAN.h"
//#include "variable.h"
//#include "variable.h" 

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: CAN 1 setup
 ******************************************************************************/
void init_CAN_1(void)
{
 
    C1CONHbits.REQOP = 4;
    while(C1CONHbits.OPMOD != 4);
    
    // setup CAN clock
    /* Set up the CAN clock generator for 40 MIPS and enable the CAN clock generator. */
    C1CONLbits.CLKSEL = 0x0; //Set clock source the CAN clock generator 
    
     // 10 mips (FOSC 20Mhz)
    CANCLKCONbits.CANCLKSEL = 0x2; // Set FPLLO for Clock Source Select bits
    CANCLKCONbits.CANCLKDIV = 0;
    CANCLKCONbits.CANCLKEN = 1; 
    
    // 20 mips (FOSC 40Mhz)
//    CANCLKCONbits.CANCLKSEL = 0x2; // Set FPLLO for Clock Source Select bits
//    CANCLKCONbits.CANCLKDIV = 1;
//    CANCLKCONbits.CANCLKEN = 1; 
    
     // 40 mips (FOSC 80Mhz)
//    CANCLKCONbits.CANCLKSEL = 0x02; // Set FPLLO for Clock Source Select bits
//    CANCLKCONbits.CANCLKDIV = 0x7;
//    CANCLKCONbits.CANCLKEN = 1; 
    
    //propagSeg = 1
    
    // s1Seg = 4
    // s2Seg = 2
    
    /* Enable the CANFD module */
    C1CONLbits.CON = 1;
    
    /* Initialize the C1FIFOBA with the start address of the CAN FIFO message buffer area. */
    //C1FIFOBAL = (unsigned int) &CanTxBuffer;
    C1FIFOBAH = 0x0000;
    C1FIFOBAL = (unsigned int) &CanTxBuffer; // TX
    //C1FIFOBAL = (unsigned int) &CanRxBuffer; // TX
    
    /* Set up the CANFD module for 1Mbps of Nominal bit rate speed and 2Mbps of Data bit rate. */

       // 10 mips (FOSC 20Mhz)- 1Mbps & 4Mbps
    C1NBTCFGH = 0x000E; // 1Mbps of nominal
    C1NBTCFGL = 0x0303;
    C1DBTCFGH = 0x0002; // 4Mbps of of Data bit rate
    C1DBTCFGL = 0x0000;
    C1TDCH = 0x0002;    //TDCMOD is Auto
    C1TDCL = 0x0300;
    
    
      // 20 mips - 1Mbps & 4Mbps
//    C1NBTCFGH = 0x000E; // 1Mbps of nominal
//    C1NBTCFGL = 0x0303;
//    C1DBTCFGH = 0x0002; // 4Mbps of of Data bit rate
//    C1DBTCFGL = 0x0000;
//    C1TDCH = 0x0002;    //TDCMOD is Auto
//    C1TDCL = 0x0300;
    
//    // 40 mips - 1Mbps & 2Mbps
//    C1NBTCFGH = 0x001E; // 1Mbps of nominal
//    C1NBTCFGL = 0x0707;
//    C1DBTCFGH = 0x000E; // 2Mbps of of Data bit rate
//    C1DBTCFGL = 0x0303;
//    C1TDCH = 0x0002;    //TDCMOD is Auto
//    C1TDCL = 0x0F00;

    // 40 mips - 1Mbps & 4Mbps 
//    C1NBTCFGH = 0x000E; // 1Mbps of nominal
//    C1NBTCFGL = 0x0303;
//    C1DBTCFGH = 0x0002;   // 4Mbps of Data bit rate
//    C1DBTCFGL = 0x0000;
//    C1TDCH = 0x0002;    //TDCMOD is Auto
//    C1TDCL = 0x0300;
    
//    // 40 mips - 1Mbps & 5Mbps 
//    C1NBTCFGH = 0x000E; // 1Mbps of nominal
//    C1NBTCFGL = 0x0303;
//    C1DBTCFGH = 0x0000;   // 5Mbps of Data bit rate
//    C1DBTCFGL = 0x0101;
//    C1TDCH = 0x0002;    //TDCMOD is Auto
//    C1TDCL = 0x0100;
    
//    // 80 mips
//    C1NBTCFGH = 0x001E;     // 1Mbps of nominal
//    C1NBTCFGL = 0x0707;
//    C1DBTCFGH = 0x0002;     // 5Mbps of Data bit rate
//    C1DBTCFGL = 0x0303;
//    C1TDCH = 0x0002;        //TDCMOD is Auto
//    C1TDCL = 0x0300;
    
    //////////////////////////////////////////////////////////
    
    // Configure 
    C1CONLbits.ISOCRCEN = 0x1; // Includes stuff bit count in CRC field and uses non-zero CRC initialization vector
    
    C1CONLbits.BRSDIS = 0x0;
    C1CONHbits.STEF = 0x0;   // Don't save transmitted messages in TEF
    C1CONHbits.TXQEN = 0x0;  // No TXQ
    C1CONHbits.RTXAT = 0x1; // Restricted retransmission attempts, uses TXAT[1:0] bits (C1TXQCONH[6:5])
    
    // FIFO1 as transmiter (2 messages)
    C1FIFOCON1Hbits.FSIZE = 2;  // 1 messages deep
    //C1FIFOCON1Hbits.PLSIZE = 0x0;    // 8 bytes of data
    C1FIFOCON1Hbits.PLSIZE = 0x7;    // 64 bytes of data
    C1FIFOCON1Lbits.TXEN = 1;        // Set TXEN bit, transmit fifo
    C1TXQCONHbits.TXAT = 0x0; //DSP Disable retransmission attempts
    
    // FIFO2 as receiver (2 messages)
    C1FIFOCON2Hbits.FSIZE = 2;      // 1 messages deep
    //C1FIFOCON2Hbits.PLSIZE = 0x0;    // 8 bytes of data
    C1FIFOCON2Hbits.PLSIZE = 0x7;    // 64 bytes of data
    C1FIFOCON2Lbits.TXEN = 0;        // Clear TXEN bit, receive fifo
    // filter 0
    C1FLTCON0Lbits.F0BP = 2;    // Store messages in FIFO2
    C1FLTOBJ0H = 0x0100;        // Filter 0 ID
    C1FLTOBJ0L = 0x0000;        // Filter 0 ID
    C1FLTOBJ0Hbits.EXIDE = 0;   // Filter only EID messages
    C1FLTCON0Lbits.FLTEN0 = 1;  // Enable the filter
    // mask 0
    C1MASK0H = 0x0000;      // Ignore all bits in comparison
    C1MASK0L = 0x0000;      // Ignore all bits in comparison
    C1MASK0Hbits.MIDE = 0;  // Match all message types
    
 /////////////////////////////////////////////////////////////
 // Interrupts
    C1FIFOCON2Lbits.TFNRFNIE = 1; // Receive FIFO Not Empty Interrupt Enable
    //C1RXOVIFLbits.RFOVIF2 = 1; 
    C1INTHbits.RXIE = 1;          // Receive Object Interrupt Enable bit
    IEC1bits.C1RXIE = 1; 
/////////////////////////////////////////////////////////////////    
    /* Place the CAN module in Normal mode. */
    C1CONHbits.REQOP = 0;
    while(C1CONHbits.OPMOD != 0)
    {
        C1CONHbits.REQOP = 0;
        //write_uart_1(C1CONH >> 8);
        //write_uart_1(C1CONH & 0xFF);
    } 
    
//    /* Place the CAN module in listen only mode. */
//    C1CONHbits.REQOP = 3;
//    while(C1CONHbits.OPMOD != 3)
//    {
//        C1CONHbits.REQOP = 3;
//        //write_uart_1(C1CONH >> 8);
//        //write_uart_1(C1CONH & 0xFF);
//    }     
    
//     /* Place the CAN module in Restricted mode. */
//    C1CONHbits.REQOP = 7;
//    while(C1CONHbits.OPMOD != 7)
//    {
//        C1CONHbits.REQOP = 7;
//        //write_uart_1(C1CONH >> 8);
//        //write_uart_1(C1CONH & 0xFF);
//    }      
    
    /* Place the CAN module in External Loopback mode. */
//    C1CONHbits.REQOP = 5;
//    while(C1CONHbits.OPMOD != 5)
//    {
//        C1CONHbits.REQOP = 5;
//        //write_uart_1(C1CONH >> 8);
//        //write_uart_1(C1CONH & 0xFF);
//    }  

}


/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void CAN_Send_MSG(uint8_t destination, uint8_t *data, uint8_t length)
{
    unsigned char index;

    /* Transmit message 0 from FIFO 1 - CANFD base frame with BRS*/
    CANFD_TX_MSGOBJ *txObj;
    /* SID = 0x300 , 64 bytes of data */
    txObj = (CANFD_TX_MSGOBJ *)C1FIFOUA1L;
    txObj->bF.id.SID = 0x100;
    //txObj->bF.id.SID = destination;
    //txObj->bF.id.EID = 0x00000000000000000;
    txObj->bF.id.EID =   0x4567;
    txObj->bF.ctrl.BRS = 1; //Switch bit rate
    
    switch (length)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            txObj->bF.ctrl.DLC = 0x8;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            txObj->bF.ctrl.DLC = 0x9;
            break;
        case 13:
        case 14:
        case 15:
        case 16:
            txObj->bF.ctrl.DLC = 0xA;
            break;
        case 17:
        case 18:
        case 19:
        case 20:
            txObj->bF.ctrl.DLC = 0xB;
            break;
        case 21:
        case 22:
        case 23:
        case 24:
            txObj->bF.ctrl.DLC = 0xC;
            break;
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            txObj->bF.ctrl.DLC = 0xD;
            break;
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
            txObj->bF.ctrl.DLC = 0xE;
            break;
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
            txObj->bF.ctrl.DLC = 0xF;
            break;
        default:
            txObj->bF.ctrl.DLC = 0xF;
            break;
    }
    //txObj->bF.ctrl.DLC = 0xF; //64 bytes
    //txObj->bF.ctrl.DLC = 0xA; //16 bytes
    //txObj->bF.ctrl.DLC = 0x8; //8 bytes
    txObj->bF.ctrl.FDF = 1; // CAN or CANFD frame
    txObj->bF.ctrl.IDE = 0; //Standard frame or extended
    //txObj->bF.ctrl.SEQ = 64;
    //txObj->word[0] = 0; 
    //txObj->word[1] = 0; 
    //txObj->word[2] = 0; 
    //txObj->word[3] = 0; 
    //txObj->bF.ctrl.RTR = 0; //request response
    //txObj->bF.ctrl.SEQ = 23; 
    
    for (index=0;index<length;index++ )
    {
        //txObj->byte[index+8] = 0xA5 ; // 16 bytes of 0xA5
        txObj->byte[index+8] = data[index];
    }
    
    C1FIFOCON1Lbits.UINC = 1; // Set UINC bit
    C1FIFOCON1Lbits.TXREQ = 1; // Set TXREQ bit

    while(C1FIFOCON1Lbits.TXREQ == 1)
    {
        if(CAN_Enable == 0)
        {
            break; 
        }
    }
    //while(C1FIFOCON1Lbits.TXREQ == 1); // wait until message send
    //write_uart_1(0xD2);
}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void CAN_Received_To_Uart(void)
{

   char rdata[64];
   int r = can_rec(rdata);
   int i = 0; 
   if (r == 1)
   {
        //write_uart_1(0xDD);
        for(i=0; i<64;i++)
        {
            write_uart_1(rdata[i]);
        }
   }
   else
   {
       write_uart_1(0xEE);
   }

    
    

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
int can_rec(char *data)
{
    //UDK_UNUSED(fifo);


    int i;
    uint16_t errorCAN = 0; 
    
    //CAN_FLAGS flagValue = 0;
    CAN_RxMsgBuffer *buffer = NULL;

    if (C1FIFOSTA2bits.TFNRFNIF == 0)  // fifo empty
    {
        return 0;
    }
    buffer = (CAN_RxMsgBuffer *)C1FIFOUA2L;

    // ID
    uint32_t canId;
    if (CAN_DSPIC33C_RX_IDE(buffer))
    {
        //flagValue += CAN_VERS2BA;  // extended ID
        canId = (((uint32_t)CAN_DSPIC33C_RX_SID(buffer)) << 18) + CAN_DSPIC33C_RX_EIDH(buffer) + CAN_DSPIC33C_RX_EIDL(buffer);
    }
    else
    {
        canId = CAN_DSPIC33C_RX_SID(buffer);
    }
    //header->id = canId;

    // data read and copy
    uint8_t size = CAN_DSPIC33C_RX_DLC(buffer);
    if (CAN_DSPIC33C_RX_FDF(buffer))
    {
        //flagValue += CAN_FDF;  // CAN Fd
        switch (size)
        {
            case 9:
                size = 12;
                break;

            case 10:
                size = 16;
                break;

            case 11:
                size = 20;
                break;

            case 12:
                size = 24;
                break;

            case 13:
                size = 32;
                break;

            case 14:
                size = 48;
                break;

            case 15:
                size = 64;
                break;
        }
    }
    else
    {
        if (size > 8)
        {
            size = 8;
        }
    }
    
    errorCAN = C1BDIAG1H; 
    //write_uart_1(size);
    write_uart_1((errorCAN & 0xFF00) >> 8);
    write_uart_1(errorCAN & 0xFF);
    
    //write_uart_1(buffer);
    
    char *bufferData = (char *)buffer + 8;
    for (i = 0; i < 64; i++)
    {
        data[i] = bufferData[i];
    }
    
//    int *bufferData = (int *)buffer + 8;
//    for (i = 0; i < 8; i+=2)
//    {
//        data[i] = bufferData[i] >> 8;
//        data[i+1] = bufferData[i] & 0xFF;
//    }
    
    
    //header->size = size;

    C1FIFOCON2Lbits.UINC = 1;  // mark as read
    C1FIFOCON2Lbits.FRESET = 1; // Reset the Fifo

    // flags
//    if (CAN_DSPIC33C_RX_RTR(buffer))
//    {
//        flagValue += CAN_RTR;
//    }
//
//    header->flags = flagValue;

    return 1;

}

/*******************************************************************************
 * Function: 
 * Parameters: none
 * Return: none
 * Description: 
 ******************************************************************************/
void CAN_Decode_Received(void)
{
    int i;
    uint16_t errorCAN = 0; 
    uint8_t data[64];
    uint8_t buf_tempo[64];
    uint8_t Mem_test[20];
    uint16_t address_event=0;
    uint8_t pointer; 
    /////////////////////////////////////////////
    // debug ADC gyro
    uint16_t tempo16;
    uint8_t tempo8;
    uint16_t gyro_raw_value_Unsigned; 
    uint16_t gyro_Vol_Ref_Unsigned; 
    int16_t gyro_value=0; 
    /////////////////////////////////////////////
    // debug magnetometer
    //uint32_t tempo_Mag;
    /////////////////////////////////////////////
    //uint32_t addr = 0x0; 
    
    //CAN_FLAGS flagValue = 0;
    CAN_RxMsgBuffer *buffer = NULL;

    if (C1FIFOSTA2bits.TFNRFNIF == 0)  // fifo empty
    {
        return;
    }
    buffer = (CAN_RxMsgBuffer *)C1FIFOUA2L;

    // ID
    uint32_t canId;
    if (CAN_DSPIC33C_RX_IDE(buffer))
    {
        //flagValue += CAN_VERS2BA;  // extended ID
        canId = (((uint32_t)CAN_DSPIC33C_RX_SID(buffer)) << 18) + CAN_DSPIC33C_RX_EIDH(buffer) + CAN_DSPIC33C_RX_EIDL(buffer);
    }
    else
    {
        canId = CAN_DSPIC33C_RX_SID(buffer);
    }
    //header->id = canId;

    // data read and copy
    uint8_t size = CAN_DSPIC33C_RX_DLC(buffer);
    if (CAN_DSPIC33C_RX_FDF(buffer))
    {
        //flagValue += CAN_FDF;  // CAN Fd
        switch (size)
        {
            case 9:
                size = 12;
                break;

            case 10:
                size = 16;
                break;

            case 11:
                size = 20;
                break;

            case 12:
                size = 24;
                break;

            case 13:
                size = 32;
                break;

            case 14:
                size = 48;
                break;

            case 15:
                size = 64;
                break;
        }
    }
    else
    {
        if (size > 8)
        {
            size = 8;
        }
    }
    
    errorCAN = C1BDIAG1H; 
    //write_uart_1(size);
    //write_uart_1((errorCAN & 0xFF00) >> 8);
    //write_uart_1(errorCAN & 0xFF);
    
    //write_uart_1(buffer);
    
    char *bufferData = (char *)buffer + 8;
    for (i = 0; i < size; i++)
    {
        data[i] = bufferData[i];
    }
    
//    int *bufferData = (int *)buffer + 8;
//    for (i = 0; i < 8; i+=2)
//    {
//        data[i] = bufferData[i] >> 8;
//        data[i+1] = bufferData[i] & 0xFF;
//    }
    
    
    //header->size = size;

    C1FIFOCON2Lbits.UINC = 1;  // mark as read
    C1FIFOCON2Lbits.FRESET = 1; // Reset the Fifo

    // flags
//    if (CAN_DSPIC33C_RX_RTR(buffer))
//    {
//        flagValue += CAN_RTR;
//    }
//
//    header->flags = flagValue;
    if(data[3] == 0xC3 || data[3] == 0xC4) // pass through
    {
        
        switch(data[6])
        {
            case 0x01:
                
                // 0C 1A 1B C4 00 0C 01 A0 B0 C0 EA 0d
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x02;
                buf_tempo[1] = 0xA2;
                buf_tempo[2] = 0xA3;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                break;
            ////////////////////////////////////////////////////////////////////  
            case 0x03:
                // 0C 1A 1B C4 00 0C 03 00 00 00 F8 0d
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //State_Flags.Drill_Init_State = 1; 
                if((State_Flags.Mem_Data_Pointer_Seek == 0) &&
                   (State_Flags.Mem_Event_Pointer_Seek == 0))
                {
                    State_Machine_Reset();
                    State_Flags.Drill_250Hz_State = 1;
                    Init_Drill_State(); 
                    buf_tempo[0] = 0x04;
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                }
                else
                {
                    buf_tempo[0] = 0x04; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                
                break; 
            case 0x05:
                // 0C 1A 1B C4 00 0C 05 00 00 00 F6 0d
                // 00 01 02 03 04 05 06 07 08 09 10 11
                State_Flags.Drill_Init_State = 0; 
                buf_tempo[0] = 0x06;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            ////////////////////////////////////////////////////////////////////  
            case 0x07:
                // 0C 1A 1B C4 00 0C 07 00 00 00 F4 0d
                // 00 01 02 03 04 05 06 07 08 09 10 11
                if((State_Flags.Mem_Data_Pointer_Seek == 0) &&
                   (State_Flags.Mem_Event_Pointer_Seek == 0))
                {
                    State_Machine_Reset();
                    State_Flags.Drill_State = 1; 
                    buf_tempo[0] = 0x08;
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                }
                else
                {
                    buf_tempo[0] = 0x08; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                
                break; 
            case 0x08:
                // 0C 1A 1B C4 00 0C 08 00 00 00 F3 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //State_Flags.Drill_State = 0; 
                State_Machine_Reset();
                State_Flags.Idle_State = 1; 
                buf_tempo[0] = 0x09;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            ////////////////////////////////////////////////////////////////////  
            case 0x0A:
                // Init drill 125Hz
                // 0C 1B 1A C4 00 0C 0A 00 00 00 F1 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                State_Flags.Drill_125Hz_State = 1; 
                //buf_tempo[0] = 0x0B;
                //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                //State_Flags.Drill_Init_State = 1; 
                if(State_Flags.Mem_Data_Pointer_Seek == 0)
                {
                    State_Machine_Reset();
                    State_Flags.Drill_125Hz_State = 1;
                    Init_Drill_State(); 
                    buf_tempo[0] = 0x0B;
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                }
                else
                {
                    buf_tempo[0] = 0x0B; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                break; 
            case 0x0C:
                State_Flags.Drill_125Hz_State = 0; 
                buf_tempo[0] = 0x0D; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            ////////////////////////////////////////////////////////////////////  
            case 0x0E:
                State_Flags.Drill_250Hz_State = 1; 
                buf_tempo[0] = 0x0F;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            case 0x10:
                // 0C 1A 1B C4 00 0C 10 00 00 00 EB 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                State_Flags.Drill_250Hz_State = 0; 
                buf_tempo[0] = 0x11; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break;    
            ////////////////////////////////////////////////////////////////////    
            case 0x12:
                // Burst Trigger
                // 0C 1B 1A C4 00 0C 12 00 00 00 E9 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                State_Flags.Burst_State = 1; 
                buf_tempo[0] = 0x13;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            case 0x14:
                State_Flags.Burst_State = 0; 
                buf_tempo[0] = 0x14; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            ////////////////////////////////////////////////////////////////////    
//            case 0x16:// CAN will not work if Uart_COM_only
//                State_Flags.CAN_COM = 1; 
//                buf_tempo[0] = 0x17;
//                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
//                break; 
            case 0x18: // CAN will stop working
                State_Flags.CAN_COM = 0; 
                buf_tempo[0] = 0x19; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            ////////////////////////////////////////////////////////////////////    
            case 0x1A:
                State_Flags.Uart_COM_only = 1; 
                buf_tempo[0] = 0x1B;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
//            case 0x1C: CAN wont work in that mode
//                State_Flags.Uart_COM_only = 0; 
//                buf_tempo[0] = 0x1D; 
//                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
//                break; 
            ////////////////////////////////////////////////////////////////////    
            case 0x1E:
                State_Flags.Idle_State = 1; 
                buf_tempo[0] = 0x1F;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            case 0x20:
                State_Flags.Idle_State = 0; 
                buf_tempo[0] = 0x21; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            //////////////////////////////////////////////////////////////////// 
            case 0x21:
                // 0C 1A 1B C4 00 0C 21 00 00 00 DA 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                Debug_Flags.Test_Data_Out = 1; 
                buf_tempo[0] = 0x22;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                Init_Drill_State(); 
                //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            //////////////////////////////////////////////////////////////////// 
            case 0x23:
                // 0C 1A 1B C4 00 0C 23 00 00 00 D8 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                Debug_Flags.Read_Burst_Out = 1; 
                buf_tempo[0] = 0x24; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                //Init_Drill_State(); 
                State_Flags.Drill_250Hz_State = 0; 
                State_Flags.Drill_State = 0; 
                break; 
            //////////////////////////////////////////////////////////////////// 
            case 0x25:
                // 0C 1A 1B C4 00 0C 25 00 00 00 D6 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                ADXL373_SPI_Start_Sensor(); 
                buf_tempo[0] = 0x26; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break; 
            //////////////////////////////////////////////////////////////////// 
            case 0x27:
                // 0C 1A 1B C4 00 0C 27 00 00 00 D4 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x28; 
                if(Debug_Flags.Accel_HG_Spit_Out == 1)
                {
                    Debug_Flags.Accel_HG_Spit_Out = 0; 
                    buf_tempo[1] = 0x00; 
                }
                else
                {
                    Debug_Flags.Accel_HG_Spit_Out = 1;
                    buf_tempo[1] = 0x01;
                }
                
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            //////////////////////////////////////////////////////////////////// 
            case 0x29:
                // 0C 1A 1B C4 00 0C 29 00 00 00 D2 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                MEM_MT25QL01_Enter_4_Bytes_Mode(2); // Enter 4 byte mode
                buf_tempo[0] = 0x2A; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
     
                break; 
            //////////////////////////////////////////////////////////////////// 
            case 0x2B:
                // 0C 1A 1B C4 00 0C 2B 00 00 00 D0 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                
                buf_tempo[0] = 0x2C; 
                //buf_tempo[1] = MEM_MT25QL01_Get_Status(2);
                buf_tempo[1] = MEM_MT25QL01_Get_Flag(2); 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
     
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x2D:
                // 0C 1A 1B C4 00 0C 2D 00 00 00 CE 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                MEM_MT25QL01_Read_ID(2, Mem_test);
                //buf_tempo[0] = 0x2E; 
                //buf_tempo[1] = MEM_MT25QL01_Get_Status(2);
                CAN_Encode_Sending(0x1B,0xC4, Mem_test, 20);
     
                break; 
                
            case 0x2E:
                // 00 01 02 03 04 05 06 07 08 09 10 11
//                 0C 1A 1B C4 00 0C 2E 01 00 00 CC 0D
//                 0C 1A 1B C4 00 0C 2E 02 00 00 CB 0D
//                 0C 1A 1B C4 00 0C 2E 03 00 00 CA 0D
//                 0C 1A 1B C4 00 0C 2E 04 00 00 C9 0D
//                 0C 1A 1B C4 00 0C 2E 05 00 00 C8 0D
//                 0C 1A 1B C4 00 0C 2E 06 00 00 C7 0D
//                 0C 1A 1B C4 00 0C 2E 07 00 00 C6 0D
//                 0C 1A 1B C4 00 0C 2E 08 00 00 C5 0D
//                 0C 1A 1B C4 00 0C 2E 09 00 00 C4 0D
//                 0C 1A 1B C4 00 0C 2E 0A 00 00 C3 0D
//                 0C 1A 1B C4 00 0C 2E 0B 00 00 C2 0D
//                 0C 1A 1B C4 00 0C 2E 0C 00 00 C1 0D
//                 0C 1A 1B C4 00 0C 2E 0D 00 00 C0 0D
//                 0C 1A 1B C4 00 0C 2E 0E 00 00 BF 0D
//                 0C 1A 1B C4 00 0C 2E 0F 00 00 BE 0D
//                 0C 1A 1B C4 00 0C 2E 10 00 00 BD 0D
//                 0C 1A 1B C4 00 0C 2E 11 00 00 BC 0D
//                 0C 1A 1B C4 00 0C 2E 12 00 00 BB 0D
//                 0C 1A 1B C4 00 0C 2E 13 00 00 BA 0D
//                 0C 1A 1B C4 00 0C 2E 14 00 00 B9 0D
                MEM_MT25QL01_Read_ID(data[7], Mem_test);
                //buf_tempo[0] = 0x2E; 
                //buf_tempo[1] = MEM_MT25QL01_Get_Status(2);
                CAN_Encode_Sending(0x1B,0xC4, Mem_test, 3);
     
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x2F:
                // 0C 1A 1B C4 00 0C 2F 00 00 00 CC 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                Mem_test[0] = MEM_MT25QL01_Read_Freeze_Bit(2); 
                //buf_tempo[0] = 0x2E; 
                //buf_tempo[1] = MEM_MT25QL01_Get_Status(2);
                CAN_Encode_Sending(0x1B,0xC4, Mem_test, 1);
     
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x30:
                // 0C 1A 1B C4 00 0C 30 00 00 00 CB 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                if(MT25QL01_Flag.Mem_Read == 0)
                {
                    MEM_MT25QL01_Init_Read(); 
                }
                
//                buf_tempo[0] = 0x30; 
//                buf_tempo[1] = 0x30; 
//                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);

                MEM_MT25QL01_Read_Bytes(MT25QL01_Read_In_Used, buf_tempo, 64);
                
                CAN_Send_MSG(0xAA, buf_tempo, 64);
                //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x31:
                // 0C 1A 1B C4 00 0C 31 00 00 00 CA 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                
                MEM_MT25QL01_End_Read();
                buf_tempo[0] = 0x32; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
               
                break; 
            ////////////////////////////////////////////////////////////////////    
            case 0x33:
                // 0C 1A 1B C4 00 0C 33 00 00 00 C8 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                if(State_Flags.Drill_State == 0 && MT25QL01_Flag.Mem_Read == 0 
                        && MT25QL01_Flag.Mem_Write == 0)
                {
                    MT25QL01_Flag.Mem_Erase_Request = 1; // timeout 5sec
                    buf_tempo[0] = 0x34; 
                    buf_tempo[1] = 0xAC; // ok
                    buf_tempo[2] = 0xED; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                else
                {
                    MT25QL01_Flag.Mem_Erase_Request = 0; // timeout 5sec
                    buf_tempo[0] = 0x34; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                break; 
            ////////////////////////////////////////////////////////////////////      
            case 0x35:
                // 0C 1A 1B C4 00 0C 35 00 00 00 C6 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                if(MT25QL01_Flag.Mem_Erase_Request == 1)
                {
                    MT25QL01_Flag.Mem_Erase_Pass = 1; 
                    MEM_MT25QL01_Erase_Memory_Init(); 
                    buf_tempo[0] = 0x36; 
                    buf_tempo[1] = 0xAC; // ok
                    buf_tempo[2] = 0xED; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);

                }
                else
                {
                    buf_tempo[0] = 0x36; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                break; 
                
            ////////////////////////////////////////////////////////////////////
            case 0x37:
                // 0C 1A 1B C4 00 0C 37 01 00 00 C3 0D
                // 0C 1A 1B C4 00 0C 37 02 00 00 C2 0D
                // 0C 1A 1B C4 00 0C 37 03 00 00 C1 0D
                // 0C 1A 1B C4 00 0C 37 04 00 00 C0 0D
                // 0C 1A 1B C4 00 0C 37 05 00 00 BF 0D
                // 0C 1A 1B C4 00 0C 37 06 00 00 BE 0D
                // 0C 1A 1B C4 00 0C 37 07 00 00 BD 0D
                // 0C 1A 1B C4 00 0C 37 08 00 00 BC 0D
                // 0C 1A 1B C4 00 0C 37 09 00 00 BB 0D
                // 0C 1A 1B C4 00 0C 37 0A 00 00 BA 0D
                // 0C 1A 1B C4 00 0C 37 0B 00 00 B9 0D
                // 0C 1A 1B C4 00 0C 37 0C 00 00 B8 0D
                // 0C 1A 1B C4 00 0C 37 0D 00 00 B7 0D
                // 0C 1A 1B C4 00 0C 37 0E 00 00 B6 0D
                // 0C 1A 1B C4 00 0C 37 0F 00 00 B5 0D
                // 0C 1A 1B C4 00 0C 37 10 00 00 B4 0D
                // 0C 1A 1B C4 00 0C 37 11 00 00 B3 0D
                // 0C 1A 1B C4 00 0C 37 12 00 00 B2 0D
                // 0C 1A 1B C4 00 0C 37 13 00 00 B1 0D
                if(MT25QL01_Flag.Mem_Erase_Pass == 1 && MT25QL01_Flag.Mem_Erase == 0)
                {
                    if(data[7] > 0 && data[7] <= 20)
                    {
                        MT25QL01_To_Erase = data[7]; 
                        MT25QL01_Flag.Mem_Erase_Request = 0; 
                        MT25QL01_Flag.Mem_Erase_Pass = 0; 
                        MT25QL01_Flag.Mem_Erase = 1; 
//                        buf_tempo[0] = 0x38; 
//                        buf_tempo[1] = 0x4F; // O
//                        buf_tempo[2] = 0x4B; // K
//                        buf_tempo[3] = MT25QL01_To_Erase; // K
//                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                        
                        
                    }
                    else
                    {
                        buf_tempo[0] = 0x38; 
                        buf_tempo[1] = 0xDE; // 
                        buf_tempo[2] = 0xAD; // 
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                    }
                    
               
//                    // DONE == 44 4F 4E 45
//                    buf_tempo[0] = 0x38; 
//                    buf_tempo[1] = 0x44; // D
//                    buf_tempo[2] = 0x4F; // O
//                    buf_tempo[3] = 0x4E; // N
//                    buf_tempo[4] = 0x45; // E
//                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 5);
                }
                else
                {
                    buf_tempo[0] = 0x38; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x39:    
                // 0C 1A 1B C4 00 0C 39 00 00 00 C2 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                if(MT25QL01_Flag.Mem_Erase == 1)
                {
                    MT25QL01_Flag.Mem_Erase = 0; 
                }
                buf_tempo[0] = 0x3A; 
                buf_tempo[1] = 0xAC; // ok
                buf_tempo[2] = 0xED; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                break;
            ////////////////////////////////////////////////////////////////////
            case 0x3B: // Adjust time
                // 0C 1B 1A C4 00 0F 3B 17 06 13 0B 02 10 70 0D
                // 0C 1B 1A C4 00 0F 3B xx xx xx xx xx xx XX 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11 12 13
                
                if(data[5] == 0x0F)
                {
                    Time.year = data[7]; 
                    Time.month = data[8]; 
                    Time.days = data[9]; 
                    Time.hours = data[10]; 
                    Time.minutes = data[11];
                    Time.seconds = data[12]; 
                    Time.miliseconds = 0x0000;

                    buf_tempo[0] = 0x3C; 
                    buf_tempo[1] = 0xAC; // ok
                    buf_tempo[2] = 0xED; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                else
                {
                    buf_tempo[0] = 0x3C; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                
                break;
            ////////////////////////////////////////////////////////////////////
            case 0x3D: // Get time
                // 0C 1B 1A C4 00 08 3D BB 0D
                // 00 01 02 03 04 05 06 07 08 

                buf_tempo[0] = Time.year; 
                buf_tempo[1] = Time.month; 
                buf_tempo[2] = Time.days; 
                buf_tempo[3] = Time.hours;
                buf_tempo[4] = Time.minutes; 
                buf_tempo[5] = Time.seconds; 
                buf_tempo[6] = Time.miliseconds >> 8; 
                buf_tempo[7] = Time.miliseconds;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 8);

                break;
                
            ////////////////////////////////////////////////////////////////////
            case 0x40:
                // 0C 1B 1A C4 00 0C 40 01 00 00 BA 0D
                if(State_Flags.Drill_State == 0 && MEM_CY15B064J_Flag.Mem_Read == 0 
                        && MEM_CY15B064J_Flag.Mem_Write == 0)
                {
                    MEM_CY15B064J_Flag.Mem_Erase_Request = 1; // timeout 5sec
                    buf_tempo[0] = 0x41; 
                    buf_tempo[1] = 0xAC; // ok
                    buf_tempo[2] = 0xED; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                else
                {
                    MEM_CY15B064J_Flag.Mem_Erase_Request = 0; // timeout 5sec
                    buf_tempo[0] = 0x41; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                break;
            ////////////////////////////////////////////////////////////////////
            case 0x42:
                // Erase Event memory 
                // 00 01 02 03 04 05 06 07 08 09 10 11
                // 0C 1B 1A C4 00 0C 42 01 00 00 B8 0D
                // 0C 1B 1A C4 00 0C 42 02 00 00 B7 0D
                // 0C 1B 1A C4 00 0C 42 03 00 00 B6 0D
                // 0C 1B 1A C4 00 0C 42 04 00 00 B5 0D
                if((MEM_CY15B064J_Flag.Mem_Erase_Request == 1) && (MEM_CY15B064J_Flag.Mem_Erase == 0))
                {
                    if(data[7] > 0 && data[7] <= 4)
                    {
                        //MEM_CY15B064J_Erase_In_Used = MEM_CY15B064J_Get_I2C_Address(data[7]); 
//                        buf_tempo[0] = 0x43; 
//                        buf_tempo[1] = 0xAC; // ok
//                        buf_tempo[2] = 0xED; 
//                        buf_tempo[3] = MEM_CY15B064J_Erase_In_Used;
//                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                        MEM_CY15B064J_Flag.Mem_Erase_Pass = 1; 
                    }
                    else
                    {
                        buf_tempo[0] = 0x43; 
                        buf_tempo[1] = 0xDE; // 
                        buf_tempo[2] = 0xAD; // 
                        buf_tempo[3] = 0x02; //
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                    }
                }
                else
                {
                    buf_tempo[0] = 0x43; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    buf_tempo[3] = 0x01; //
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                }    
                
                break;
                
            ////////////////////////////////////////////////////////////////////
            case 0x44:
                // Read 64 bytes
                // 0C 1B 1A C4 00 0C 44 00 00 00 B7 0D
                // 0C 1B 1A C4 00 0C 44 00 20 00 97 0D
                // 0C 1B 1A C4 00 0C 44 00 40 00 77 0D
                // 0C 1B 1A C4 00 0C 44 00 60 00 57 0D
                // 0C 1B 1A C4 00 0C 44 00 80 00 37 0D
                // 0C 1B 1A C4 00 0C 44 00 A0 00 17 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                address_event = data[7];
                address_event = address_event << 8; 
                address_event |= data[8]; 
                
                 //Read_Seq_16Reg_bytes_I2C(buf_tempo, MEM_CY15_M1_ID, address_event, 16);
                    
                
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 16);
                
                break; 
            ////////////////////////////////////////////////////////////////////     
            case 0x46:
                // Read event memory
                // 0C 1B 1A C4 00 0C 46 00 00 00 B5 0D
                //MEM_CY15B064J_Flag.Mem_Read = 1;
                if(MEM_CY15B064J_Flag.Mem_End_Read == 0)
                {
                    //MEM_CY15B064J_64_bytes();
                }
                else
                {
                    buf_tempo[0] = 0x46; 
                    buf_tempo[1] = 0xDE; // ok
                    buf_tempo[2] = 0xAD; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                 
                break; 
                
            case 0x47:
                // Stop Read event memory
                // 0C 1B 1A C4 00 0C 47 00 00 00 B4 0D
                MEM_CY15B064J_Flag.Mem_End_Read = 0; 
                MEM_CY15B064J_Flag.Mem_Read = 0;
                MEM_CY15B064J_Read_In_Used = 1; 
                MEM_CY15B064J_Read_bytes_pointer = 0;
                buf_tempo[0] = 0x48; 
                buf_tempo[1] = 0xAC; // ok
                buf_tempo[2] = 0xED; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x49:
                // get Memory write data pointer
                // 0C 1B 1A C4 00 0C 49 00 00 00 B2 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                MEM_MT25QL01_Get_Mem_Write_Pointer(buf_tempo); 
                Mem_test[0] = 0x50; 
                Mem_test[1] = buf_tempo[0]; 
                Mem_test[2] = buf_tempo[1];
                Mem_test[3] = buf_tempo[2];
                Mem_test[4] = buf_tempo[3];
                Mem_test[5] = buf_tempo[4];
                CAN_Encode_Sending(0x1B,0xC4, Mem_test, 6);
                
                break;    
            ////////////////////////////////////////////////////////////////////
            case 0x51:
                // get Memory write data pointer
                // 0C 1B 1A C4 00 0D x0 x1 x2 x3 x4 B2 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11 12 
                if(data[5] == 0x0D)
                {
                    if(data[6] <= 20)
                    {
                        buf_tempo[0] = data[6]; // Memory in used
                        buf_tempo[1] = data[7]; // byte 
                        buf_tempo[2] = data[8]; 
                        buf_tempo[3] = data[9]; 
                        buf_tempo[4] = data[10];
                        MEM_MT25QL01_Set_Mem_Write_Pointer(buf_tempo); 

                        buf_tempo[0] = 0x52; 
                        buf_tempo[1] = 0xAC; // ok
                        buf_tempo[2] = 0xED; 
                        buf_tempo[3] = data[0]; // Memory in used
                        buf_tempo[4] = data[1]; // byte 
                        buf_tempo[5] = data[2]; 
                        buf_tempo[6] = data[3]; 
                        buf_tempo[7] = data[4];
                        buf_tempo[8] = data[5]; // Memory in used
                        buf_tempo[9] = data[6]; // byte 
                        buf_tempo[10] = data[7]; 
                        buf_tempo[11] = data[8]; 
                        buf_tempo[12] = data[9];
                        buf_tempo[13] = data[10];
                        buf_tempo[14] = data[11];
                        buf_tempo[15] = data[12];
                        buf_tempo[16] = data[13];
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 16);
                    }
                    else
                    {
                        buf_tempo[0] = 0x52; 
                        buf_tempo[1] = 0xDE; // 
                        buf_tempo[2] = 0xAD; // 
                        buf_tempo[3] = 0x02; // 
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                    }
                    
                }
                else
                {
                    buf_tempo[0] = 0x52; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    buf_tempo[3] = 0x01; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                }
                
                break;    
            ////////////////////////////////////////////////////////////////////
            case 0x53:
                // get Memory read data pointer
                // 0C 1B 1A C4 00 0C 53 00 00 00 A8 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                MEM_MT25QL01_Get_Mem_Read_Pointer(buf_tempo); 
                Mem_test[0] = 0x54; 
                Mem_test[1] = buf_tempo[0]; 
                Mem_test[2] = buf_tempo[1];
                Mem_test[3] = buf_tempo[2];
                Mem_test[4] = buf_tempo[3];
                Mem_test[5] = buf_tempo[4];
                CAN_Encode_Sending(0x1B,0xC4, Mem_test, 6);
                
                break;      
            ////////////////////////////////////////////////////////////////////
            case 0x55:
                // Set Memory Read data pointer
                // 0C 1B 1A C4 00 0D 55 01 00 00 00 00 A3 0D 
                // 0C 1B 1A C4 00 0D 55 x0 x1 x2 x3 x4 B2 0D
                // 0C 1B 1A C4 00 0D 55 02 07 FF FF C0 B2 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11 12 13
                if(data[5] == 0x0E)
                {
                    buf_tempo[0] = data[7]; // Memory in used
                    buf_tempo[1] = data[8]; // byte 
                    buf_tempo[2] = data[9]; 
                    buf_tempo[3] = data[10]; 
                    buf_tempo[4] = data[11];
                    MEM_MT25QL01_Set_Mem_Read_Pointer(buf_tempo); 
                    
                    buf_tempo[0] = 0x56; 
                    buf_tempo[1] = 0xAC; // ok
                    buf_tempo[2] = 0xED; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                }
                else
                {
                    buf_tempo[0] = 0x56; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                }
                break;     
             ////////////////////////////////////////////////////////////////////   
            case 0x57:
                // Test event write memory
                // 0C 1B 1A C4 00 0C 57 00 00 00 A4 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                // all event are 16 bytes
//                buf_tempo[0] = 0xAA;
//                buf_tempo[1] = Time.year;
//                buf_tempo[2] = Time.month;
//                buf_tempo[3] = Time.days;
//                buf_tempo[4] = Time.hours;
//                buf_tempo[5] = Time.minutes;
//                buf_tempo[6] = Time.seconds;
//                buf_tempo[7] = (Time.miliseconds & 0xFF00) >> 8;
//                buf_tempo[8] = Time.miliseconds & 0x00FF;
//                buf_tempo[9] = 0x0C;
//                buf_tempo[10] = 0x00; // not used
//                buf_tempo[11] = 0x00; // not used
//                buf_tempo[12] = 0x00; // not used
//                buf_tempo[13] = 0x00; // not used 
//                buf_tempo[14] = 0xEE; // not used
//                buf_tempo[15] = 0xEE; // not used 
//                //MEM_CY15B064J_Write_Bytes(MEM_CY15_M1_ID, 0, buf_tempo, 16);
//                Write_Seq_16bReg_bytes_I2C(MEM_CY15_M1_ID, 0, buf_tempo, 16); 
                Save_Event_Cmd_Buffer(0xAA, 0x0F);
                
                
                buf_tempo[0] = 0x58; 
                buf_tempo[1] = 0xAC; // ok
                buf_tempo[2] = 0xED; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                
                
                break;  
            ////////////////////////////////////////////////////////////////////
            case 0x59:
                // Reset Memory write data pointer
                // 0C 1B 1A C4 00 0C 59 00 00 00 A2 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x01; // Memory in used
                buf_tempo[1] = 0x00; // byte 
                buf_tempo[2] = 0x00; 
                buf_tempo[3] = 0x00; 
                buf_tempo[4] = 0x00;
                MEM_MT25QL01_Set_Mem_Write_Pointer(buf_tempo); 

                buf_tempo[0] = 0x5A; 
                buf_tempo[1] = 0xAC; // ok
                buf_tempo[2] = 0xED; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                
                break;   
            //////////////////////////////////////////////////////////////////// 
            ////////////////////////////////////////////////////////////////////
            case 0x5B:
                // Read Interrupt Accel HG
                // 0C 1B 1A C4 00 0C 5B 00 00 00 A0 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x5C; 
                buf_tempo[1] = 0xAC; // ok
                buf_tempo[2] = 0xED; 
                buf_tempo[3] = ADXL373_SPI_Get_Interrupt();
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                
                break;   
            ////////////////////////////////////////////////////////////////////
                
            case 0x5D:
                // Read any register Accel HG
                // 0C 1B 1A C4 00 0C 5D 3F 00 00 5F 0D  // read power
                // 0C 1B 1A C4 00 0C 5D 04 00 00 9A 0D  // read status
                // 0C 1B 1A C4 00 0C 5D 05 00 00 99 0D  // read status
                // 0C 1B 1A C4 00 0C 5D 24 00 00 7A 0D  // read thresh X L
                // 0C 1B 1A C4 00 0C 5D 3E 00 00 60 0D  // Meas ctl
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x5E; 
                buf_tempo[1] = 0xAC; // ok
                buf_tempo[2] = 0xED; 
                buf_tempo[3] = ADXL373_SPI_Get_Register(data[7]);
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                
                break;   
            ////////////////////////////////////////////////////////////////////   
            case 0x5F:
                // Read max peak
                // 0C 1B 1A C4 00 0C 5F 00 00 00 9C 0D
                Mem_test[0] = (ACC373_MAXPEAK_X_H << 1)| 0x01;
                Mem_test[1] = ADXL373_SPI_Get_Data(Mem_test, 1, buf_tempo, 6);
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 6);
                
                break;   
            ////////////////////////////////////////////////////////////////////  
            case 0x60:
                // Read data
                // 0C 1B 1A C4 00 0C 60 00 00 00 9B 0D
                Mem_test[0] = (ACC373_XDATA_H << 1)| 0x01;
                Mem_test[1] = ADXL373_SPI_Get_Data(Mem_test, 1, buf_tempo, 6);
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 6);
                
                break;   
            //////////////////////////////////////////////////////////////////// 
            case 0x61:
                // Stop Accel 
                // 0C 1B 1A C4 00 0C 61 00 00 00 9A 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                ADXL373_SPI_Stop_Sensor(); 
                buf_tempo[0] = 0x62; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break;
            ////////////////////////////////////////////////////////////////////
            case 0x63:
                // Burst Out
                // 0C 1B 1A C4 00 0C 63 00 00 00 98 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                
                //MEM_MT25QL01_Read_Bytes(MT25QL01_Read_In_Used, buf_tempo, 64);
                if(Buffer_Read_Pointer < 12288)
                {
                    for(i=0; i<64; i++)
                    {
                        buf_tempo[i] = Buffer_RAM_Before[Buffer_Read_Pointer++]; 
                    }
                
                    CAN_Send_MSG(0xAA, buf_tempo, 64);
                    //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                }
                else
                {
                    buf_tempo[0] = 0x63; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                }
                
                
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x65:
                // Burst out finish
                // 0C 1A 1B C4 00 0C 65 00 00 00 96 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                Buffer_Read_Pointer=0;
                buf_tempo[0] = 0x66; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x67:
                // Read ADC 4 channel
                // 0C 1B 1A C4 00 0C 67 00 00 00 94 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //buf_tempo[1] = I2CSequentialSetReadReg(Mem_test, ADC_AD7993_ID, 0x30, 0x04);
                
                buf_tempo[0] = 0x68; 
                
                tempo16 = Mem_test[0] & 0x0F; // Filter 4 MSB bit
                gyro_raw_value_Unsigned = (tempo16 << 8) | Mem_test[1]; 

                tempo16 = Mem_test[2] & 0x0F; // Filter 4 MSB bit
                gyro_Vol_Ref_Unsigned = (tempo16 << 8) | Mem_test[3]; 

                if(gyro_raw_value_Unsigned > gyro_Vol_Ref_Unsigned)
                {
                    gyro_value = 2500 + gyro_raw_value_Unsigned - gyro_Vol_Ref_Unsigned; 
                }
                else
                {
                    gyro_value = 2500 + gyro_Vol_Ref_Unsigned - gyro_raw_value_Unsigned; 
                }
                //gyro_value = gyro_raw_value_Unsigned - gyro_Vol_Ref_Unsigned; 
                
                // buf_tempo[1] = status; // 
                buf_tempo[2] = Mem_test[0]; //
                buf_tempo[3] = Mem_test[1]; // 
                buf_tempo[4] = Mem_test[2]; // 
                buf_tempo[5] = Mem_test[3]; // 
                buf_tempo[6] = gyro_value >> 8; // 
                buf_tempo[7] = gyro_value; //
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 8);
                
                //buf_tempo[1] = status; // 
//                buf_tempo[2] = Mem_test[0]; //
//                buf_tempo[3] = Mem_test[1]; // 
//                buf_tempo[4] = Mem_test[2]; // 
//                buf_tempo[5] = Mem_test[3]; // 
//                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 6);
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x69:
                // Accel LG1 read range
                // 0C 1B 1A C4 00 0C 69 00 00 00 92 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[1] = ADXL355_SPI_Read_Accel_Device_Register(0x2C);
                
                buf_tempo[0] = 0x70; 
                //buf_tempo[1] = status; // 
                //buf_tempo[2] = Mem_test[0]; //
                //buf_tempo[3] = Mem_test[1]; // 
                //buf_tempo[4] = Mem_test[2]; // 
                //buf_tempo[5] = Mem_test[3]; // 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x71:
                // Accel LG2 read range
                // 0C 1B 1A C4 00 0C 71 00 00 00 8A 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //buf_tempo[1] = ADXL355_I2C_Read_Register(ACC_ADXL355_LG2_ID, 0x2C);
                
                buf_tempo[0] = 0x72; 
                //buf_tempo[1] = status; // 
                //buf_tempo[2] = Mem_test[0]; //
                //buf_tempo[3] = Mem_test[1]; // 
                //buf_tempo[4] = Mem_test[2]; // 
                //buf_tempo[5] = Mem_test[3]; // 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x73:
                // Accel LG2 read  x y z
                // 0C 1B 1A C4 00 0C 73 00 00 00 88 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //status = I2CSequentialSetReadReg(buffer, ACC_ADXL355_LG2_ID, cmd[0], 9);
                buf_tempo[0] = (0x08 << 1) | 0x01;
                ADXL355_SPI_Get_Data(SPI_CS_ACC_LG2, buf_tempo, 1, Mem_test, 9); 
                //buf_tempo[1] = I2CSequentialSetReadReg(Mem_test, ACC_ADXL355_LG2_ID, buf_tempo[0], 9);
                //buf_tempo[1] = ADXL355_I2C_Read_Register(ACC_ADXL355_LG2_ID, 0x2C);
                
                buf_tempo[0] = 0x74; 
                buf_tempo[1] = 0xA2; // 
                buf_tempo[2] = Mem_test[0]; // X
                buf_tempo[3] = Mem_test[1]; // X
                buf_tempo[4] = Mem_test[2]; // X
                buf_tempo[5] = Mem_test[3]; // Y
                buf_tempo[6] = Mem_test[4]; // Y
                buf_tempo[7] = Mem_test[5]; // Y
                buf_tempo[8] = Mem_test[6]; // Z
                buf_tempo[9] = Mem_test[7]; // Z
                buf_tempo[10] = Mem_test[8]; // Z
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 11);
               
                break; 
            ////////////////////////////////////////////////////////////////////
            case 0x75:
                // Accel LG1 read  x y z
                // 0C 1B 1A C4 00 0C 75 00 00 00 86 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = (0x08 << 1) | 0x01;
                ADXL355_SPI_Get_Data(SPI_CS_ACC_LG1, buf_tempo, 1, Mem_test, 9); 
                //status = I2CSequentialSetReadReg(buffer, ACC_ADXL355_LG2_ID, cmd[0], 9);
                //buf_tempo[0] = 0x08; // XDATA3
                //buf_tempo[1] = I2CSequentialSetReadReg(Mem_test, ACC_ADXL355_LG2_ID, buf_tempo[0], 9);
                //buf_tempo[1] = ADXL355_I2C_Read_Register(ACC_ADXL355_LG2_ID, 0x2C);
                
                buf_tempo[0] = 0x76; 
                buf_tempo[1] = 0xA1; // 
                buf_tempo[2] = Mem_test[0]; // X
                buf_tempo[3] = Mem_test[1]; // X
                buf_tempo[4] = Mem_test[2]; // X
                buf_tempo[5] = Mem_test[3]; // Y
                buf_tempo[6] = Mem_test[4]; // Y
                buf_tempo[7] = Mem_test[5]; // Y
                buf_tempo[8] = Mem_test[6]; // Z
                buf_tempo[9] = Mem_test[7]; // Z
                buf_tempo[10] = Mem_test[8]; // Z
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 11);
               
                break; 
             ////////////////////////////////////////////////////////////////////
            case 0x77:
                // Magnetometer x y z
                // 0C 1B 1A C4 00 0C 77 00 00 00 84 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x00;
                //buf_tempo[1] = I2CSequentialSetReadReg(Mem_test, MAG_MMC5983_ID, buf_tempo[0], 6);
                //status = I2CSequentialSetReadReg(buffer, ACC_ADXL355_LG2_ID, cmd[0], 9);
                //buf_tempo[0] = 0x08; // XDATA3
                //buf_tempo[1] = I2CSequentialSetReadReg(Mem_test, ACC_ADXL355_LG2_ID, buf_tempo[0], 9);
                //buf_tempo[1] = ADXL355_I2C_Read_Register(ACC_ADXL355_LG2_ID, 0x2C);
                MAG_MMC5983MA_Get_data_SPI(Mem_test, 6);
                buf_tempo[0] = 0x78; 
                buf_tempo[1] = Mem_test[0]; 
                buf_tempo[2] = Mem_test[1]; 
                buf_tempo[3] = Mem_test[2]; 
                buf_tempo[4] = Mem_test[3]; 
                buf_tempo[5] = Mem_test[4]; 
                buf_tempo[6] = Mem_test[5]; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 7);
               
                break; 
            ///////////////////////////////////////////////////////////////
            case 0x79:
                // Mag Read ID
                // 0C 1B 1A C4 00 0C 79 00 00 00 82 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
       
                tempo8 = MAG_MMC5983MA_read_ID(); 
                
                buf_tempo[0] = 0x79; 
                buf_tempo[1] = tempo8; // 
                //buf_tempo[2] = Mem_test[0]; //
                //buf_tempo[3] = Mem_test[1]; // 
                //buf_tempo[4] = Mem_test[2]; // 
                //buf_tempo[5] = Mem_test[3]; // 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
               
                break; 
             ///////////////////////////////////////////////////////////////
            case 0x7A:
                // Mag Take meas
                // 0C 1B 1A C4 00 0C 7A 00 00 00 81 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //buf_tempo[1] = Write_1_reg_I2C(MAG_MMC5983_ID,0x09,0x01);
                buf_tempo[0] = 0x09;
                buf_tempo[1] = 0x01;
                MAG_MMC5983MA_Write_data_SPI(buf_tempo, 2); 
                
                buf_tempo[0] = 0x7A; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
               
                break; 
            ///////////////////////////////////////////////////////////////
            case 0x7B:
                // Disable all sensors
                // 0C 1B 1A C4 00 0C 7B 00 00 00 80 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                Disabled_All_Sensors();
                
                buf_tempo[0] = 0x7C; 
                //buf_tempo[1] = status; // 
                //buf_tempo[2] = Mem_test[0]; //
                //buf_tempo[3] = Mem_test[1]; // 
                //buf_tempo[4] = Mem_test[2]; // 
                //buf_tempo[5] = Mem_test[3]; // 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
               
                break; 
            ///////////////////////////////////////////////////////////////
            case 0x7D:
                // Read memory status
                // 0C 1B 1A C4 00 0C 7D 00 00 00 7E 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                pointer = 0; 
                
                buf_tempo[pointer++] = 0x7E; 
                buf_tempo[pointer++] = MT25QL01_In_Used; // 
                if(MT25QL01_Flag.Mem_Overflow)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Fail)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Busy)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_WEP)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Wait_Write)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Write)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Test_Write)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Test_Read)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Read)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Pointer_Set)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Erase_Request)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Erase_Pass)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_Erase)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                if(MT25QL01_Flag.Mem_All_Sleep)
                    buf_tempo[pointer++] = 0x01;
                else
                    buf_tempo[pointer++] = 0x00;
                
                tempo16 = MEM_MT25QL01_Check_Status_Sleep(MT25QL01_In_Used);
                buf_tempo[pointer++] = tempo16 >> 8;
                buf_tempo[pointer++] = tempo16;
   
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, pointer);
               
                break; 
             ///////////////////////////////////////////////////////////////
            case 0x7F:
                // wake up memory
                // 0C 1B 1A C4 00 0C 7F 01 00 00 7B 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                
                buf_tempo[0] = 0x80; 
                
                if(data[7] > 0 && data[7] <= 20)
                {
                    
                    MEM_MT25QL01_Release_Deep_Power_Down(data[7]); 
                    buf_tempo[1] = 0xAC; // ok
                    buf_tempo[2] = 0xED; 
                   
                }
                else
                {
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                }

                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
               
                break; 
              ///////////////////////////////////////////////////////////////
                 
            case 0x81:
                // Get I2C errors
                // 0C 1B 1A C4 00 0C 81 01 00 00 79 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                
                buf_tempo[0] = 0x82; 
                buf_tempo[1] = I2C_Errors_Counter >> 24; 
                buf_tempo[2] = I2C_Errors_Counter >> 16; 
                buf_tempo[3] = I2C_Errors_Counter >> 8; 
                buf_tempo[4] = I2C_Errors_Counter; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 5);
               
                break; 
                
            ////////////////////////////////////////////////////////////////////
           case 0x83:
                // Erase I2C errors
                // 0C 1B 1A C4 00 0C 83 01 00 00 77 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                I2C_Errors_Counter = 1; 
                buf_tempo[0] = 0x84; 
                buf_tempo[1] = I2C_Errors_Counter >> 24; 
                buf_tempo[2] = I2C_Errors_Counter >> 16; 
                buf_tempo[3] = I2C_Errors_Counter >> 8; 
                buf_tempo[4] = I2C_Errors_Counter; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 5);
               
                break;  
            ////////////////////////////////////////////////////////////////////
            case 0x85:
                // Accel LG1 read  ID
                // 0C 1B 1A C4 00 0C 85 00 00 00 76 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x86; 
                buf_tempo[1] = Get_Accel_Device_ID(SPI_CS_ACC_LG1);
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            ////////////////////////////////////////////////////////////////////
                case 0x87:
                // Accel LG2 read  ID
                // 0C 1B 1A C4 00 0C 87 00 00 00 74 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                buf_tempo[0] = 0x88; 
                buf_tempo[1] = Get_Accel_Device_ID(SPI_CS_ACC_LG2);
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x89:
                // Gyro  read value
                // 0C 1B 1A C4 00 0C 89 00 00 00 72 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                tempo16 = ADC_ADS868x_READ_DATA(SPI_CS_GYRO);    
                    
                buf_tempo[0] = 0x90;
                buf_tempo[1] = tempo16 >> 8; 
                buf_tempo[2] = tempo16 & 0x00FF;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x91:
                // Gyro ADC read Range
                // 0C 1B 1A C4 00 0C 91 00 00 00 6A 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                tempo16 = Get_ADC_ADS868x_RANGE(SPI_CS_GYRO);    
                    
                buf_tempo[0] = 0x92;
                buf_tempo[1] = tempo16 >> 8; 
                buf_tempo[2] = tempo16 & 0x00FF;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x93:
                // Gyro ADC Set Range
                // 0C 1B 1A C4 00 0C 93 00 00 00 68 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                    
                buf_tempo[0] = 0x94;
                buf_tempo[1] = data[7];
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x95:
                // Read ID Gyro
                // 0C 1B 1A C4 00 0C 95 00 00 00 66 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                Get_ADC_ADS868x_Device_ID(SPI_CS_GYRO);
                //buf_tempo[0] = 0x96;
                //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x97:
                // Set Dataout Gyro
                // 0C 1B 1A C4 00 0C 97 00 00 00 64 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                SET_ADC_ADS868x_DATAOUT_CTL(SPI_CS_GYRO);
                buf_tempo[0] = 0x98;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x99:
                // Read CH0 ADC 4CH
                // 0C 1B 1A C4 00 0C 99 00 00 00 62 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                tempo16 = ADC_ADS863x_READ_DATA(SPI_CS_VOLT, data[7]);    
                    
                //tempo16 = tempo16 << 3; 
                
                buf_tempo[0] = 0x9A;
                buf_tempo[1] = data[7]; 
                buf_tempo[2] = (tempo16 & 0xFF00) >> 8; 
                buf_tempo[3] = tempo16 & 0x00FF;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x9B:
                // Read RANGE CH1 ADC 4CH
                // 0C 1B 1A C4 00 0C 9B 00 00 00 60 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                tempo8 = Get_ADC_ADS863x_RANGE(SPI_CS_VOLT);     
                    
                //tempo16 = tempo16 << 3; 
                
                buf_tempo[0] = 0x9C; 
                buf_tempo[1] = tempo8;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 2);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x9D:
                // Read AUX config
                // 0C 1B 1A C4 00 0C 9D 00 00 00 5E 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                tempo16 = Get_ADC_ADS863x_AUX_CONFIG(SPI_CS_VOLT);    
                    
                //tempo16 = tempo16 << 3; 
                
                //buf_tempo[0] = 0x9E;
                //buf_tempo[1] = (tempo16 & 0xFF00) >> 8; 
                //buf_tempo[2] = tempo16 & 0x00FF;
                //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                break; 
            ///////////////////////////////////////////////////////////////////
                case 0x9F:
                // Wake up the f***ing device
                // 0C 1B 1A C4 00 0C 9F 00 00 00 5C 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                //SET_ADC_ADS868x_RANGE(SPI_CS_GYRO, data[7]);    
                 SET_ADC_ADS863x_POWER_UP(SPI_CS_VOLT); 
                    
                //tempo16 = tempo16 << 3; 
                
                buf_tempo[0] = 0xA0;
                //buf_tempo[1] = (tempo16 & 0xFF00) >> 8; 
                //buf_tempo[2] = tempo16 & 0x00FF;
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break;
            ////////////////////////////////////////////////////////////////////
                case 0xA1:
                // Testing the time
                // 0C 1B 1A C4 00 0C A1 00 00 00 5A 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                    
                //tempo16 = tempo16 << 3; 
                Time_debug_Flag = 1; 
                //buf_tempo[0] = 0xA2;
                //buf_tempo[1] = (tempo16 & 0xFF00) >> 8; 
                //buf_tempo[2] = tempo16 & 0x00FF;
                //CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
                break;
            ////////////////////////////////////////////////////////////////////
                
            case 0xE0:
                // reset
                // 0C 1B 1A C4 00 0C E0 BF FF 0C 51 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                if(data[7] == 0xBF)
                {
                    if(data[8] == 0xFF)
                    {
                        if(data[9] == 0x0C)
                        {
                            asm volatile ("RESET"); 
                        }
                        else
                        {
                            buf_tempo[0] = 0xE0; 
                            buf_tempo[1] = 0xDE; // 
                            buf_tempo[2] = 0xAD; // 
                            CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                        }
                    }
                    else
                    {
                        buf_tempo[0] = 0xE0; 
                        buf_tempo[1] = 0xDE; // 
                        buf_tempo[2] = 0xAD; // 
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                    }
                }
                else
                {
                    buf_tempo[0] = 0xE0; 
                    buf_tempo[1] = 0xDE; // 
                    buf_tempo[2] = 0xAD; // 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                }
                
               
                break; 
             
             ////////////////////////////////////////////////////////////////////
            case 0xF0:
                // Get version
                // 0C 1B 1A C4 00 0C F0 00 00 00 0B 0D
                // 00 01 02 03 04 05 06 07 08 09 10 11
                Get_Version_Firmware(buf_tempo); 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 6);
               
                break; 
            case 0xFF:
                break;
            ////////////////////////////////////////////////////////////////////
            /////////////////////////// Game Over //////////////////////////////
            ////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////
        }

        // override debug UART
//        for(i=0; i<size;i++)
//        {
//            write_uart_1(data[i]);
//        }
        
        
    }
    else
    {
        if(data[3] == 0xB0)
        {
            // 0C 1A 1B B0 00 1C 00 00 00 00 00 6A 04 00 05 00 00 00 FF FF FF FF FF FF FF FF 94 0D
            // 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
            buf_tempo[0] = Pointer_Block_Flash_test >> 8; 
            buf_tempo[1] = Pointer_Block_Flash_test & 0xFF; 
            buf_tempo[2] = Pointer_Entire_Flash_test >> 24; 
            buf_tempo[3] = Pointer_Entire_Flash_test >> 16; 
            buf_tempo[4] = Pointer_Entire_Flash_test >> 8;  
            buf_tempo[5] = Pointer_Entire_Flash_test;
            buf_tempo[6] = Pointer_Entire_Flash_test >> 8;  
            buf_tempo[7] = Pointer_Entire_Flash_test;
            
            //uart_1_send_message(0xBA,buffer_TX,6); // received
            CAN_Encode_Sending(0x1B,0xBA,buf_tempo,8); // received
        
        }
        if(data[3] == 0xB1)
        {
            Pointer_Block_Flash_test = 0; 
            Pointer_Entire_Flash_test = 0; 
            buf_tempo[0] = 0xB2; 
            CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 1);
            
        }
        if(data[3] == 0xB6) // goto to bootloader 
        {
            // 0C 1B 1A B6 00 09 B6 56 0D
            // 00 01 02 03 04 05 06 07 08 
            
            if(data[2] == 0x1A) // destination
            {
                if(data[6] == 0xB6)
                {
                    if(data[7] == 0x56)
                    {
                        //asm volatile ("goto %0" : : "r"(addr)); // not working
                        asm volatile ("RESET"); 
                        //RESET
                        buf_tempo[0] = 0xB6; 
                        buf_tempo[1] = 0xAC; // ok
                        buf_tempo[2] = 0xED; 
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 3);
                    }
                    else
                    {
                        buf_tempo[0] = 0xB6; 
                        buf_tempo[1] = 0xDE; // ok
                        buf_tempo[2] = 0xAD; 
                        buf_tempo[3] = 0x03; 
                        CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                    }
                }
                else
                {
                    buf_tempo[0] = 0xB6; 
                    buf_tempo[1] = 0xDE; // ok
                    buf_tempo[2] = 0xAD; 
                    buf_tempo[3] = 0x02; 
                    CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
                }
            }
            else
            {
                buf_tempo[0] = 0xB6; 
                buf_tempo[1] = 0xDE; // ok
                buf_tempo[2] = 0xAD; 
                buf_tempo[3] = 0x01; 
                CAN_Encode_Sending(0x1B,0xC4, buf_tempo, 4);
            }
            
            
        }
        if(data[3] == 0xD0)
        {
            switch(data[6])
            {
                case 0x01: // ack from SAST COM check
                    buf_tempo[0] = 0x02; 
                    CAN_Encode_Sending(0x1C,0xD0, buf_tempo, 1);
                    break;
                case 0x04: // read one packet
                    if(MT25QL01_Flag.Mem_Read == 0)
                    {
                        MEM_MT25QL01_Init_Read(); 
                    }
                    
                    MEM_MT25QL01_Read_Bytes(MT25QL01_Read_In_Used, buf_tempo, 64);
                    
                    CAN_Send_MSG(0xAA, buf_tempo, 64);
                    break;
                case 0x06:
                    MEM_MT25QL01_End_Read();
                    buf_tempo[0] = 0x07; 
                    CAN_Encode_Sending(0x1C, 0xD0, buf_tempo, 1);
                break;
            }
        }
       
    }
    
    

}

/*******************************************************************************
 * Function: CAN_Encode_Sending
 * Parameters: uint8_t command, uint8_t *data, uint16_t data_len
 * Return: none
 * Description: 
 ******************************************************************************/
void CAN_Encode_Sending(uint8_t dest, uint8_t command, uint8_t *data, uint16_t data_len)
{
    /* Format SPI_2 
     * SOF (1 byte) == 0x0C (Not in checksum)
     * Source (1 byte) == 0x1C (CUA)
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
    buffer[pointer++] = dest;
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
    
    
    CAN_Send_MSG(0xAA,buffer,full_length); 
}
