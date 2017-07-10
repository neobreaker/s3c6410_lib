#ifndef __BSP_KEY_H__
#define __BSP_key_H__

#define GPNCON0_MSK        (0xf<0)
#define GPNCON1_MSK        (0xf<4)
#define GPNCON2_MSK        (0xf<8)
#define GPNCON3_MSK        (0xf<12)

#define GPNCON0_IN			GPNCON0_MSK        
#define GPNCON1_IN			GPNCON1_MSK        
#define GPNCON2_IN			GPNCON2_MSK        
#define GPNCON3_IN			GPNCON3_MSK      

#define GPNDAT0_MSK        (0x1<<4)
#define GPNDAT1_MSK        (0x1<<5)
#define GPNDAT2_MSK        (0x1<<6)
#define GPNDAT3_MSK        (0x1<<7)

#define GPNCON0 		   (*(volatile unsigned long *)0x7F008830)
#define GPNDAT			   (*(volatile unsigned long *)0x7F008834)

typedef enum
{
	KEY_1 = 0,
    KEY_2,
    KEY_3,
    KEY_4,
}key_t;

void bsp_key_init(void);

#endif
