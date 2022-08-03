#include "i2c.h"
#include "sim900.h"
#include "myserial.h"
#include "ring_buff.h"
#include <util/delay.h>
#include "SSD1306.h"


extern char buffer[BUFFER_SIZE+1];


// void power_on(void)
// {

// }

bool stat_check(void)
{
    USART_Transmit_String("AT\r");
    _delay_ms(2000);
    if(checker())
    {
        return true;
    }
    else
    {
        return false;

    }
}

bool sim_check(void)
{
    buffer_reset();
    USART_Transmit_String("AT+CPIN?\r");
    _delay_ms(2000);
    if(checker())
    {
        return true;
    }
    else
    {
        return false;

    }
}

bool sms_send(void)
{
    buffer_reset();
    USART_Transmit_String("AT+CMGS=\"+380507525453\"\r");
    _delay_ms(2000);
    USART_Transmit_String("AVR SMS test\r");
    _delay_ms(2000);
    USART_Transmit((char)26);
    _delay_ms(2000);
    return true;

}

bool sms_read(void)
{
    buffer_reset();
    USART_Transmit_String("AT+CMGF=1\r");
    _delay_ms(2000);
    USART_Transmit_String("AT+CNMI=2,2,0,0,0\r");
    _delay_ms(2000);
    buffer_reset();
    USART_Flush();

    _delay_ms(20000); // wait for SMS ???
    while(UDR0 != '\0')
    {
        for(int i = 0; i <=BUFFER_SIZE;i++)
        {
            if((buffer[i] == 'S')&&(buffer[i+1]=='e')&&(buffer[i+2]=='t'))
            {
                OLED_Clear();
                OLED_SetCursor(3,0);
                OLED_Printf("Set");
                buffer_reset();
            }
        }
        break;
    }

    return true;
    

}