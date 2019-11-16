/*
 * adc.c
 *
 * Created: 14-Nov-19 17:48:40
 *  Author: Will
 */ 

#include "adc.h"

void adc_initalise(void){
	/* Configure ADC Clock */
	MCLK->APBDMASK.reg |= MCLK_APBDMASK_ADC;
	GCLK->PCHCTRL[ADC_GCLK_ID].reg = GCLK_PCHCTRL_GEN(0) | GCLK_PCHCTRL_CHEN; // Set SERCOM3 Peripheral Clock to use Generic Clock 0
	while (0 == (GCLK->PCHCTRL[ADC_GCLK_ID].reg & GCLK_PCHCTRL_CHEN)); // Wait until generic peripheral clock connected to SERCOM3
		
	/* Configure ADC */
	ADC->CTRLA.reg = 0;			// Reset
	ADC->CTRLB.reg = 0;			// Prescaler set to Divide By 2
	ADC->REFCTRL.reg = 0x03;	// VREFA
	ADC->CTRLC.reg = 0;
	ADC->CTRLA.reg |= ADC_CTRLA_ENABLE;
}

uint16_t adc_read_channel(uint8_t channel){
	/* Configure Channel */
	ADC->INPUTCTRL.reg = (0x18<<8)|(channel);
	ADC->SWTRIG.reg = ADC_SWTRIG_START;
	while(!(ADC->INTFLAG.reg & ADC_INTFLAG_RESRDY));
	return 0xFFF&ADC->RESULT.reg;
}