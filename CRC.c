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
 *      CRC.c
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/
#include "CRC.h"
/******************************************************************************
 * Function:        void CRC_Init(void)
 *
 * PreCondition:    None   
 *
 * Input:           None
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function configures CRC module
 *****************************************************************************/
void CRC_Init( void )
{

    CRCCONLbits.CRCEN = 0;
    CRCXORL = 0x0000;
        asm volatile ("nop");
        asm volatile ("nop");
   

    CRCWDATL = 0x0000;

    CRCWDATH = 0x0000; 	//  NOTE:Non-direct Initial value fed to CRCWDAT
    CRCXORL = POLY;             // Generator Polynomial // X^12 + X^5
    CRCXORH = 0x0000;
    CRCCON1bits.CRCISEL = 0;
    CRCCON2bits.PLEN = POLYLEN; // Length of polynomial-1"
    CRCCON2bits.DWIDTH = 7;
    CRCCON1bits.LENDIAN = 0x0;
    CRCCON1bits.CRCEN = 1;
}


/******************************************************************************
 * Function:        uint16_t CRC_ChecksumByte(uint8_t* data, uint8_t Number_of_bytes, uint16_t prev_CRC)
 *
 * PreCondition:    None
 *
 * Input:           data - Pointer to the first data byte for which CRC needs to be
 *                  calculated.
 *                  Number_of_bytss - Total number of bytes for which CRC needs to be
 *                  calculated. ==> 15 bytes Maximum ???
 *                  prev_CRC - previous CRC result.
 *
 * Output:          CRCWDATL Register content that is the two byte checksum
 *
 * Side Effects:    None
 *
 * Overview:        Calculates the checksum and returns the value
 *****************************************************************************/
uint16_t CRC_ChecksumByte( uint8_t *data, uint8_t Number_of_bytes, uint16_t prev_CRC )
{
    uint8_t volatile    *dest = ( uint8_t * ) &CRCDATL;

    CRCWDATL = prev_CRC;
    IFS3bits.CRCIF=0;				//CRC status Flag is Cleared
    do
    {
       while( (0 == CRCCON1bits.CRCFUL) && (0 < Number_of_bytes) )
        {
            *dest = *data;
            data++;
            Number_of_bytes--;
        }
    } while( 0 < Number_of_bytes );
 CRCCON1bits.CRCGO = 1;
 CRCDATL = 0x0000;   /* Do this to shift the last word out of the CRC shift register */
 while( CRCCON1bits.CRCFUL == 1 );
   
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
	while(CRCCON1bits.CRCMPT!=1);

        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
	while(IFS3bits.CRCIF!=1);

        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
	CRCCON1bits.CRCGO=0;
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");

    return ( CRCWDATL );
}

/*******************************************************************************
 End of File
 */