
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
#include "MEM_MT25QL01.h"


/*******************************************************************************
 * Function: MT25QL01GCBB_Init
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Init(void)
{
    uint8_t buffer[20]; 
    uint8_t memory_error = 0xFF;
    //uint8_t memory_asleep = 0;
    uint8_t status;
    uint8_t i;
    // verified Id
    
    //MEM_MT25QL01_Wake_UP_All_Memory();
    
    
    Start_Timer_3(300);
    while(Check_Timer_3() == 0){}; 
    Stop_Timer_3();

    for(i=1; i<MT25QL01_Number_Max; i++)
    {
        MEM_MT25QL01_Enter_4_Bytes_Mode(i); // Enter 4 byte mode 
            
            
        Start_Timer_3(1250);
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();

        status =  MEM_MT25QL01_Get_Flag(i); // get the flag

        if((status & 0x01) != 0x01) // check is 4 byte mode ON
        {
            memory_error = 1; 
            buffer[0] = 0xEE; 
            buffer[1] = 0x01;
            buffer[2] = 0x02; 
            buffer[3] = i; // put memory index
            CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
            break;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
//    for(i=1; i<21; i++)
//    {
//        status = MEM_MT25QL01_Read_ID(i,buffer);
//    
//        if(buffer[0] == 0x20 && buffer[1] == 0xBA && buffer[2] == 0x21)
//        {
//            memory_error = 0; 
////            buffer[0] = 0xAA; 
////            buffer[1] = 0xBB;
////            buffer[2] = 0x01; 
////            buffer[3] = i; 
////            CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//        }
//        else
//        {
//            if(buffer[0] == 0xFF && buffer[1] == 0xFF && buffer[2] == 0xFF)
//            {
//                // momemy already asleep
//                memory_asleep = 1; 
//            }   
//            else
//            {
//                // error
//                memory_error = 1; 
//                buffer[0] = 0xEE; 
//                buffer[1] = 0x01; 
//                buffer[2] = 0x01; 
//                buffer[3] = i; // put memory index
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//                break; 
//            }
//        }
//        
//        Start_Timer_3(1250);
//        while(Check_Timer_3() == 0){}; 
//        Stop_Timer_3();
//
//        if(memory_error ==  0 && memory_asleep == 0)
//        {
//            MEM_MT25QL01_Enter_4_Bytes_Mode(i); // Enter 4 byte mode 
//            
//            
//            Start_Timer_3(1250);
//            while(Check_Timer_3() == 0){}; 
//            Stop_Timer_3();
//            
//            status =  MEM_MT25QL01_Get_Flag(i); // get the flag
//            
//            if((status & 0x01) != 0x01) // check is 4 byte mode ON
//            {
//                memory_error = 1; 
//                buffer[0] = 0xEE; 
//                buffer[1] = 0x01;
//                buffer[2] = 0x02; 
//                buffer[3] = i; // put memory index
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//                break;
//            }
//        }
//        
//        #ifndef Memory_Data_Sleep_Override
//            if(memory_error ==  0 && memory_asleep == 0)
//            {
//                MEM_MT25QL01_Enter_Deep_Power_Down(i);
//            }
//        #endif
//        
//        Start_Timer_3(1250);
//        while(Check_Timer_3() == 0){}; 
//        Stop_Timer_3();
//    }
//    
//    #ifndef Memory_Data_Sleep_Override
//        MT25QL01_Flag.Mem_All_Sleep = 1; 
//    #endif
//
//    #ifdef CAN_Debug_Message
//        if(memory_error ==  0)
//        {
//            buffer[0] = 0xAA; 
//            buffer[1] = 0xCC;
//            buffer[2] = 0x01; 
//            buffer[3] = 0x01; 
//            CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//        }
//        else
//        {
//            buffer[0] = 0xEE; 
//            buffer[1] = 0x01;
//            buffer[2] = 0x01; 
//            buffer[3] = memory_error; 
//            buffer[4] = status; 
//            CAN_Encode_Sending(0x1B,0xC4, buffer, 5);
//        }
//    #else
//        
//    #endif
//    
//    
    

}

/*******************************************************************************
 * Function: MT25QL01GCBB_Read_ID
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Read_ID(uint8_t cs_port, uint8_t *buffer)
{
    /*
     * Command   = 0x9F
     * Byte 1    = Manufacturer identification = 0x20
     * Byte 2    = Manufacturer ID = 0xBA
     * Byte 3    = Manufacturer ID = 0x21
     * Byte 4    = Remaining byte = 0x10
     * Byte 3    = Extended device ID
     * Byte 3    = Device configuration information = 0x00
     * Byte 7:20 = UID = Unique
     */
    uint8_t status;
    uint8_t cmd_buffer[1];
    cmd_buffer[0] = 0x9F;     // CMD 
    
    //status = SPI_2_Routine_Read(cs_port, cmd_buffer, 1, buffer, 20);
    status = SPI_2_Routine_Read(cs_port, cmd_buffer, 1, buffer, 3);
    return status;
    
}

/*******************************************************************************
 * Function: MT25QL02GCBB_Enter_4_Bytes_Mode
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Enter_4_Bytes_Mode(uint8_t cs_port)
{
    uint8_t status = 0; 
    uint8_t cmd_buffer[1];
    //MT25QL02GCBB_Write_Enable();
    cmd_buffer[0] = 0xB7;     // CMD 
    //SPI_2_Routine(cmd_buffer, 1, 0); 
    SPI_2_Routine(cs_port, cmd_buffer, 1, 0); 
    return status; 
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Enter_Deep_Power_Down
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Enter_Deep_Power_Down(uint8_t cs_port)
{
    uint8_t status = 0; 
    uint8_t cmd_buffer[1];
    //MT25QL02GCBB_Write_Enable();
    cmd_buffer[0] = 0xB9;     // CMD 
    //SPI_2_Routine(cmd_buffer, 1, 0); 
    SPI_2_Routine(cs_port, cmd_buffer, 1, 0); 
    return status; 
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Release_Deep_Power_Down
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Release_Deep_Power_Down(uint8_t cs_port)
{
    uint8_t status = 0; 
    uint8_t cmd_buffer[1];
    //MT25QL02GCBB_Write_Enable();
    cmd_buffer[0] = 0xAB;     // CMD 
    //SPI_2_Routine(cmd_buffer, 1, 0); 
    SPI_2_Routine(cs_port, cmd_buffer, 1, 0); 
    MT25QL01_Flag.Mem_All_Sleep = 0; 
    return status; 
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Get_Status
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Get_Status(uint8_t cs_port)
{
    /* 
     * 7	Status register
     * 6	Protection Area
     * 5	Top/bottom
     * 4	Protection Area
     * 3	Protection Area
     * 2	Protection Area
     * 1	write enable
     * 0	write in progress
     */
    uint8_t status = 0;
    uint8_t cmd_buffer[1];
    uint8_t buffer[1];
    cmd_buffer[0] = 0x05;     // CMD 
    buffer[0] = 0x00;
    //read_SPI_2_Debug(cmd_buffer, 2, 2); 
    //return (SPI_2_Routine(cs_port, cmd_buffer, 1, 1)); 
    status = SPI_2_Routine_Read(cs_port, cmd_buffer, 1, buffer, 1);
    
    return buffer[0];
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Get_Flag
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Get_Flag(uint8_t cs_port)
{
    /*
     * 7	Program
     * 6	Erase suspend
     * 5	Erase
     * 4	Program
     * 3	n/a
     * 2	Program Suspend
     * 1	Protection
     * 0	Addressing 3 or 4
     */
    uint8_t cmd_buffer[1];
    cmd_buffer[0] = 0x70;     // CMD 
    //read_SPI_2_Debug(cmd_buffer, 2, 2); 
    return (SPI_2_Routine(cs_port, cmd_buffer, 1, 1)); 
}

/*******************************************************************************
 * Function: MT25QL02GCBB_Get_Flag
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Read_Freeze_Bit(uint8_t cs_port)
{
    uint8_t cmd_buffer[1];
    cmd_buffer[0] = 0xA7;     // CMD 
    //read_SPI_2_Debug(cmd_buffer, 2, 2); 
    return (SPI_2_Routine(cs_port, cmd_buffer, 1, 1)); 
}

/*******************************************************************************
 * Function: MT25QL02GCBB_Get_Flag
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Writing_Swap(void)
{
    uint8_t status = 0; 
    //Deep power-down tDP == 3us
    // HIGH to standby mode (DPD exit time) tRDP = 30us
    MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_In_Used);
            
    Start_Timer_3(4); // around 3us
    while(Check_Timer_3() == 0){}; 
    Stop_Timer_3();
    
    
    MT25QL01_In_Used++; 
    
    
    if(MT25QL01_In_Used > MT25QL01_Number_Max)
    {
        status = 0xFF; 
    }
    else
    {
        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_In_Used);
        Start_Timer_3(38); // around 30us
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
    }
    
    return status; 
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Get_Status
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Write_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length)
{
    uint8_t i; 
    uint8_t buffer[64] = {0}; 
    uint8_t status_flag;
    
    if(MT25QL01_Flag.Mem_Read == true && MT25QL01_Flag.Mem_Erase == true)
    {
        buffer[0] = 0xEE;   // Error
        buffer[1] = 0x01;   // Memory Error
        buffer[2] = 0x07;   // Read while Write or erase
        buffer[3] = cs_port;// put memory index
        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
        return 0xFF; 
    }
    
    ////////////////////////////////////////////////////
    
    if(MT25QL01_Flag.Mem_Overflow == true)
    {
        // memory overflow do not overwrite for now ?
        return 0xFF; 
    }
    
    ////////////////////////////////////////////////////
    
    MEM_MT25QL01_Write_Enable(cs_port); 
    
    __builtin_nop(); 
    __builtin_nop(); 
    
    ///////////////////////////////////////////////////
    
 
    buffer[0] = 0x12;     // CMD 
    //buffer[1] = MT25QL01_segment_pointer;  
    buffer[1] = (MT25QL01_bytes_pointer & 0xFF000000) >> 24; 
    buffer[2] = (MT25QL01_bytes_pointer & 0xFF0000) >> 16; 
    buffer[3] = (MT25QL01_bytes_pointer & 0xFF00) >> 8; 
    buffer[4] = MT25QL01_bytes_pointer & 0xFF; 
   
    for(i=0; i<length; i++)
    {
        buffer[i+5] = data[i];
    }
    SPI_2_Routine(cs_port, buffer, 5 + length, 0);

    __builtin_nop(); 
    
    ///////////////////////////////////////////////////
    // check status
    while((MEM_MT25QL01_Get_Status(cs_port) & 0x01) == 0x01)
    {
       __builtin_nop();
       __builtin_nop();
       __builtin_nop();
       __builtin_nop();

    }
    ///////////////////////////////////////////////////
    // check Flag
    status_flag = MEM_MT25QL01_Get_Flag(cs_port); 
    if((status_flag & 0x76) >= 0x01)
    {
        // check Erase suspend == 0x40
        // check Erase error == 0x20
        // check program error == 0x10
        // check Program suspend == 0x04
        // check protection error == 0x02
        buffer[0] = 0xEE;   // Error
        buffer[1] = 0x01;   // Memory Error
        buffer[2] = 0x03;   // Flags error writing
        buffer[3] = i;      // put memory index
        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
        return 0xFF; // error
    }
    
    /////////////////////////////////////////////////
    // Write Disable
    MEM_MT25QL01_Write_Disable(cs_port); 
    
    //////////////////////////////////////////////////
    
    MT25QL01_bytes_pointer += length; 
    
    if(MT25QL01_bytes_pointer >= MT25QL01_bytes_Max)
    {
        MT25QL01_bytes_pointer = 0; 
        
        // memory full
            MT25QL01_bytes_pointer = 0; 
            //MT25QL01_In_Used++; 
            if(MEM_MT25QL01_Writing_Swap() > 0)
            {
                MT25QL01_Flag.Mem_Overflow = true; 
                buffer[0] = 0xEE;   // Error
                buffer[1] = 0x01;   // Memory Error
                buffer[2] = 0x03;   // Flags error writing
                buffer[3] = i;      // put memory index
                CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
                return 0xFF; // error
            }
        
//        MT25QL01_segment_pointer++; 
//        if(MT25QL01_segment_pointer >= MT25QL01_segment_Max)
//        {
//            // memory full
//            MT25QL01_segment_pointer = 0; 
//            //MT25QL01_In_Used++; 
//            if(MEM_MT25QL01_Writing_Swap() > 0)
//            {
//                MT25QL01_Flag.Mem_Overflow = true; 
//                buffer[0] = 0xEE;   // Error
//                buffer[1] = 0x01;   // Memory Error
//                buffer[2] = 0x03;   // Flags error writing
//                buffer[3] = i;      // put memory index
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
//                return 0xFF; // error
//            }
//        }
    }
    //__builtin_nop();
    //__builtin_nop();
    return 0; 
}

/*******************************************************************************
 * Function: GD5F2GQ5_Write_Enable
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Write_Enable(uint8_t cs_port)
{
    uint8_t cmd_buffer[1]; 
    cmd_buffer[0] = 0x06; 
    SPI_2_Routine(cs_port, cmd_buffer, 1, 0);
}

/*******************************************************************************
 * Function: GD5F2GQ5_Write_Disable
 * Parameters:
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Write_Disable(uint8_t cs_port)
{
    uint8_t cmd_buffer[1]; 
    cmd_buffer[0] = 0x04; 
    SPI_2_Routine(cs_port, cmd_buffer, 1, 0);
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Get_Mem_Write_Pointer
 * Parameters:
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Get_Mem_Write_Pointer(uint8_t *buffer)
{
    buffer[0] = MT25QL01_In_Used; 
    buffer[1] = MT25QL01_bytes_pointer >> 24; 
    buffer[2] = MT25QL01_bytes_pointer >> 16; 
    buffer[3] = MT25QL01_bytes_pointer >> 8; 
    buffer[4] = MT25QL01_bytes_pointer; 
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Set_Mem_Write_Pointer
 * Parameters:
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Set_Mem_Write_Pointer(uint8_t *buffer)
{
    MT25QL01_In_Used = buffer[0];  
    MT25QL01_bytes_pointer = buffer[1]; 
    MT25QL01_bytes_pointer = MT25QL01_bytes_pointer << 8; 
    MT25QL01_bytes_pointer |= buffer[2];
    MT25QL01_bytes_pointer = MT25QL01_bytes_pointer << 8; 
    MT25QL01_bytes_pointer |= buffer[3];
    MT25QL01_bytes_pointer = MT25QL01_bytes_pointer << 8; 
    MT25QL01_bytes_pointer |= buffer[4];
    
}
/*******************************************************************************
 * Function: MEM_MT25QL01_Get_Mem_Write_Pointer
 * Parameters:
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Get_Mem_Read_Pointer(uint8_t *buffer)
{
    buffer[0] = MT25QL01_Read_In_Used; 
    buffer[1] = MT25QL01_Read_bytes_pointer >> 24; 
    buffer[2] = MT25QL01_Read_bytes_pointer >> 16; 
    buffer[3] = MT25QL01_Read_bytes_pointer >> 8; 
    buffer[4] = MT25QL01_Read_bytes_pointer; 
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Set_Mem_Write_Pointer
 * Parameters:
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Set_Mem_Read_Pointer(uint8_t *buffer)
{
    MT25QL01_Read_In_Used = buffer[0];  
    MT25QL01_Read_bytes_pointer = buffer[1]; 
    MT25QL01_Read_bytes_pointer = MT25QL01_Read_bytes_pointer << 8; 
    MT25QL01_Read_bytes_pointer |= buffer[2];
    MT25QL01_Read_bytes_pointer = MT25QL01_Read_bytes_pointer << 8; 
    MT25QL01_Read_bytes_pointer |= buffer[3];
    MT25QL01_Read_bytes_pointer = MT25QL01_Read_bytes_pointer << 8; 
    MT25QL01_Read_bytes_pointer |= buffer[4];
    
}
/*******************************************************************************
 * Function: MEM_MT25QL01_Init_Read
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Init_Read(void)
{
    MT25QL01_Read_In_Used = 1; 
    //MT25QL01_Read_segment_pointer = 0; 
    MT25QL01_Read_bytes_pointer = 0; 
    
    MEM_MT25QL01_Wake_UP_All_Memory(); 
            
    #ifndef Memory_Data_Sleep_Override
    if(MT25QL01_Flag.Mem_All_Sleep == 1)
    {
        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_Read_In_Used);
    }
    else
    {
        if(MT25QL01_In_Used != 1)
        {
            MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_In_Used);
            Start_Timer_3(4); // around 3us
            while(Check_Timer_3() == 0){}; 
            Stop_Timer_3();

            MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_Read_In_Used); 
            Start_Timer_3(50); // min 30us
            while(Check_Timer_3() == 0){}; 
            Stop_Timer_3();

        }
    }
    #endif

    

    MT25QL01_Flag.Mem_Read = 1; 
    
}
/*******************************************************************************
 * Function: MT25QL02GCBB_Get_Flag
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Reading_Swap(void)
{
    uint8_t status = 0; 
    //Deep power-down tDP == 3us
    // HIGH to standby mode (DPD exit time) tRDP = 30us
    
    #ifndef Memory_Data_Sleep_Override
    MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_Read_In_Used);
            
    Start_Timer_3(4); // around 3us
    while(Check_Timer_3() == 0){}; 
    Stop_Timer_3();
    #endif
    
    MT25QL01_Read_In_Used++; 
    
    #ifndef Memory_Data_Sleep_Override
    if(MT25QL01_Read_In_Used > MT25QL01_Number_Max)
    {
        status = 0xFF; 
    }
    else
    {
        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_Read_In_Used);
        Start_Timer_3(50); // around 30us
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
    }
    #endif
    
    
    return status; 
}
/*******************************************************************************
 * Function: MT25QL02GCBB_Read_Memory
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Read_Bytes(uint8_t cs_port, uint8_t *data, uint8_t length)
{
    //uint32_t i; 
    uint8_t status;
    uint8_t cmd_buffer[5];
    
    //uint8_t buffer[16] = {0}; 
    //uint8_t status_flag;

    ////////////////////////////////////////////////////
    
    if(MT25QL01_Flag.Mem_Write == true && MT25QL01_Flag.Mem_Erase == true)
    {
        cmd_buffer[0] = 0xEE;   // Error
        cmd_buffer[1] = 0x01;   // Memory Error
        cmd_buffer[2] = 0x06;   // Read while Write or erase
        cmd_buffer[3] = cs_port;// put memory index
        CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 4);
        return; 
    }

    ///////////////////////////////////////////////////

    cmd_buffer[0] = 0x13;     // CMD 
    cmd_buffer[1] = (MT25QL01_Read_bytes_pointer & 0xFF000000) >> 24; 
    cmd_buffer[2] = (MT25QL01_Read_bytes_pointer & 0xFF0000) >> 16; 
    cmd_buffer[3] = (MT25QL01_Read_bytes_pointer & 0xFF00) >> 8; 
    cmd_buffer[4] = MT25QL01_Read_bytes_pointer & 0xFF; 
   
     // CMD 
    status = SPI_2_Routine_Read(cs_port, cmd_buffer, 5, data, length);

    __builtin_nop(); 
    __builtin_nop();

    
    MT25QL01_Read_bytes_pointer += length; 
    
    if(MT25QL01_Read_bytes_pointer >= MT25QL01_bytes_Max)
    {
        MT25QL01_Read_bytes_pointer = 0; 
        //MT25QL01_Read_segment_pointer++; 
        //MT25QL01_Read_segment_pointer = 0; 
        //MT25QL01_Read_In_Used++; 
        if(MEM_MT25QL01_Reading_Swap() > 0)
        {
            // read all memories - Game over
            cmd_buffer[0] = 0xA0;   // 
            cmd_buffer[1] = 0x04;   // 
            cmd_buffer[2] = 0x44; // D
            cmd_buffer[3] = 0x4F; // O
            cmd_buffer[4] = 0x4E; // N
            cmd_buffer[5] = 0x45; // E
            CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 6); 
            MT25QL01_Flag.Mem_Read = 0; 
        }
    }

}
/*******************************************************************************
 * Function: MEM_MT25QL01_End_Read
 * Parameters: command
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_End_Read(void)
{
    #ifndef Memory_Data_Sleep_Override
    if(MT25QL01_In_Used != MT25QL01_Read_In_Used)
    {
        MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_Read_In_Used);
        Start_Timer_3(4); // around 3us
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
        
        MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_In_Used); 
        Start_Timer_3(50); // min 30us
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
        
    }
    #endif
    
    MT25QL01_Flag.Mem_Read = 0; 
    MT25QL01_Read_bytes_pointer = 0; 
}
/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Erase_Memory_Init(void)
{
    MT25QL01_Erase_In_Used = 1; 
    //MT25QL01_Erase_segment_pointer = 0; 
    MT25QL01_Erase_bytes_pointer = 0; 
   
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Erase_Memory_Swap(uint8_t memory_to_swap)
{
    #ifndef Memory_Data_Sleep_Override
    if(MT25QL01_Erase_In_Used != memory_to_swap)
    {
        MEM_MT25QL01_Enter_Deep_Power_Down(MT25QL01_Erase_In_Used);
        Start_Timer_3(4); // around 3us
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
        
        MEM_MT25QL01_Release_Deep_Power_Down(memory_to_swap); 
        Start_Timer_3(50); // min 30us
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
        
        //memory_to_swap = MT25QL01_Erase_In_Used; 
        MT25QL01_Erase_In_Used = memory_to_swap; 
    }
    #endif
}

/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
uint8_t MEM_MT25QL01_Erase_Memory(uint8_t memory_to_erase)
{
    // sector size 64kB
    uint16_t i; // MT25QL02GCBB_Sub_Sector
//    uint8_t j;
    uint8_t buffer[20];
    uint8_t status_flag = 0;  
    uint8_t error = 0;  
    uint16_t tempo16 = 0;
    //MT25QL01_Erase_segment_pointer = 0; 
    MT25QL01_Erase_bytes_pointer = 0; 
    
    ////////////////////////////////////////////////////////////////////////////
    if(MT25QL01_Flag.Mem_Write == true || MT25QL01_Flag.Mem_Read == true)
    {
        buffer[0] = 0xEE;   // Error
        buffer[1] = 0x01;   // Memory Error
        buffer[2] = 0x08;   // Read while Write or erase
        buffer[3] = memory_to_erase;// put memory index
        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
        return 0xFF; 
    }
    
    tempo16 = MEM_MT25QL01_Check_Status_Sleep(memory_to_erase);
    if(tempo16 == 0xDEAD)
    {
        MEM_MT25QL01_Release_Deep_Power_Down(memory_to_erase); 
        Start_Timer_3(300);
        while(Check_Timer_3() == 0){}; 
        Stop_Timer_3();
    }

    ////////////////////////////////////////////////////////////////////////////
    #ifndef Memory_Data_Sleep_Override
    if(MT25QL01_Flag.Mem_All_Sleep == 1)
    {
        MEM_MT25QL01_Release_Deep_Power_Down(memory_to_erase); 
    }
    else
    {
        MEM_MT25QL01_Erase_Memory_Swap(memory_to_erase);
    }
    ////////////////////////////////////////////////////////////////////////////
    // Make memory is really awake!
    status_flag = MEM_MT25QL01_Read_ID(memory_to_erase,buffer);
    
    if(buffer[0] == 0x20 && buffer[1] == 0xBA && buffer[2] == 0x21)
    {
        CAN_Encode_Sending(0x1B,0xC4, buffer, 20);
    }
    else
    {
        // memory not awake
        buffer[0] = 0xEE;
        buffer[1] = 0x09;    
        buffer[2] = status_flag;
        buffer[3] = memory_to_erase;
        CAN_Encode_Sending(0x1B,0xC4, buffer, 5); 
        return 0xFF; 
    }
    #endif
    ////////////////////////////////////////////////////////////////////////////
    //MEM_MT25QL01_Write_Enable(memory_to_erase);
    
    ////////////////////////////////////////////////////////////////////////////
    for(i=0; i<MT25QL01_Sector_Max; i++)
    {
        MEM_MT25QL01_Write_Enable(memory_to_erase); 

        __builtin_nop();
        __builtin_nop();

        buffer[0] = 0xDC;     // CMD 4-BYTE SECTOR ERASE
        buffer[1] = (MT25QL01_Erase_bytes_pointer & 0xFF000000) >> 24;  
        buffer[2] = (MT25QL01_Erase_bytes_pointer & 0xFF0000) >> 16;  
        buffer[3] = (MT25QL01_Erase_bytes_pointer & 0x00FF00) >> 8;
        buffer[4] = MT25QL01_Erase_bytes_pointer & 0xFF; 

        SPI_2_Routine(memory_to_erase, buffer, 5, 0); 

        __builtin_nop();
        __builtin_nop();

       ///////////////////////////////////////////////////////////////////
        //Start_Timer_3(1500000); // ~ 1.2 Sec
        while((MEM_MT25QL01_Get_Status(memory_to_erase) & 0x01) == 0x01)
        {
            __builtin_nop();
            __builtin_nop();
            __builtin_nop();
            __builtin_nop();
//            if(Check_Timer_3() == 1) // timeout ?
//            {
//                error = 0xFF;  
//                buffer[0] = 0xEE;
//                buffer[1] = 0x01;   
//                buffer[2] = 0x0A;  
//                buffer[3] = status_flag;
//                buffer[4] = (i & 0xFF00) >> 8;
//                buffer[5] = i & 0x00FF;
//                CAN_Encode_Sending(0x1B,0xC4, buffer, 6); 
//                MEM_MT25QL01_Write_Disable(memory_to_erase); 
//                return 0xFF; 
//            }

        }
        //Stop_Timer_3(); 
        
        __builtin_nop();
        __builtin_nop();

        ///////////////////////////////////////////////////////////////
        // check Flag
        status_flag = MEM_MT25QL01_Get_Flag(memory_to_erase); 
        if((status_flag & 0x76) >= 0x01)
        {
            // check Erase suspend == 0x40
            // check Erase error == 0x20
            // check program error == 0x10
            // check Program suspend == 0x04
            // check protection error == 0x02
            error = 0xFF;  
            buffer[0] = 0xEE;
            buffer[1] = 0x05;    
            buffer[2] = status_flag;
            buffer[3] = memory_to_erase;
            CAN_Encode_Sending(0x1B,0xC4, buffer, 4); 
            MEM_MT25QL01_Write_Disable(memory_to_erase);
            __builtin_nop();
            __builtin_nop();
            break; 
        }
        else
        {
            if((i >= 64) && (i % 64 == 0))
            {
                buffer[0] = 0xA0;
                buffer[1] = 0x03;  
                buffer[2] = memory_to_erase; 
                buffer[3] = (i & 0xFF00) >> 8;
                buffer[4] = i & 0x00FF;
                buffer[5] = 0xAC; // ok
                buffer[6] = 0xED; 
      
                CAN_Encode_Sending(0x1B,0xC4, buffer, 7); 
            }
            
            

        
            MT25QL01_Erase_bytes_pointer += 64000; // sub sector 64kB

            if(MT25QL01_Erase_bytes_pointer >= MT25QL01_bytes_Max)
            {
                MT25QL01_Erase_bytes_pointer = 0; 
                //break; 
                
                //MT25QL01_Erase_segment_pointer++; 
//                if(MT25QL01_Erase_segment_pointer >= MT25QL01_segment_Max)
//                {
//                    // done
//                    //i = MT25QL01_Sector_Max + 1; 
//                }

            }
        }


        ///////////////////////////////////////////////////////////////      
        
        MEM_MT25QL01_Write_Disable(memory_to_erase);
        __builtin_nop();
        __builtin_nop();

    }
    
    //////////////////////////////////////////////////////////////////////////// 
    //MEM_MT25QL01_Write_Disable(memory_to_erase); 
    
    ////////////////////////////////////////////////////////////////////////////
    MT25QL01_Flag.Mem_Erase = 0; 
    
    if(error == 0)
    {
        buffer[0] = 0xA0;
        buffer[1] = 0x02;  
        buffer[2] = memory_to_erase; 
        buffer[3] = 0xAC; // ok
        buffer[4] = 0xED; 
      
        CAN_Encode_Sending(0x1B,0xC4, buffer, 5); 
    }
    else
    {
        error = 0xFF;  
        buffer[0] = 0xEE;
        buffer[1] = 0x05;    
        buffer[2] = status_flag;
        buffer[3] = memory_to_erase;
        CAN_Encode_Sending(0x1B,0xC4, buffer, 5); 
        MEM_MT25QL01_Write_Disable(memory_to_erase); 
    }
    
    return error; 
    
  
     //MEM_MT25QL01_Write_Disable(); 
    
    //buffer[0] = 0xEF;
    //buffer[1] = 0xFA;  
    //buffer[2] = 0xCE;
    //uart_1_send_message_timed(0xCA, buffer, 3); 
}


/*******************************************************************************
 * Function: 
 * Parameters: 
 * Return: 
 * Description: 
 ******************************************************************************/
void MEM_MT25QL01_Pointer_Seaching(void)
{
    uint8_t cmd_buffer[13];
    uint8_t data[1];
    uint8_t status;
    uint16_t tempo16;

    if(State_Flags.Mem_Data_Pointer_Seek_Init == 0)
    {
        State_Flags.Mem_Data_Pointer_Seek_Init = 1; 
        MT25QL01_Seek_In_Used = 1; 
        MT25QL01_Seek_bytes_pointer = 0; 
        MT25QL01_Seek_bytes_Start_Reference = 0; 
        MT25QL01_Seek_bytes_End_Reference = MT25QL01_bytes_Max; 
        
        tempo16 = MEM_MT25QL01_Check_Status_Sleep(MT25QL01_Seek_In_Used);
        if(tempo16 == 0xDEAD)
        {
            MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_Seek_In_Used); 
            Start_Timer_3(300);
            while(Check_Timer_3() == 0){}; 
            Stop_Timer_3();
        }
    }
    
    
    
    cmd_buffer[0] = 0x13;     // CMD 
    cmd_buffer[1] = (MT25QL01_Seek_bytes_pointer & 0xFF000000) >> 24; 
    cmd_buffer[2] = (MT25QL01_Seek_bytes_pointer & 0xFF0000) >> 16; 
    cmd_buffer[3] = (MT25QL01_Seek_bytes_pointer & 0xFF00) >> 8; 
    cmd_buffer[4] = MT25QL01_Seek_bytes_pointer & 0xFF; 

     // CMD 
    status = SPI_2_Routine_Read(MT25QL01_Seek_In_Used, cmd_buffer, 5, data, 1);
    
    
    switch(Memory_Search_Sequencer)
    {
        
        case 0 :
            // find each memory have no data by checking first byte of each 
            // memory
            if(data[0] == 0xFF)
            {
                if(MT25QL01_Seek_In_Used == 1)
                {
                    // all memory mostly empty
                    cmd_buffer[0] = 0xCA;   // 
                    cmd_buffer[1] = 0xFE;   // 
                    cmd_buffer[2] = 0x01; // 
                    CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 

                    MT25QL01_In_Used = MT25QL01_Seek_In_Used; // show which memory is in
                    MT25QL01_bytes_pointer = MT25QL01_Seek_bytes_pointer; 

                    State_Flags.Mem_Data_Pointer_Seek = 0; 
                    
//                    #ifndef Memory_Data_Sleep_Override
//                        MEM_MT25QL01_Set_Sleep_Unused_ATM(MT25QL01_In_Used);
//                    #endif
                    return; 
                }
                else
                {
                    // this memory is not written, so pointer must be on
                    MT25QL01_Seek_In_Used--;   
                    tempo16 = MEM_MT25QL01_Check_Status_Sleep(MT25QL01_Seek_In_Used);
                    if(tempo16 == 0xDEAD)
                    {
                        MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_Seek_In_Used); 
                        Start_Timer_3(300);
                        while(Check_Timer_3() == 0){}; 
                        Stop_Timer_3();
                    }
                    Memory_Search_Sequencer++;
//                    cmd_buffer[0] = 0xA1;   // 
//                    cmd_buffer[1] = 0x01;   // 
//                    cmd_buffer[2] = MT25QL01_Seek_In_Used; // 
//                    CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
                    MT25QL01_Seek_bytes_pointer = Memory_2_bytes; 
                    
//                    cmd_buffer[0] = 0x01; 
//                    cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                    cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                    cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                    cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                    cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                    cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                    cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                    cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                    cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                    cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                    cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                    cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                    CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                }
                
                
            }
            else
            {
                MT25QL01_Seek_In_Used++; // check next memory
                tempo16 = MEM_MT25QL01_Check_Status_Sleep(MT25QL01_Seek_In_Used);
                if(tempo16 == 0xDEAD)
                {
                    MEM_MT25QL01_Release_Deep_Power_Down(MT25QL01_Seek_In_Used); 
                    Start_Timer_3(300);
                    while(Check_Timer_3() == 0){}; 
                    Stop_Timer_3();
                }
            }
            
            
            break;
        ////////////////////////////////////////////////////////////////////////
        case 1:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_4_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_2_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x11; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference = Memory_2_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_4_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x12; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;
        ////////////////////////////////////////////////////////////////////////
        case 2:
           if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_8_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_4_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x21; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_4_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_8_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x22; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;
        ////////////////////////////////////////////////////////////////////////
        case 3:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_16_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_8_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x31; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13);  
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_8_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_16_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x32; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13);  
            }
            Memory_Search_Sequencer++;
            break; 
        ////////////////////////////////////////////////////////////////////////
        case 4:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_32_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_16_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x41; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_16_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_32_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x42; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;    
        ////////////////////////////////////////////////////////////////////////
        case 5:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_64_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_32_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x51; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_32_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_64_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x52; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;    
        ////////////////////////////////////////////////////////////////////////
        case 6:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_128_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_64_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x61; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_64_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_128_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x62; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;    
        ////////////////////////////////////////////////////////////////////////
        case 7:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_256_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_128_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x71; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13);  
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_128_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_256_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x72; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;  
        ////////////////////////////////////////////////////////////////////////
        case 8:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_512_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_256_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x81; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_256_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_512_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x82; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break;
        ////////////////////////////////////////////////////////////////////////
        case 9:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_1024_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_512_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x91; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_512_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_1024_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0x92; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break; 
        ////////////////////////////////////////////////////////////////////////
        case 10:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_2048_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_1024_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xA1; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_1024_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_2048_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xA2; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break; 
        ////////////////////////////////////////////////////////////////////////
        case 11:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_4096_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_2048_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xB1; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_2048_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_4096_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xB2; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13);  
            }
            Memory_Search_Sequencer++;
            break; 
        ////////////////////////////////////////////////////////////////////////
        case 12:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_8192_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_4096_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xC1; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_4096_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_8192_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x02;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xC2; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break; 
        ////////////////////////////////////////////////////////////////////////
        case 13:
            if(data[0] == 0xFF)
            {
                MT25QL01_Seek_bytes_Start_Reference = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_16384_bytes;
                MT25QL01_Seek_bytes_End_Reference -= Memory_8192_bytes;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x0D;   // 
//                cmd_buffer[2] = 0x01; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
//                cmd_buffer[0] = 0xD1; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
                
            }
            else
            {
                MT25QL01_Seek_bytes_Start_Reference += Memory_8192_bytes;
                MT25QL01_Seek_bytes_pointer = MT25QL01_Seek_bytes_Start_Reference;
                MT25QL01_Seek_bytes_pointer += Memory_16384_bytes;
                MT25QL01_Seek_bytes_End_Reference = MT25QL01_Seek_bytes_End_Reference;;
//                cmd_buffer[0] = 0xA1;   // 
//                cmd_buffer[1] = 0x0D;   // 
//                cmd_buffer[2] = 0x02; // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
                
//                cmd_buffer[0] = 0xD2; 
//                cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//                cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//                cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//                cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//                cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//                cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//                cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//                cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//                cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//                cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//                cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//                cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 
            }
            Memory_Search_Sequencer++;
            break; 
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        // Scan all the reminding bytes
        case 14:
        {
            if(data[0] == 0xFF)
            {
                //cafe
                cmd_buffer[0] = 0xCA;   // 
                cmd_buffer[1] = 0xFE;   // 
                cmd_buffer[2] = 0x01; // 
                CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 

                MT25QL01_In_Used = MT25QL01_Seek_In_Used; // show which memory is in
                MT25QL01_bytes_pointer = MT25QL01_Seek_bytes_pointer; 

                State_Flags.Mem_Data_Pointer_Seek = 0; 
                Memory_Search_Sequencer = 0; 
                
//                #ifndef Memory_Data_Sleep_Override
//                MEM_MT25QL01_Set_Sleep_Unused_ATM(MT25QL01_In_Used);
//                #endif
                return; 
            }

            MT25QL01_Seek_bytes_pointer += 64; 
            
//            cmd_buffer[0] = 0xE0; 
//            cmd_buffer[1] = MT25QL01_Seek_bytes_pointer>>24;   // 
//            cmd_buffer[2] = MT25QL01_Seek_bytes_pointer>>16;   // 
//            cmd_buffer[3] = MT25QL01_Seek_bytes_pointer>>8;   // 
//            cmd_buffer[4] = MT25QL01_Seek_bytes_pointer;   // 
//            cmd_buffer[5] = MT25QL01_Seek_bytes_Start_Reference>>24;   // 
//            cmd_buffer[6] = MT25QL01_Seek_bytes_Start_Reference>>16;   // 
//            cmd_buffer[7] = MT25QL01_Seek_bytes_Start_Reference>>8;   // 
//            cmd_buffer[8] = MT25QL01_Seek_bytes_Start_Reference;   // 
//            cmd_buffer[9] = MT25QL01_Seek_bytes_End_Reference>>24;   // 
//            cmd_buffer[10] = MT25QL01_Seek_bytes_End_Reference>>16;   // 
//            cmd_buffer[11] = MT25QL01_Seek_bytes_End_Reference>>8;   // 
//            cmd_buffer[12] = MT25QL01_Seek_bytes_End_Reference;   // 
//            CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 13); 

            if(MT25QL01_Seek_bytes_pointer >= MT25QL01_Seek_bytes_End_Reference)
            {
                if(MT25QL01_Seek_bytes_End_Reference == MT25QL01_bytes_Max)
                {
                    //cafe
                    cmd_buffer[0] = 0xCA;   // 
                    cmd_buffer[1] = 0xFE;   // 
                    cmd_buffer[2] = 0x01; // 
                    CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 

                    if(MT25QL01_Seek_In_Used < MT25QL01_Number_Max)
                    {
                        MT25QL01_In_Used = (MT25QL01_Seek_In_Used + 1); // show which memory is in
                        MT25QL01_bytes_pointer = MT25QL01_Seek_bytes_pointer; 

                        State_Flags.Mem_Data_Pointer_Seek = 0; 
                        Memory_Search_Sequencer = 0; 
//                        cmd_buffer[0] = 0xEE;   // 
//                        cmd_buffer[1] = 0x0C;   // 
//                        cmd_buffer[2] = 0x00; // 
//                        CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
                        return; 
                    }
                    else
                    {
                        // all memory full
                        cmd_buffer[0] = 0xEE;   // 
                        cmd_buffer[1] = 0x04;   // 
                        cmd_buffer[2] = 0x00; // 
                        CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
                    }
                }
                else
                {
                    // cannot find pointer where it is to start writing
                    cmd_buffer[0] = 0xEE;   // 
                    cmd_buffer[1] = 0x0B;   // 
                    cmd_buffer[2] = 0x00; // 
                    CAN_Encode_Sending(0x1B,0xC4, cmd_buffer, 3); 
                }
            }
        }
    }

}

/*******************************************************************************
 * Function: MEM_MT25QL01_Check_Status_Sleep
 * Parameters: 
 * Return: CAFE (memory awake) or DEAD (memory asleep)
 * Description: 
 ******************************************************************************/
uint16_t MEM_MT25QL01_Check_Status_Sleep(uint8_t memory_to_check)
{
    uint8_t buffer[20]; 
    uint8_t status;

    // verified Id
    // 20 BA 21 10 44 00 1C C7 0E 00 11 0E 00 23 00 3A 88 B7 DC 2B
    // 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19
 
    status = MEM_MT25QL01_Read_ID(memory_to_check,buffer);
    
    if(buffer[0] == 0x20 && buffer[1] == 0xBA && (buffer[2] == 0x21 || buffer[2] == 0x22))
    {
//        buffer[0] = 0xC0; 
//        buffer[1] = 0xDE; 
//        buffer[2] = 0x00; 
//        buffer[3] = 0x02; 
//        buffer[4] = 0xDE; 
//        buffer[5] = 0xAD; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
        return 0xCAFE; 

    }   
    else
    {
        //if((buffer[0] == 0xFF && buffer[1] == 0xFF) || buffer[0] == 0x00 && buffer[1] == 0x00))
//        buffer[0] = 0xC0; 
//        buffer[1] = 0xDE; 
//        buffer[2] = 0x00; 
//        buffer[3] = 0x02; 
//        buffer[4] = 0xDE; 
//        buffer[5] = 0xAD; 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 4);
        return 0xDEAD; 
    }
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Set_Sleep_Unused_ATM
 * Parameters: memory_in_used
 * Return: none
 * Description: put unused memory to sleep 
 ******************************************************************************/
void MEM_MT25QL01_Set_Sleep_Unused_ATM(uint8_t memory_in_used)
{
    uint8_t buffer[20]; 
    //uint8_t memory_error = 0xFF;
    //uint8_t memory_asleep = 0;
    //uint8_t status;
    uint8_t i;
    // verified Id
    
    //Start_Timer_3(300);
    //while(Check_Timer_3() == 0){}; 
    //Stop_Timer_3();

    for(i=1; i<21; i++)
    {
        if(i != memory_in_used)
        {
            MEM_MT25QL01_Enter_Deep_Power_Down(i);
        }
        
        //Start_Timer_3(50);
        //while(Check_Timer_3() == 0){}; 
        //Stop_Timer_3();
    }
    
    buffer[0] = 0xC0;   // 
    buffer[1] = 0xDE;   // 
    buffer[2] = 0x00; // 
    buffer[3] = 0x03; // 
    CAN_Encode_Sending(0x1B,0xC4, buffer, 4); 
    
    
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Wake_UP_All_Memory
 * Parameters: memory_in_used
 * Return: none
 * Description: put unused memory to sleep 
 ******************************************************************************/
void MEM_MT25QL01_Wake_UP_All_Memory(void)
{
    uint8_t buffer[20]; 
    //uint8_t memory_error = 0xFF;
    //uint8_t memory_asleep = 0;
    //uint8_t status;
    uint8_t i;
    uint16_t tempo16 = 0; 

    for(i=1; i<MT25QL01_Number_Max; i++)
    {
        tempo16 = MEM_MT25QL01_Check_Status_Sleep(i);
        if(tempo16 == 0xDEAD)
        {
            MEM_MT25QL01_Release_Deep_Power_Down(i); 
            
        }
        
        //Start_Timer_3(50);
        //while(Check_Timer_3() == 0){}; 
        //Stop_Timer_3();
    }
    
    Start_Timer_3(300);
    while(Check_Timer_3() == 0){}; 
    Stop_Timer_3();
            
//    #ifdef CAN_Debug_Message
//        buffer[0] = 0xC0;   // 
//        buffer[1] = 0xDE;   // 
//        buffer[2] = 0x00; // 
//        buffer[3] = 0x04; // 
//        CAN_Encode_Sending(0x1B,0xC4, buffer, 4); 
//    #endif
}

/*******************************************************************************
 * Function: MEM_MT25QL01_Shutdowm_All_Memory
 * Parameters: memory_in_used
 * Return: none
 * Description: put unused memory to sleep 
 ******************************************************************************/
void MEM_MT25QL01_Shutdowm_All_Memory(void)
{
    uint8_t buffer[20]; 
    //uint8_t memory_error = 0xFF;
    //uint8_t memory_asleep = 0;
    //uint8_t status;
    uint8_t i;
    uint16_t tempo16 = 0; 

    for(i=1; i<(MT25QL01_Number_Max+1); i++)
    {
        tempo16 = MEM_MT25QL01_Check_Status_Sleep(i);
        if(tempo16 == 0xCAFE)
        {
            MEM_MT25QL01_Enter_Deep_Power_Down(i);
        }
        
        //Start_Timer_3(50);
        //while(Check_Timer_3() == 0){}; 
        //Stop_Timer_3();
    }
    
    Start_Timer_3(300);
    while(Check_Timer_3() == 0){}; 
    Stop_Timer_3();
            
    
    buffer[0] = 0xC0;   // 
    buffer[1] = 0xDE;   // 
    buffer[2] = 0x00; // 
    buffer[3] = 0x05; // 
    CAN_Encode_Sending(0x1B,0xC4, buffer, 4); 
}