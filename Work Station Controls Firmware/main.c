/*
 * Work Station Controls Firmware.c
 *
 * Created: 14-Nov-19 17:26:23
 * Author : Will
 */ 


#include "sam.h"
#include "adc.h"
#include "fan.h"
#include "npic6c4894-Q100_led_driver.h"
#include "timer3.h"


void sys_init(void)
{
	// Switch to 16MHz clock (disable prescaler)
	OSCCTRL->OSC16MCTRL.reg = OSCCTRL_OSC16MCTRL_ENABLE | OSCCTRL_OSC16MCTRL_FSEL_16;

	// Switch to the highest performance level
	PM->INTFLAG.reg = PM_INTFLAG_PLRDY;
	PM->PLCFG.reg = PM_PLCFG_PLSEL_PL2_Val;
	while (!PM->INTFLAG.reg);

	// Enable interrupts
	__enable_irq();
}

int main(void)
{
    /* Initialize the SAM system */
    sys_init();

	/* Enable Peripherals */
	init_timer1();
	adc_initalise();
	fan_initialise();
	led_driver_init();
	uint16_t i = 0;
	while(1){
		led_driver_write(i);
		i++;
		delay_ms(100);
	}
    /* Replace with your application code */
    while (1) 
    {
		fan_process();
		uint32_t top = TCC0->COUNT.reg;
		//fan_set_pwm(250);
	}
}
