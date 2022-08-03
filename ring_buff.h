#ifndef RING_BUFF_H
#define RING_BUFF_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 256
bool write_into_buffer(void);           //writes into buffer
bool read_from_buffer(void);            //reads from uffer
bool checker(void);                     // check for OK or ERROR
void buffer_reset(void);                //flushed the buffer ans resets the indexes

#endif
