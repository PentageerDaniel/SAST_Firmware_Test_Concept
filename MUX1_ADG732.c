
/******************************************************************************/
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    MEM_MT25QL01.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 ******************************************************************************/
#include "MUX1_ADG732.h"


/*******************************************************************************
 * Function: MUX1_ADG732_INIT
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MUX1_ADG732_INIT(void)
{
    CS_CONT = 0; 
    while (CS_CONT != 0)
    {
        CS_CONT = 0;
    }
    CTL_CS_A0 = 0; 
    CTL_CS_A1 = 0; 
    CTL_CS_A2 = 0; 
    CTL_CS_A3 = 0; 
    CTL_CS_A4 = 0; 
    CS_CONT = 1; 
    while (CS_CONT != 1)
    {
        CS_CONT = 1;
    }
}

/*******************************************************************************
 * Function: MUX1_ADG732_INIT
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MUX1_ADG732_CHIP_SELECT(uint8_t port)
{
    
    //PORTA = 0x02; 
//    CTL_CS_WR = 0; 
//    while (CTL_CS_WR != 0)
//    {
//        CTL_CS_WR = 0;
//    }
//    
//    CS_CONT = 0; // Select chip control
//    while (CS_CONT != 0)
//    {
//        CS_CONT = 0;
//    }
//    
//    Start_Timer_3(100);
//    while(Check_Timer_3() == 0){}; 
//    Stop_Timer_3();
    
    //CTL_CS_WR = 0; 
    
    switch (port)
    {
        case 0:
            // None
            PORTA = 0x00;
//            CTL_CS_A0 = 0; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0; 
            break;
        case 1:
            // CS_MEM1
            PORTA = 0x01;
//            CTL_CS_A0 = 1; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0; 
            break;
        case 2:
            // CS_MEM2
            PORTA = 0x02;
            break;
        case 3:
            // CS_LG1
            PORTA = 0x03;
//            CTL_CS_A0 = 1; 
//            CTL_CS_A1 = 1; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0;  
            break;
        case 4:
            // CS_LG2
            PORTA = 0x04;
//            CTL_CS_A0 = 0; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 1; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0; 
            break;    
        case 5:
            // CS_HG1
            PORTA = 0x05;
//            CTL_CS_A0 = 1; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 1; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0; 
            break;    
        case 6:
            // CS_GYRO
            PORTA = 0x06;
//            CTL_CS_A0 = 0; 
//            CTL_CS_A1 = 1; 
//            CTL_CS_A2 = 1; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0; 
            break;
        case 7:
            // CS_VOLT
            PORTA = 0x07;
//            CTL_CS_A0 = 1; 
//            CTL_CS_A1 = 1; 
//            CTL_CS_A2 = 1; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0;  
            break;    
        case 8:
            // CS_MAG
            PORTA = 0x08;
//            CTL_CS_A0 = 0; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 1; 
//            CTL_CS_A4 = 0; 
            break;    
        case 9:
            // CS_SRAM1
            PORTA = 0x09;
//            CTL_CS_A0 = 1; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 1; 
//            CTL_CS_A4 = 0; 
            break;    
        case 10:
            // Not used
            PORTA = 0x0A;
//            CTL_CS_A0 = 0; 
//            CTL_CS_A1 = 1; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 1; 
//            CTL_CS_A4 = 0; 
            break;    
        
//        default:
//            // Set default port S1 where nothing connected 
//            CTL_CS_A0 = 0; 
//            CTL_CS_A1 = 0; 
//            CTL_CS_A2 = 0; 
//            CTL_CS_A3 = 0; 
//            CTL_CS_A4 = 0; 
//            break;       
            
    }
    
    
    
//    Start_Timer_3(5100);
//    while(Check_Timer_3() == 0){}; 
//    Stop_Timer_3();
//    
//    CTL_CS_WR = 1; 
//    while (CTL_CS_WR != 1)
//    {
//        CTL_CS_WR = 1;
//    }
//    
//    CS_CONT = 1;  // Deselect chip control
//    while (CS_CONT != 1)
//    {
//        CS_CONT = 1;
//    }
    
    //CTL_CS_A1 = 1;
    
}

/*******************************************************************************
 * Function: MUX1_ADG732_INIT
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MUX1_ADG732_CHIP_DESELECT(uint8_t port)
{
    
    PORTA = 0x00; 
//    CS_CONT = 0; 
//    while (CS_CONT != 0)
//    {
//        CS_CONT = 0;
//    }
//    
//    Start_Timer_3(100);
//    while(Check_Timer_3() == 0){}; 
//    Stop_Timer_3();
//    
//    CTL_CS_A0 = 0; 
//    CTL_CS_A1 = 0; 
//    CTL_CS_A2 = 0; 
//    CTL_CS_A3 = 0; 
//    CTL_CS_A4 = 0; 
//    CS_CONT = 1; 
//    
//    Start_Timer_3(100);
//    while(Check_Timer_3() == 0){}; 
//    Stop_Timer_3();
//    while (CS_CONT != 1)
//    {
//        CS_CONT = 1;
//    }
    
    
}
