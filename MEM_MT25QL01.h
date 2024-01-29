/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Pentageer

  @File Name
    MEM_MT25QL01.h

  @Summary
 

  @Description
    Describe the purpose of this file.
*/
/* ************************************************************************** */

/*************************************************************************
 * Include
 ************************************************************************/
#include "Init.h"

/*******************************************************************************
 * Internal Function declaration 
 ******************************************************************************/
void MEM_MT25QL01_Init(void); 
uint8_t MEM_MT25QL01_Read_ID(uint8_t cs_port, uint8_t *buffer);
uint8_t MEM_MT25QL01_Enter_Deep_Power_Down(uint8_t cs_port); 
uint8_t MEM_MT25QL01_Release_Deep_Power_Down(uint8_t cs_port); 
uint8_t MEM_MT25QL01_Enter_4_Bytes_Mode(uint8_t cs_port); 
uint8_t MEM_MT25QL01_Get_Status(uint8_t cs_port); 
uint8_t MEM_MT25QL01_Get_Flag(uint8_t cs_port); 
uint8_t MEM_MT25QL01_Read_Freeze_Bit(uint8_t cs_port); 
uint8_t MEM_MT25QL01_Write_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length); 
void MEM_MT25QL01_Write_Enable(uint8_t cs_port);
void MEM_MT25QL01_Write_Disable(uint8_t cs_port);
void MEM_MT25QL01_Init_Read(void);
uint8_t MEM_MT25QL01_Reading_Swap(void);
uint8_t MEM_MT25QL01_Writing_Swap(void); 
void MEM_MT25QL01_Read_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length);
void MEM_MT25QL01_End_Read(void); 
void MEM_MT25QL01_Erase_Memory_Init(void); 
void MEM_MT25QL01_Erase_Memory_Swap(uint8_t memory_to_swap); 
uint8_t MEM_MT25QL01_Erase_Memory(uint8_t memory_to_erase);
void MEM_MT25QL01_Pointer_Seaching(void); 
uint16_t MEM_MT25QL01_Check_Status_Sleep(uint8_t memory_to_check); 
void MEM_MT25QL01_Set_Sleep_Unused_ATM(uint8_t memory_in_used);
void MEM_MT25QL01_Wake_UP_All_Memory(void); 
void MEM_MT25QL01_Shutdowm_All_Memory(void); 

void MEM_MT25QL01_Get_Mem_Write_Pointer(uint8_t *buffer);
void MEM_MT25QL01_Set_Mem_Write_Pointer(uint8_t *buffer);
void MEM_MT25QL01_Get_Mem_Read_Pointer(uint8_t *buffer);
void MEM_MT25QL01_Set_Mem_Read_Pointer(uint8_t *buffer); 

/*******************************************************************************
 * External Function declaration
 ******************************************************************************/
extern void CAN_Encode_Sending(uint8_t destination, uint8_t command, uint8_t *data, uint16_t data_len); 

extern uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_2_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);


extern void Start_Timer_3(uint32_t microSec);
extern uint8_t Check_Timer_3(void);
extern void Stop_Timer_3(void); 
/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/

extern const uint8_t MT25QL01_Number_Max; 
extern uint8_t MT25QL01_In_Used; // show which memory is in 

extern const uint16_t MT25QL01_Sector_Max; // Sector size = 64kB

//extern const uint8_t MT25QL01_segment_Max; 
//extern uint8_t MT25QL01_segment_pointer; 
extern const uint32_t MT25QL01_bytes_Max;
extern uint32_t MT25QL01_bytes_pointer; 

extern uint8_t MT25QL01_Read_In_Used; // show which memory is in 
//extern uint8_t MT25QL01_Read_segment_pointer; 
extern uint32_t MT25QL01_Read_bytes_pointer; 

extern uint8_t MT25QL01_Erase_In_Used; // show which memory is in 
extern uint8_t MT25QL01_To_Erase; // 
//extern uint8_t MT25QL01_Erase_segment_pointer; 
extern uint32_t MT25QL01_Erase_bytes_pointer; 

extern uint8_t MT25QL01_Seek_In_Used; // show which memory is in 
extern uint32_t MT25QL01_Seek_bytes_pointer; 

extern struct {
    uint16_t Mem_Overflow : 1;
    uint16_t Mem_Fail : 1;
    uint16_t Mem_Busy : 1;
    uint16_t Mem_WEP : 1;
    uint16_t Mem_Wait_Write : 1;  // wait finish to write to clear WEP
    uint16_t Mem_Write : 1;  //
    uint16_t Mem_Test_Write : 1; 
    uint16_t Mem_Test_Read : 1;
    uint16_t Mem_Read : 1;
    uint16_t Mem_Pointer_Set : 1;
    uint16_t Mem_Erase_Request : 1;
    uint16_t Mem_Erase_Pass : 1;
    uint16_t Mem_Erase : 1;
    uint16_t Mem_All_Sleep : 1;
}MT25QL01_Flag;

///////////////////////////////////////////////////////////////////////////////
extern uint32_t MT25QL01_Seek_bytes_Start_Reference; 
extern uint32_t MT25QL01_Seek_bytes_End_Reference; 

#define Memory_2_bytes MT25QL01_bytes_Max >> 1; 
#define Memory_4_bytes MT25QL01_bytes_Max >> 2; 
#define Memory_8_bytes MT25QL01_bytes_Max >> 3; 
#define Memory_16_bytes MT25QL01_bytes_Max >> 4; 
#define Memory_32_bytes MT25QL01_bytes_Max >> 5; 
#define Memory_64_bytes MT25QL01_bytes_Max >> 6; 
#define Memory_128_bytes MT25QL01_bytes_Max >> 7; 
#define Memory_256_bytes MT25QL01_bytes_Max >> 8; 
#define Memory_512_bytes MT25QL01_bytes_Max >> 9; 
#define Memory_1024_bytes MT25QL01_bytes_Max >> 10;
#define Memory_2048_bytes MT25QL01_bytes_Max >> 11; 
#define Memory_4096_bytes MT25QL01_bytes_Max >> 12;
#define Memory_8192_bytes MT25QL01_bytes_Max >> 13; 
#define Memory_16384_bytes MT25QL01_bytes_Max >> 14;

extern uint8_t Memory_Search_Sequencer; 

//extern struct {
//    uint8_t Memory_Select : 1;
//    uint8_t Memory_2 : 1;
//    uint8_t Memory_4 : 1;
//    uint8_t Memory_8 : 1;

//    uint8_t Memory_16 : 1;
//    uint8_t Memory_32 : 1;
//    
//}MT25QL01_Search_Flag;


extern struct {
  uint8_t Init_State : 1;         
  uint8_t Idle_State : 1; 
  uint8_t Sleep_State : 1; 
  uint8_t Uart_COM_only : 1;   // Save power, COM only
  uint8_t CAN_COM: 1; 
  uint8_t Drill_Init_State : 1; 
  uint8_t Drill_State : 1; 
  uint8_t Drill_125Hz_State : 1; 
  uint8_t Drill_250Hz_State : 1; 
  uint8_t Burst_State : 1; 
  uint8_t Burst_State_Old : 1; 
  uint8_t Burst_State_New : 1; 
  uint8_t Burst_Paused : 1; 
  uint8_t Super_Burst_Rec : 1; 
  uint8_t Super_Burst_Saved : 1;
  uint8_t Burst_Init_State : 1; 
  uint8_t Time_Sync_Set : 1; 
  uint8_t Time_Sync_Processing : 1; 
  uint8_t Mem_Data_Pointer_Seek_Init : 1;
  uint8_t Mem_Data_Pointer_Seek : 1;
  uint8_t Mem_Event_Pointer_Seek : 1;
} State_Flags;