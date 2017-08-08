#include "bsp_uart.h"
#include "s3c6410.h"

void bsp_uart_init(void)
{
	
	__REG(GPACON) &= ~0xFF;
	__REG(GPACON) |=  0x22;

	ULCON0_REG = 0x03;
	UCON0_REG   = 0x05;
	UFCON0_REG = 0X01;
	UMCON0_REG = 0X00;

	//115200
	UBRDIV0_REG = 35;
	UDIVSLOT0_REG = 0x01;
	
}

char getchar(void)
{
	while(UFSTAT0_REG & 0x7f);
	return URXH0_REG;
}

void putchar(char c)
{
	while(UFSTAT0_REG & (1<<14));
	URXH0_REG = c;
}


