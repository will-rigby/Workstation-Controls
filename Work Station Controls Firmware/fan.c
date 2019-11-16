/*
 * fan.c
 *
 * Created: 14-Nov-19 17:28:52
 *  Author: Will
 */ 

#include "fan.h"
#include "adc.h"

void fan_init_control_switch(void){
	/* Set up Fan On Switch */
	PORT->Group[0].DIRCLR.reg = (1<<25);
	PORT->Group[0].PINCFG[25].reg = PORT_PINCFG_INEN;
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
	TCC0->PER.reg = TCC_PER_PER(0xFF);
	TCC0->CC[3].reg = TCC_CC_CC(128);
	TCC0->CC[2].reg = TCC_CC_CC(128);
	TCC0->CC[1].reg = TCC_CC_CC(128);
	TCC0->CC[0].reg = TCC_CC_CC(128);
	TCC0->EVCTRL.reg = TCC_EVCTRL_TCEI1 | TCC_EVCTRL_TCEI0 | TCC_EVCTRL_CNTEO | TCC_EVCTRL_EVACT1_RETRIGGER | TCC_EVCTRL_EVACT0_COUNTEV;
	TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE;
	
	
	TCC0->CTRLBSET.reg = 0x1<<5;
	
	
}

void fan_set_pwm(uint8_t val){
	TCC0->CC[3].reg = ((uint32_t)val)<<6;
}

void fan_initialise(void){
	fan_init_control_switch();
	fan_init_power_pot();
	fan_init_pwm();
}

uint8_t fan_read_control_switch(void){
	if(PORT->Group[0].IN.reg & (1<<25)){
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
		uint8_t fanPower = (uint8_t)(adcVal>>4);
		fan_set_pwm(fanPower);
	} else {
		fan_set_pwm(0200);
	}
}
