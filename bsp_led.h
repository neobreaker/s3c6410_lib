#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "s3c6410/s3c6410_gpio.h"

typedef enum
{
	LED_1 = 0,
    LED_2,
    LED_3,
    LED_4,
}led_t;

#define GPKCON4_MSK        (0xf<<16)
#define GPKCON5_MSK        (0xf<<20)
#define GPKCON6_MSK        (0xf<<24)
#define GPKCON7_MSK        (0xf<<28)

#define GPKCON4_OUT         (1<<16)
#define GPKCON5_OUT         (1<<20)
#define GPKCON6_OUT         (1<<24)
#define GPKCON7_OUT         (1<<28)

#define GPKDAT4_MSK        (0x1<<4)
#define GPKDAT5_MSK        (0x1<<5)
#define GPKDAT6_MSK        (0x1<<6)
#define GPKDAT7_MSK        (0x1<<7)


void bsp_led_init(void);

void bsp_led_on(led_t led);
void bsp_led_off(led_t led);

#endif
