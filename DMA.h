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
 *      DMA.h
 * 
 * @Summary
 *      
 * 
 ******************************************************************************/

#include "Init.h"


void Init_DMA(void); 
void DMA_Channel_0(void); 
void DMA_Channel_1(void); 
void DMA_Channel_2(void); 

/*******************************************************************************
 * external Variable and Function declaration
 ******************************************************************************/
//extern uint8_t __attribute__((aligned(4)))Buffer_Uart_Msg[64];
extern uint8_t Buffer_Uart_Msg[16]; 
//extern volatile unsigned int Buffer_Uart_Msg[16]; 
