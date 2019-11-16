/*
 * adc.h
 *
 * Created: 14-Nov-19 17:48:49
 *  Author: Will
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "sam.h"

extern void adc_initalise(void);
extern uint16_t adc_read_channel(uint8_t channel);
#endif /* ADC_H_ */