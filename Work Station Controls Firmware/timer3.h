/*
 * timer3.h
 *
 * Created: 14-Nov-19 18:19:28
 *  Author: Will
 */ 


#ifndef TIMER3_H_
#define TIMER3_H_

#include "sam.h"

uint32_t get_millis(void);
void delay_ms(uint32_t time);
void init_timer3(void);



#endif /* TIMER3_H_ */