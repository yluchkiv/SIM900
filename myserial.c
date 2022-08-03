//
//   myserial.h
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "myserial.h"
#define BUAD 9600               // selecter speed
#define BRC ((F_CPU/16/BUAD)-1) // calculated value 103 

void serial_setup(void)
{
    UBRR0H = (unsigned char)(BRC >> 8);                        // set the value 103 (0110 0111) into register ; the value is 8-bit, has to be shifted
    UBRR0L = (unsigned char) BRC;                              // set the value into register
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0);              // enable RX and TX and Interrupt flag wnen RX is full!
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
    // set datframe 8 bit ans 2 stop bits - Extra stop bits can  add a little extra receive processing time,
    // especially at high baud rates and/or using soft UART, where time is required to process the received byte.
}

void USART_Transmit(unsigned char data)
{ 
    while (!( UCSR0A & (1<<UDRE0)));            // Wait for empty transmit buffer                                       
    UDR0 = data;                                // Put data into buffer, sends the data 
}

unsigned char USART_Receive(void)
{
    while (!(UCSR0A & (1<<RXC0)));              // Wait for data to be received */
    return UDR0;                                // Get and return received data from buffer */
}

void USART_Transmit_String(const char *data)
{
    cli();
    while(*data != '\0')
    {
        
        USART_Transmit(*data);
        data++;
        sei();
    }
}

void USART_Flush(void)
{
    unsigned char dummy;
    while (UCSR0A & (1<<RXC0))
        dummy = UDR0;  //The following code example shows how to flush the receive buffer.
    (void)dummy;       //I know that this value in not in-use
}
