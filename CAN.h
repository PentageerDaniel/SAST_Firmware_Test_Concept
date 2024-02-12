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
 *      CAN.h
 * 
 * @Summary
 *      Bootloader for dspic33CK512MP605
 * 
 ******************************************************************************/

#include "Init.h"

/******************************************************************************
 * Local Function
 ******************************************************************************/
void init_CAN_1(void); 
void CAN_Send_MSG(uint8_t destination, uint8_t *data, uint8_t length); 
void CAN_Received_To_Uart(void); 
void CAN_Decode_Received(void); 
void CAN_Encode_Sending(uint8_t destination, uint8_t command, uint8_t *data, uint16_t data_len); 

int can_rec(char *data); 

/******************************************************************************
 * External Function
 ******************************************************************************/


/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
//#define FCAN    40000000
//#define BITRATE 1000000
//#define NTQ     20  // 20 Time Quanta in a Bit Time
//#define BRP_VAL ( (FCAN / (2 * NTQ * BITRATE)) - 1 )

// CAN Bus FIFO Memory information
#define CAN1_FIFO_ALLOCATE_RAM_SIZE    288U // CAN FIFO allocated ram size based on (number of FIFO x FIFO message Payload size x Message object DLC size)

unsigned int __attribute__((aligned(4)))CanTxBuffer[CAN1_FIFO_ALLOCATE_RAM_SIZE];

/*Data structure to implement a CANFD message buffer. */
/* CANFD Message Time Stamp */
typedef unsigned long CANFD_MSG_TIMESTAMP;

/* CAN TX Message Object Control*/
typedef struct _CANFD_TX_MSGOBJ_CTRL {
    unsigned DLC:4;
    unsigned IDE:1;
    unsigned RTR:1; 
    unsigned BRS:1;
    unsigned FDF:1;
    unsigned ESI:1;
    unsigned SEQ:16; //  unsigned SEQ:23;
    unsigned unimplemented1:16;
} CANFD_TX_MSGOBJ_CTRL;

/* CANFD TX Message ID*/
typedef struct _CANFD_MSGOBJ_ID {
    unsigned SID:11;
    unsigned long EID:18;
    unsigned SID11:1;
    unsigned unimplemented1:2;
} CANFD_MSGOBJ_ID;

/* CAN TX Message Object*/
typedef union _CANFD_TX_MSGOBJ {
    struct {
        CANFD_MSGOBJ_ID id;
        CANFD_TX_MSGOBJ_CTRL ctrl;
        CANFD_MSG_TIMESTAMP timeStamp;
    } bF;
    unsigned int word[4];
    unsigned char byte[64];
} CANFD_TX_MSGOBJ;


//unsigned int __attribute__((aligned(4)))CanRxBuffer[MAX_WORDS];
/*data structure to implement a CANFD message buffer. */

/* CANFD Message Time Stamp */
//typedef unsigned long CANFD_MSG_TIMESTAMP;

/* CANFD RX Message Object Control*/
typedef struct _CANFD_RX_MSGOBJ_CTRL {
    unsigned DLC:4;
    unsigned IDE:1;
    unsigned RTR:1;
    unsigned BRS:1;
    unsigned FDF:1;
    unsigned ESI:1;
    unsigned unimplemented1:2;
    unsigned FilterHit:5;
    unsigned unimplemented2:16;
} CANFD_RX_MSGOBJ_CTRL;

/* CANFD RX Message ID*/


/* CANFD RX Message Object */
typedef union _CANFD_RX_MSGOBJ {
    struct 
    {
        CANFD_MSGOBJ_ID id;
        CANFD_RX_MSGOBJ_CTRL ctrl;
        CANFD_MSG_TIMESTAMP timeStamp;
    } bF;
    unsigned int word[4];
    unsigned char byte[64];  
} CANFD_RX_MSGOBJ;

// CAN TX Message Object
typedef union
{
    struct
    {
        uint16_t sid;
        uint16_t eid;
        uint16_t flags;
        uint16_t unused;
    };
    uint16_t messageWord[4];
} CAN_TxMsgBuffer;

// Can RX Message Object
typedef struct
{
    uint16_t sid;
    uint16_t eid;
    uint16_t flags;
    uint16_t unused;
    uint16_t timeStampL;
    uint16_t timeStampH;
} CAN_RxMsgBuffer;

#define CAN_DSPIC33C_RX_DLC(rxbuffer)  ((rxbuffer)->flags & 0x000F)
#define CAN_DSPIC33C_RX_IDE(rxbuffer)  ((rxbuffer)->flags & 0x0010)
#define CAN_DSPIC33C_RX_RTR(rxbuffer)  ((rxbuffer)->flags & 0x0020)
#define CAN_DSPIC33C_RX_BRS(rxbuffer)  ((rxbuffer)->flags & 0x0040)
#define CAN_DSPIC33C_RX_FDF(rxbuffer)  ((rxbuffer)->flags & 0x0080)
#define CAN_DSPIC33C_RX_SID(rxbuffer)  ((uint32_t)(rxbuffer)->sid & 0x07FF)
#define CAN_DSPIC33C_RX_EIDL(rxbuffer) (((uint32_t)(rxbuffer)->sid & 0xF800) >> 11)
#define CAN_DSPIC33C_RX_EIDH(rxbuffer) ((uint32_t)(rxbuffer)->eid << 5)

// CAN filter Object
#define CAN_filter_SID(idFilter)  ((uint16_t)(idFilter >> 18) & 0x07FF)
#define CAN_filter_EIDL(idFilter) ((uint16_t)(idFilter << 11) & 0xF800)
#define CAN_filter_EIDH(idFilter) ((uint16_t)(idFilter >> 5) & 0x1FFF)

#define CAN_MESSAGE_HEADER_SIZE 6U

typedef enum
{
    CAN_CLK_AFVCO_4 = 0b1010,   ///< AFVCO_4
    CAN_CLK_AFVCO_3 = 0b1001,   ///< AFVCO_3
    CAN_CLK_AFVCO_2 = 0b1000,   ///< AFVCO_2
    CAN_CLK_AFVCO = 0b0111,     ///< AFVCO
    CAN_CLK_AFPLLO = 0b0110,    ///< AFPLLO
    CAN_CLK_FVCO_4 = 0b0101,    ///< FVCO_4
    CAN_CLK_FVCO_3 = 0b0100,    ///< FVCO_3
    CAN_CLK_FVCO_2 = 0b0011,    ///< FVCO_2
    CAN_CLK_FPLLO = 0b0010,     ///< FPLLO
    CAN_CLK_FVCO = 0b0001,      ///< FVCO
    CAN_CLK_NO_CLOCK = 0b0000,  ///< NO_CLOCK
} CAN_CLK;

/*******************************************************************************
 * Global Variable and Constant
 ******************************************************************************/
//extern struct {
//  uint16_t Init_State : 1;         
//  uint16_t Idle_State : 1; 
//  uint16_t Sleep_State : 1; 
//  uint16_t Uart_COM_only : 1;   // Save power, COM only
//  uint16_t CAN_COM: 1; 
//  uint16_t Drill_Init_State : 1; 
//  uint16_t Drill_State : 1; 
//  uint16_t Drill_125Hz_State : 1; 
//  uint16_t Drill_250Hz_State : 1; 
//  uint16_t Burst_State : 1; 
//  uint16_t Time_Sync_Set : 1; 
//  uint16_t Time_Sync_Processing : 1; 
//} State_Flags;

//extern struct State_Flags;

extern struct {
  uint16_t Test_Burst_Out : 1;    
  uint16_t Read_Burst_Out : 1;
  uint16_t Test_Data_Out:1; 
  uint16_t Read_Data_Out:1; 
  uint16_t Accel_HG_Spit_Out:1; 
} Debug_Flags;

extern uint8_t __attribute__((aligned(4)))Buffer_RAM_Before[12288]; // used to work

//uint8_t __attribute__((aligned(2)))BufferRAM[16384]; // nope
//uint8_t __attribute__((aligned))BufferRAM[16384]; // nope
//uint8_t __attribute__((aligned))BufferRAM[16384]; // nope
//uint8_t __attribute__(aligned (4),address(0x8000))BufferRAM[16384]; // error syntax
//uint8_t __attribute__((aligned, packed))BufferRAM[16384]; // nope

//uint8_t __attribute__((aligned(4)))BufferRAM[2048]; // works

extern uint16_t Buffer_Read_Pointer;  // to write to memory

extern uint16_t Pointer_Block_Flash_test; 
extern uint32_t Pointer_Entire_Flash_test;
/*******************************************************************************
 * Memory
 ******************************************************************************/


extern uint8_t MEM_MT25QL01_Read_ID(uint8_t cs_port, uint8_t *buffer);
extern uint8_t MEM_MT25QL01_Enter_Deep_Power_Down(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Release_Deep_Power_Down(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Enter_4_Bytes_Mode(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Get_Status(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Get_Flag(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Read_Freeze_Bit(uint8_t cs_port); 
extern uint8_t MEM_MT25QL01_Write_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length); 
extern void MEM_MT25QL01_Write_Enable(uint8_t cs_port);
extern void MEM_MT25QL01_Write_Disable(uint8_t cs_port); 
extern void MEM_MT25QL01_Init_Read(void);
extern uint8_t MEM_MT25QL01_Reading_Swap(void);
extern uint8_t MEM_MT25QL01_Writing_Swap(void); 
extern void MEM_MT25QL01_Read_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length);
extern void MEM_MT25QL01_End_Read(void); 
extern void MEM_MT25QL01_Erase_Memory_Init(void); 
extern void MEM_MT25QL01_Erase_Memory_Swap(uint8_t memory_to_swap); 
extern uint8_t MEM_MT25QL01_Erase_Memory(uint8_t memory_to_erase);
extern void MEM_MT25QL01_Get_Mem_Write_Pointer(uint8_t *buffer);
extern void MEM_MT25QL01_Set_Mem_Write_Pointer(uint8_t *buffer);
extern void MEM_MT25QL01_Get_Mem_Read_Pointer(uint8_t *buffer);
extern void MEM_MT25QL01_Set_Mem_Read_Pointer(uint8_t *buffer); 
extern uint16_t MEM_MT25QL01_Check_Status_Sleep(uint8_t memory_to_check); 

extern const uint8_t MT25QL01_Number_Max; 
extern uint8_t MT25QL01_In_Used; // show which memory is in 

extern const uint16_t MT25QL01_Sector_Max; // Sector size = 64kB

extern const uint8_t MT25QL01_segment_Max; 
extern uint8_t MT25QL01_segment_pointer; 
extern const uint32_t MT25QL01_bytes_Max;
extern uint32_t MT25QL01_bytes_pointer; 

extern uint8_t MT25QL01_Read_In_Used; // show which memory is in 
extern uint8_t MT25QL01_Read_segment_pointer; 
extern uint32_t MT25QL01_Read_bytes_pointer; 

extern uint8_t MT25QL01_Erase_In_Used; // show which memory is in 
extern uint8_t MT25QL01_To_Erase; // 
extern uint8_t MT25QL01_Erase_segment_pointer; 
extern uint32_t MT25QL01_Erase_bytes_pointer; 

extern void Disabled_All_Sensors(void); 

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


/*******************************************************************************
 * Time
 ******************************************************************************/
extern volatile struct {
  uint8_t year;         // calendar year - 2000
  uint8_t month;        // calendar month, January = 1, February = 2, December = 12
  uint8_t days;         // 0 to 31
  uint8_t hours;        // 0 to 23
  uint8_t minutes;      // 0 to 59
  uint8_t seconds;      // 0 00 59
  uint16_t miliseconds; // 0 to 999
} Time;


/*******************************************************************************
 * Memory event
 ******************************************************************************/
extern uint8_t __attribute__((aligned(4)))MemEveBuf[512];
extern const uint16_t NumberEventMax; // event are 16 bytes
extern uint8_t NumberEventSaved; // event are 16 bytes
extern const uint16_t EventPointerMax; 
extern uint16_t EventPointerBuffer;
extern uint16_t EventPointerWriting;

// 4 memories of 8000 bytes
extern const uint16_t MEM_CY15B064J_64_Slices_Max; 
extern const uint16_t MEM_CY15B064J_bytes_Max;
extern const uint8_t MEM_CY15B064J_Number_Max; 

extern uint8_t MEM_CY15B064J_Write_In_Used; // show which memory is in 
extern uint16_t MEM_CY15B064J_Write_bytes_pointer; 

extern uint8_t MEM_CY15B064J_Read_In_Used; // show which memory is in 
extern uint16_t MEM_CY15B064J_Read_bytes_pointer; 

//extern uint8_t MEM_CY15B064J_Erase_In_Used; // show which memory is in 
//uint32_t MEM_CY15B064J_Erase_bytes_pointer = 0; 


extern uint32_t I2C_Errors_Counter;  

extern volatile struct {
    uint16_t Mem_Overflow : 1;
    uint16_t Mem_Fail : 1;
    uint16_t Mem_Busy : 1;
    uint16_t Mem_WEP : 1;
    uint16_t Mem_Wait_Write : 1;  // wait finish to write to clear WEP
    uint16_t Mem_Write : 1;  //
    uint16_t Mem_Test_Write : 1; 
    uint16_t Mem_Test_Read : 1;
    uint16_t Mem_Read : 1;
    uint16_t Mem_End_Read : 1;
    uint16_t Mem_Pointer_Set : 1;
    uint16_t Mem_Erase_Request : 1;
    uint16_t Mem_Erase_Pass : 1;
    uint16_t Mem_Erase : 1;
    uint16_t Mem_All_Sleep : 1;
}MEM_CY15B064J_Flag;

extern uint8_t ADXL355_SPI_Read_Accel_Device_Register(uint8_t register_to_read); 
extern void ADXL355_SPI_Write_Accel_Device_Register(uint8_t register_address, uint8_t register_value);
extern uint8_t ADXL355_I2C_Read_Register(uint8_t address, uint8_t reg); 

extern uint8_t ADXL373_SPI_Get_Interrupt(void); 
extern uint8_t ADXL373_SPI_Get_Register(uint8_t reg); 


#define	ACC373_DEVID_AD         0x00
#define	ACC373_DEVID_MST        0x01
#define	ACC373_PARTID           0x02
#define	ACC373_REVID            0x03
#define	ACC373_STATUS           0x04
#define	ACC373_STATUS2          0x05
#define	ACC373_XDATA_H          0x08
#define	ACC373_XDATA_L          0x09
#define	ACC373_YDATA_H          0x0A
#define	ACC373_YDATA_L          0x0B
#define	ACC373_ZDATA_H          0x0C
#define	ACC373_ZDATA_L          0x0D
#define	ACC373_MAXPEAK_X_H      0x15 
#define	ACC373_MAXPEAK_X_L      0x16 
#define	ACC373_MAXPEAK_Y_H      0x17 
#define	ACC373_MAXPEAK_Y_L      0x18 
#define	ACC373_MAXPEAK_Z_H      0x19 
#define	ACC373_MAXPEAK_Z_L      0x1A 
#define	ACC373_OFFSET_X         0x20
#define	ACC373_OFFSET_Y         0x21
#define	ACC373_OFFSET_Z         0x22
#define	ACC373_THRESH_ACT_X_H	0x23
#define	ACC373_THRESH_ACT_X_L	0x24
#define	ACC373_THRESH_ACT_Y_H	0x25
#define	ACC373_THRESH_ACT_Y_L	0x26
#define	ACC373_THRESH_ACT_Z_H	0x27
#define	ACC373_THRESH_ACT_Z_L	0x28
#define	ACC373_TIME_ACT         0x29
#define	ACC373_THRESH_INACT_X_H	0x2A
#define	ACC373_THRESH_INACT_X_L	0x2B
#define	ACC373_THRESH_INACT_Y_H	0x2C
#define	ACC373_THRESH_INACT_Y_L	0x2D
#define	ACC373_THRESH_INACT_Z_H	0x2E
#define	ACC373_THRESH_INACT_Z_L	0x2F
#define	ACC373_TIME_INACT_H     0x30
#define	ACC373_TIME_INACT_L     0x31
#define	ACC373_THRESH_ACT2_X_H	0x32
#define	ACC373_THRESH_ACT2_X_L	0x33
#define	ACC373_THRESH_ACT2_Y_H	0x34
#define	ACC373_THRESH_ACT2_Y_L	0x35
#define	ACC373_THRESH_ACT2_Z_H	0x36
#define	ACC373_THRESH_ACT2_Z_L	0x37
#define	ACC373_HPF              0x38
#define	ACC373_FIFO_SAMPLES     0x39 
#define	ACC373_FIFO_CTL         0x3A 
#define	ACC373_INT1_MAP         0x3B
#define	ACC373_INT2_MAP         0x3C
#define	ACC373_TIMING           0x3D
#define	ACC373_MEASURE          0x3E
#define	ACC373_POWER_CTL        0x3F
#define	ACC373_SELF_TEST        0x40
#define	ACC373_RESET            0x41
#define ACC373_FIFO_DATA        0x42

////////////////////////////////////////////////////////////////////////////////

extern uint8_t Time_debug_Flag; 