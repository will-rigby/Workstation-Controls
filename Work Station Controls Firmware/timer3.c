/*
 * timer3.c
 *
 * Created: 14-Nov-19 18:18:50
 *  Author: Will
 */ 

//#include "timer3.h"
//
//#define F_CPU 16000000ul
//
//volatile uint32_t ticks = 0; // volatile as only updated in ISR
//
//
//void TC3_Handler(void)
//{
	//if (TC3->COUNT16.INTFLAG.reg & TC_INTFLAG_MC(1))
	//{
		//ticks++;
		//TC3->COUNT16.INTFLAG.reg = TC_INTFLAG_MC(1);
	//}
//}
//
//uint32_t get_millis(void){
	//return ticks;
//}
//
//void delay_ms(uint32_t time){
	//uint32_t waitUntil = ticks + time;
	//while(ticks < waitUntil);
//}
//
//static void timer_set_period(uint16_t i)
//{
	//TC3->COUNT16.CC[0].reg = 500;
	//TC3->COUNT16.CC[1].reg = 500;
	//TC3->COUNT16.COUNT.reg = 0;
//}
//
//void init_timer3(void){
	//
	//MCLK->APBCMASK.reg |= MCLK_APBCMASK_TC3;
//
	//GCLK->PCHCTRL[TC3_GCLK_ID].reg = GCLK_PCHCTRL_GEN(0) | GCLK_PCHCTRL_CHEN;
	//while (0 == (GCLK->PCHCTRL[TC3_GCLK_ID].reg & GCLK_PCHCTRL_CHEN));
//
	//TC3->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV8 |
	//TC_CTRLA_PRESCSYNC_RESYNC;
//
	//TC3->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ;
//
	//TC3->COUNT16.COUNT.reg = 0;
//
	//timer_set_period(1000);
//
	//TC3->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
//
	//TC3->COUNT16.INTENSET.reg = TC_INTENSET_MC(1);
	//NVIC_EnableIRQ(TC3_IRQn);
	//
//}