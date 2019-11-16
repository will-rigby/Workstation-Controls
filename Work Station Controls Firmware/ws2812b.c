/*
 * ws2812b.c
 *
 * Created: 16-Nov-19 10:44:16
 *  Author: Will
 */ 

#include "ws2812b.h"

void ws2812b_init_data_output(void){
	PORT->Group[0].DIRSET.reg = (1<<14);	// Set PA14 as output
	PORT->Group[0].OUTCLR.reg = (1<<14);
}

void ws2812b_set_high(void){
	PORT->Group[0].OUTSET.reg = (1<<14);
}

void ws2812b_set_low(void){
	PORT->Group[0].OUTCLR.reg = (1<<14);
}

void ws2812b_write_one(void){
	ws2812b_set_high();
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	ws2812b_set_low();
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	
}

void ws2812b_write_zero(void){
	ws2812b_set_high();
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	ws2812b_set_low();
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}

void ws2812b_write_byte(uint8_t data){
	for(uint8_t i = 0; i < 8; i++){
		if(data&0b10000000){
			ws2812b_write_one();	
		} else {
			ws2812b_write_zero();
		}
		data = data<<1;
	}
}

void ws2812b_write_led(uint8_t red, uint8_t green, uint8_t blue){
	ws2812b_write_byte(green);
	ws2812b_write_byte(red);
	ws2812b_write_byte(blue);
}

void ws2812b_init(void){
	ws2812b_init_data_output();
}