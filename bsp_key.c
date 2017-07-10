#include "bsp_key.h"

void bsp_key_init(void)
{
	
	GPNCON0  &= ~(GPNCON0_MSK | GPNCON1_MSK | GPNCON2_MSK | GPNCON3_MSK); 
	GPNCON0  |=  (GPNCON0_IN | GPNCON1_IN | GPNCON2_IN | GPNCON3_IN); 
}



