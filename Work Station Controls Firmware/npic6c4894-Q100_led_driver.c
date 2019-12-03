/*
 * npic6c4894_Q100_led_driver.c
 *
 * Created: 30/11/2019 8:04:45 PM
 *  Author: William Rigby
 */ 

#include "npic6c4894-Q100_led_driver.h"

static void cp_high(void){
	PORT->Group[0].OUTSET.reg = (1<<30);
}

static void cp_low(void){
	PORT->Group[0].OUTCLR.reg = (1<<30);
}

static void le_high(void){
	PORT->Group[0].OUTSET.reg = (1<<31);
}

static void le_low(void){
	PORT->Group[0].OUTCLR.reg = (1<<31);
}

static void data_high(void){
	PORT->Group[1].OUTSET.reg = (1<<2);
}

static void data_low(void){
	PORT->Group[1].OUTCLR.reg = (1<<2);
}

static void oe_high(void){
	PORT->Group[1].OUTSET.reg = (1<<3);
}

static void oe_low(void){
	PORT->Group[1].OUTCLR.reg = (1<<3);
}

static void led_driver_init_pins(void){
	PORT->Group[1].DIRSET.reg = (1<<2)|(1<<3);
	PORT->Group[0].DIRSET.reg = (1<<30)|(1<<31);
}

void led_driver_init(void){
	led_driver_init_pins();
	le_high();
	oe_high();
}

void led_driver_write(uint16_t outputValue){
	for(uint8_t i = 0; i < 12; i++){
		delay_ms(1);
		cp_low();
		if(outputValue&1){
			data_high();
		} else {
			data_low();
		}
		delay_ms(1);
		cp_high();
		outputValue = outputValue>>1;
	}
	le_low();
	delay_ms(1);
	le_high();
	delay_ms(20);
}

void led_driver_turn_off(void){
	oe_low();
}

void led_driver_turn_on(void){
	oe_high();
}