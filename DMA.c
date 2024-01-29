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
 *      DMA.c
 * 
 * @Summary
 *      
 * 
 ******************************************************************************/
#include "DMA.h"

/*******************************************************************************
 * Function: DMA_Channel_0
 * Parameters: none
 * Return: none
 * Description: Set DMA channel 0: Uart1 / DMA => RX1 to TX2
 ******************************************************************************/
void Init_DMA(void)
{
    DMACONbits.DMAEN=1;     // DMA Module Enable bit
    DMACONbits.PRSSEL=0;    // Channel Priority Scheme Selection bit
    DMAH=0x5000;            // set upper address limit
    DMAL=0x850;             // set lower address limit
}

/*******************************************************************************
 * Function: DMA_Channel_0
 * Parameters: none
 * Return: none
 * Description: Set DMA channel 0: Uart1 / DMA => RX1 to TX2
 ******************************************************************************/
void DMA_Channel_0(void)
{
    
    DMASRC0=(unsigned int)&U1RXREG;         // set source address
    DMADST0=(unsigned int)&U2TXREG;   // load destination address
    DMACNT0=1; // buffer is full 16,do a interrupt and transfer 16 bytes
    DMACH0=0;   // Reset Channel n Control Register
    DMACH0bits.SIZE = 1; // bytes
    DMACH0bits.SAMODE=0; //Source addr increment mode: 0 == do no increment
    DMACH0bits.DAMODE=0; //Dest addr increment mode: 0 == do no increment
    DMACH0bits.TRMODE=1; //Transfer mode One-Shot, Rep One-Shot, Continous
    DMAINT0bits.CHSEL=0x04; //Trigger on UART1 Receive
    DMACH0bits.CHEN=1; //Channel enable
    IFS0bits.DMA0IF=0; // interrupt

}

/*******************************************************************************
 * Function: DMA_Channel_1
 * Parameters: none
 * Return: none
 * Description: Set DMA channel 1
 ******************************************************************************/
void DMA_Channel_1(void)
{
    DMASRC1=(unsigned int)&U2RXREG;         // set source address
    DMADST1=(unsigned int)&U1TXREG;   // load destination address
    DMACNT1=1; // buffer is full 7,do a interrupt and transfer 16 bytes
    DMACH1=0;   // Reset Channel n Control Register
    DMACH1bits.SIZE = 1; // bytes
    DMACH1bits.SAMODE=0; //Source addr increment mode: 0 == do no increment
    DMACH1bits.DAMODE=0; //Dest addr increment mode: 0 == do no increment
    DMACH1bits.TRMODE=1; //Transfer mode One-Shot, Rep One-Shot, Continous
    DMAINT1bits.CHSEL=0x0E; //Trigger on UART2 Receive
    DMACH1bits.CHEN=1; //Channel enable
    IFS0bits.DMA1IF=0; // interrupt

}

/*******************************************************************************
 * Function: DMA_Channel_2
 * Parameters: none
 * Return: none
 * Description: Set DMA channel 1
 ******************************************************************************/
void DMA_Channel_2(void)
{
//    DMASRC2=(unsigned int)&U2RXREG;         // set source address
//    //DMASRC2=(unsigned short int)&U1TXREG;         // set source address
//    DMADST2=(unsigned int)&Buffer_Uart_Msg;   // load destination address
//    DMACNT2=16; // buffer is full 7,do a interrupt and transfer 16 bytes
//    DMACH2=0;   // Reset Channel n Control Register
//    DMACH2bits.SIZE = 1; // bytes
//    DMACH2bits.SAMODE=0; //Source addr increment mode: 0 == do no increment
//    DMACH2bits.DAMODE=1; //Dest addr increment mode: 0 == do no increment
//    DMACH2bits.RELOAD = 1; 
//    DMACH2bits.TRMODE=1; //Transfer mode One-Shot, Rep One-Shot, Continous
//    DMAINT2bits.CHSEL=0x0E; //Trigger on UART2 Receive
//    DMACH2bits.CHEN=1; //Channel enable
//    IFS1bits.DMA2IF=0; // interrupt

}