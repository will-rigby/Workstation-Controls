/*
 * timer3.c
 *
 * Created: 14-Nov-19 18:18:50
 *  Author: Will
 */ 

#include "timer3.h"

#define F_CPU 16000000ul

volatile uint32_t ticks = 0; // volatile as only updated in ISR
volatile uint8_t ledFlashTic = 0;

void TC1_Handler(void)
{
	if (TC1->COUNT16.INTFLAG.reg & TC_INTFLAG_MC(1))
	{
		ticks++;
		ledFlashTic++;
		if(ledFlashTic == 0){
			if(PORT->Group[0].OUT.reg & (1<<21)){
				PORT->Group[0].OUTCLR.reg = (1<<21);
			} else {
				PORT->Group[0].OUTSET.reg = (1<<21);
			}
		}
		TC1->COUNT16.INTFLAG.reg = TC_INTFLAG_MC(1);
	}
}

uint32_t get_millis(void){
	return ticks;
}

void delay_ms(uint32_t time){
	uint32_t waitUntil = ticks + time;
	while(ticks < waitUntil);
}

static void timer_set_period(uint16_t i)
{
	TC1->COUNT16.CC[0].reg = 500;
	TC1->COUNT16.CC[1].reg = 500;
	TC1->COUNT16.COUNT.reg = 0;
}

void init_timer1(void){
	
	MCLK->APBCMASK.reg |= MCLK_APBCMASK_TC1;

	GCLK->PCHCTRL[TC1_GCLK_ID].reg = GCLK_PCHCTRL_GEN(0) | GCLK_PCHCTRL_CHEN;
	while (0 == (GCLK->PCHCTRL[TC1_GCLK_ID].reg & GCLK_PCHCTRL_CHEN));

	TC1->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV8 |
	TC_CTRLA_PRESCSYNC_RESYNC;

	TC1->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ;

	TC1->COUNT16.COUNT.reg = 0;

	timer_set_period(1000);

	TC1->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;

	TC1->COUNT16.INTENSET.reg = TC_INTENSET_MC(1);
	NVIC_EnableIRQ(TC1_IRQn);
	
	
	PORT->Group[0].DIRSET.reg = (1<<21);
}