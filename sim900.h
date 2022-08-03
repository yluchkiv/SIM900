#ifndef SIM900_H
#define SIM900_H

#include <stdbool.h>

void power_on(void); //turn on SIM900 shield
bool stat_check(void); // send AT and wait for OK
bool sim_check(void); // send AT+CPIN? and wait for OK
bool sms_send(void); //send sms to fixed number
bool sms_read(void); //read sms

#endif
