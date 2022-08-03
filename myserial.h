#ifndef MYSERIAL_H

#define MYSERIAL_H

void serial_setup(void);
/* called function set the UBRR0H and UBRR0L with calculated BRC;
Function enables RT and TX communication for transmiting and receiving data;
USART is using a 8-bit data format , with 1-st stop bit and no parity*/

void USART_Transmit(unsigned char data);
/* called function waits for empty transmit buffer;
Function puts data into buffer and sends the data */

unsigned char USART_Receive(void);
/* called function waits for data to be received;
Function gets and returns received data from buffer */
void USART_Transmit_String(const char *data);
/*transmit string*/

void USART_Flush(void);
/* called function flushed data from the buffer*/

#endif