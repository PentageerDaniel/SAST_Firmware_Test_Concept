/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    ADXL355.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include "init.h"


/*******************************************************************************
 * Function declaration access externally
 ******************************************************************************/
void ADXL373_SPI_Init(void);
void ADXL373_SPI_Init_Wake_Up_Mode(void); 
uint8_t ADXL373_SPI_ID(uint8_t cs_port);
void ADXL373_SPI_Start_Sensor(void);
void ADXL373_SPI_Stop_Sensor(void);
void ADXL373_Shift_Data(uint8_t *input, uint8_t *output); 
uint8_t ADXL373_SPI_Get_Data(uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len); 
void ADXL373_SPI_Check_Level(const uint8_t *buffer); 
uint8_t ADXL373_SPI_Get_Interrupt(void);
void ADXL373_SPI_Get_Max_Peak(void); 
uint8_t ADXL373_SPI_Get_Register(uint8_t reg);
uint8_t ADXL373_Read_Fifo(void); 
/*******************************************************************************
 * internal Function declaration
 ******************************************************************************/
extern uint8_t SPI_2_Routine(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t data_len);
extern uint8_t SPI_2_Routine_Read(uint8_t cs_port, uint8_t *cmd, uint8_t cmd_len, uint8_t *buffer, uint8_t data_len);
extern void Save_Event_Buffer(uint8_t packetID, uint8_t event, uint8_t *data); 
extern void Save_Event_Cmd_Buffer(uint8_t packetID, uint8_t event); 

extern int32_t Multiplication(int x, int y); 
/*******************************************************************************
 * external Function declaration
 ******************************************************************************/

extern uint8_t Accel_HG_Max_Peak[5];

//extern uint8_t __attribute__((aligned(4)))SuperBurst[1024];

//extern const uint16_t SuperBurst_Pointer_Max;
//extern uint16_t SuperBurst_Pointer;

//extern uint8_t ADXL373_FIFO[42]; 

extern struct {
  uint16_t Test_Burst_Out : 1;    
  uint16_t Read_Burst_Out : 1;
  uint16_t Test_Data_Out:1; 
  uint16_t Read_Data_Out:1; 
  uint16_t Accel_HG_Spit_Out:1; 
} Debug_Flags;

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

#define BURST_TRIGGER_SAMPLE_TIME 4 // 1 ms step
extern uint8_t Burst_Trigger_Sample_Counter; 

//extern union
//{
//    struct 
//    {
//        uint8_t Level_25g : 1;
//        uint8_t Level_50g : 1;
//        uint8_t Level_75g : 1;
//        uint8_t Level_100g : 1;
//        uint8_t Level_150g : 1;
//        uint8_t Level_200g : 1;
//        uint8_t Level_250g : 1;
//        uint8_t Level_300g : 1;
//        uint8_t Level_350g : 1;
//        uint8_t Level_400g : 1;
//    };
//    uint8_t All_Level_Flags;
//    
//}Burst_Flag;

extern struct 
{
    uint8_t Level_25g : 1;
    uint8_t Level_50g : 1;
    uint8_t Level_75g : 1;
    uint8_t Level_100g : 1;
    uint8_t Level_150g : 1;
    uint8_t Level_200g : 1;
    uint8_t Level_250g : 1;
    uint8_t Level_300g : 1;
    uint8_t Level_350g : 1;
    uint8_t Level_400g : 1;
}Burst_Flag;
/*******************************************************************************
 * definition
 ******************************************************************************/
#define Shock_Threshold         375      // 375*.2 = 75g

#define FIFO_SIZE               7       // Number sample per axis
#define FIFO_SIZE_3X            42      // 3 x FIFO_SIZE


#define	ACC373_DEVID_AD         0x00
#define	ACC373_DEVID_MST        0x01
#define	ACC373_PARTID           0x02
#define	ACC373_REVID            0x03
#define	ACC373_STATUS           0x04
#define	ACC373_STATUS2          0x05
#define	ACC373_FIFO_ENTRIES2    0x06
#define	ACC373_FIFO_ENTRIES     0x07
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

//

