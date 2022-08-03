#include "i2c.h"
#include "SSD1306.h"
#include "ring_buff.h"
#include "myserial.h"
#include "sim900.h"
#include <util/delay.h>
#include <avr/interrupt.h>


void display_init();


int main()
{
    display_init();
    serial_setup();
    DDRD = (1 << PORTD6);
    PORTD = 0;
    sei();
    _delay_ms(5000);
    if(stat_check())
    {
        _delay_ms(5000);
        if(sim_check())
        {
            _delay_ms(5000);

            if(sms_read())
            {

                read_from_buffer();

            }
        }
        else
        {
            _delay_ms(5000);
            OLED_SetCursor(6,0);
            OLED_Printf("error");

        }
    }
 
    while(1)
    {
           
 
    }
    return 0;
}

void display_init()
{
    OLED_Init();  //initialize the OLED
    OLED_SetCursor(0, 0);        //set the cursor position to (0 - move down, 0-move left)
    OLED_Printf("Display Initialized");
}
ISR(USART_RX_vect)
{
    PORTD ^= (1 << PD6);
    write_into_buffer();
}
