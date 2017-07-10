#include "bsp_led.h"


void bsp_led_init()
{
		
	GPKCON0  &= ~(GPKCON4_MSK | GPKCON5_MSK | GPKCON6_MSK | GPKCON7_MSK); 
	GPKCON0  |=  (GPKCON4_OUT | GPKCON5_OUT | GPKCON6_OUT | GPKCON7_OUT);
}


void bsp_led_on(led_t led)
{
	switch(led)
	{
	case LED_1:
		GPKDAT  &= ~(GPKDAT4_MSK);
		break;
	case LED_2:
		GPKDAT	&= ~(GPKDAT5_MSK);
		break;
	case LED_3:
		GPKDAT  &= ~(GPKDAT6_MSK);
		break;
	case LED_4:
		GPKDAT	&= ~(GPKDAT7_MSK);
		break;
	}
}

void bsp_led_off(led_t led)
{
	
	switch(led)
	{
	case LED_1:
		GPKDAT	|= (GPKDAT4_MSK);
		break;
	case LED_2:
		GPKDAT	|= (GPKDAT5_MSK);
		break;
	case LED_3:
		GPKDAT	|= (GPKDAT6_MSK);
		break;
	case LED_4:
		GPKDAT	|= (GPKDAT7_MSK);
		break;
	}
}


