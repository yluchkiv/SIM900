
#include "i2c.h"
#include "SSD1306.h"
#include "myserial.h"
#include "ring_buff.h"

char buffer[BUFFER_SIZE+1] = {'\0'};    //buffer filled with NUL 
int buffer_data_available = 0;          // the value that monitors how many cells are occupied and\or how many cells have beed read off                                             
static int read_index = 0;  //index for reading from the cell
static int write_index = 0;  //index for placing into the cell

bool write_into_buffer(void)
{
    if(buffer_data_available == BUFFER_SIZE)
    {
        return false;                     // if buff is full, quit the function
    }

    buffer[write_index] = USART_Receive(); // if USART resulr successfully assigned to buff cell
    write_index++;                    
    buffer_data_available++;     

    if(write_index == BUFFER_SIZE)
    {
        write_index = 0;
    }    
    
    return true;
}

bool read_from_buffer(void)
{
    if(buffer_data_available == 0) 
    {            
        return false; // at first need to check if the buffer in not empty
    }   

    else // we call the function and assign the result to the cell in buffer 
    {

        read_index++;                        // move the index to the next cell to read from
        buffer_data_available--;
        
        if(read_index == BUFFER_SIZE)
        {
            read_index = 0; // when the read pos reaches end of buffer, reset index to 0
        }   

        OLED_SetCursor(1,0);
        OLED_Printf("Buff data:\n %s",buffer);
    }
    return true;                                 
}

void buffer_reset(void)
{
    memset(buffer, 0, BUFFER_SIZE); //flush the buffer
    write_index = 0;
    read_index = 0;
    buffer_data_available = 0;
}

bool checker(void)
{
    for (int i = 0; i < strlen(buffer);i++)
    {
       if((buffer[i]=='O')&&(buffer[i+1]=='K'))
        {
            OLED_SetCursor(7,0);
            OLED_Printf("Checker OK");
            return true;
        }
        else if((buffer[i]=='E')&&(buffer[i+1]=='R'))
        {
            OLED_SetCursor(7,0);
            OLED_Printf("Checker Error"); 
            return false;
        }

    }
    return true;
}
