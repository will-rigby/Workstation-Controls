/*
 * fan.c
 *
 * Created: 14-Nov-19 17:28:52
 *  Author: Will
 */ 

#include "fan.h"
#include "adc.h"
#include "npic6c4894-Q100_led_driver.h"

void led_bar_write_fan_speed(uint8_t fanSpeed){
	uint16_t ledBarVal = 0;
	if(fanSpeed == 0){
		ledBarVal = 0;
		} else if (fanSpeed < 25){
		ledBarVal = 0b1;
		} else if (fanSpeed < 50){
		ledBarVal = 0b11;
		} else if (fanSpeed < 75){
		ledBarVal = 0b111;
		} else if (fanSpeed < 100){
		ledBarVal = 0b1111;
		} else if (fanSpeed < 125){
		ledBarVal = 0b11111;
		} else if (fanSpeed < 150){
		ledBarVal = 0b111111;
		} else if (fanSpeed < 175){
		ledBarVal = 0b1111111;
		} else if (fanSpeed < 200){
		ledBarVal = 0b11111111;
		} else if (fanSpeed < 225){
		ledBarVal = 0b111111111;
		} else {
		ledBarVal = 0b1111111111;
	}
	led_driver_write(ledBarVal);
}

void fan_init_control_switch(void){
	/* Set up Fan On Switch */
	PORT->Group[0].DIRCLR.reg = (1<<24);
	PORT->Group[0].PINCFG[24].reg = PORT_PINCFG_INEN;
}

void fan_init_power_pot(void){
	/* Configure fan adc for reading control potentiometer */
	PORT->Group[0].DIRCLR.reg = (1<<7);
	PORT->Group[0].PINCFG[7].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[3].reg |= (0x01<<4);
}

void fan_init_pwm(void){
	/* Configure fan io pins */
	PORT->Group[0].DIRSET.reg = (1<<19);
	PORT->Group[0].PINCFG[19].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[9].reg |= (0x05<<4);					//PMUX F - TCC0/WO3
	
	/* Configure TCC0 Clock */
	MCLK->APBCMASK.reg |= MCLK_APBCMASK_TCC0;
	GCLK->PCHCTRL[TCC0_GCLK_ID].reg = GCLK_PCHCTRL_GEN(0) | GCLK_PCHCTRL_CHEN;
	while (0 == (GCLK->PCHCTRL[TCC0_GCLK_ID].reg & GCLK_PCHCTRL_CHEN));
	
	/* Configure TCC0 */
	TCC0->CTRLA.reg  = 0;
	//TCC0->CTRLA.reg |= 0x7 << 8;
	
	TCC0->WAVE.reg = TCC_WAVE_WAVEGEN_NPWM;
	TCC0->PER.reg = 0xFF;
	TCC0->CC[3].reg = TCC_CC_CC(0);
	TCC0->CC[2].reg = TCC_CC_CC(0);
	TCC0->CC[1].reg = TCC_CC_CC(0);
	TCC0->CC[0].reg = TCC_CC_CC(0);
	//TCC0->EVCTRL.reg = TCC_EVCTRL_TCEI1 | TCC_EVCTRL_TCEI0 | TCC_EVCTRL_CNTEO | TCC_EVCTRL_EVACT1_RETRIGGER | TCC_EVCTRL_EVACT0_INC;
	TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE;
	
	
	TCC0->CTRLBSET.reg = 0x1<<5;
	
	
}

void fan_set_pwm(uint8_t val){
	TCC0->CC[3].reg = ((uint32_t)val);
}

void fan_initialise(void){
	fan_init_control_switch();
	fan_init_power_pot();
	fan_init_pwm();
}

uint8_t fan_read_control_switch(void){
	if(PORT->Group[0].IN.reg & (1<<24)){
		return 1;
	} else {
		return 0;
	}
}

uint16_t fan_read_power_pot(void){
	return adc_read_channel(0x07);
}

void fan_process(void){
	if(fan_read_control_switch()){
		uint16_t adcVal = fan_read_power_pot();
		fan_set_pwm(adcVal);
		led_bar_write_fan_speed(adcVal);
	} else {
		fan_set_pwm(0);
		led_bar_write_fan_speed(0);
	}
}
