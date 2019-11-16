/*
 * ws2812b.h
 *
 * Created: 16-Nov-19 10:45:41
 *  Author: Will
 */ 


#ifndef WS2812B_H_
#define WS2812B_H_

#include "sam.h"

void ws2812b_init_data_output(void);
void ws2812b_set_high(void);
void ws2812b_set_low(void);
void ws2812b_write_one(void);
void ws2812b_write_zero(void);
void ws2812b_write_byte(uint8_t data);
extern void ws2812b_write_led(uint8_t red, uint8_t green, uint8_t blue);
extern void ws2812b_init(void);


#endif /* WS2812B_H_ */