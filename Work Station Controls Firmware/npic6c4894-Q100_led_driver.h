/*
 * npic6c4894_Q100_led_driver.h
 *
 * Created: 30/11/2019 8:04:54 PM
 *  Author: William Rigby
 */ 


#ifndef NPIC6C4894_Q100_LED_DRIVER_H_
#define NPIC6C4894_Q100_LED_DRIVER_H_

#include "sam.h"

extern void led_driver_init(void);
extern void led_driver_write(uint16_t outputValue);
extern void led_driver_turn_off(void);
extern void led_driver_turn_on(void);

#endif /* NPIC6C4894-Q100_LED_DRIVER_H_ */