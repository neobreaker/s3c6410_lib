#include "bsp_led.h"
#include "bsp_key.h"

// 延时
void delay()
{
	volatile int i = 0x10000;
	while (i--);
}

void bsp_init()
{
	bsp_led_init();
	bsp_key_init();
}

void test_led()
{
	int i = 0;
	
	// 跑马灯
	while (1)
	{
		
		for(i = 0; i < 4; i++)
		{
		    bsp_led_on(i);
			delay();
		}
		for(i = 0; i < 4; i++)
		{
		    bsp_led_off(i);
			delay();
		}
		
		
	}
}

void test_key()
{
	
	// 轮询的方式查询按键事件
	while(1)
	{

		if(GPNDAT & (1<<0))				// KEY1被按下，则LED1亮，否则LED1灭
			bsp_led_on(LED_1);
		else
			bsp_led_off(LED_1);

		if(GPNDAT & (1<<1))				// KEY2被按下，则LED2亮，否则LED2灭
			bsp_led_on(LED_2);
		else
			bsp_led_off(LED_2);

		if(GPNDAT & (1<<2))				// KEY3被按下，则LED3亮，否则LED3灭
			bsp_led_on(LED_3);
		else
			bsp_led_off(LED_3);

		if(GPNDAT & (1<<3))				// KEY4被按下，则LED4亮，否则LED4灭
			bsp_led_on(LED_4);
		else
			bsp_led_off(LED_4);

	}
}

int main()
{
	int dat = 0;
	
	bsp_init();


	// 配置GPK4-7为输出功能
//	GPKCON0 = 0x11110000;	

	
//	test_led();
	test_key();
	
	return 0;
}
