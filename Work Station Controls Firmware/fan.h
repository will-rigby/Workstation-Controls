/*
 * fan.h
 *
 * Created: 14-Nov-19 17:33:50
 *  Author: Will
 */ 


#ifndef FAN_H_
#define FAN_H_

#include "sam.h"

void fan_init_control_switch(void);
void fan_init_power_pot(void);
void fan_init_pwm(void);
void fan_set_pwm(uint8_t val);
extern void fan_initialise(void);
uint8_t fan_read_control_switch(void);
uint16_t fan_read_power_pot(void);
extern void fan_process(void);

#endif /* FAN_H_ */