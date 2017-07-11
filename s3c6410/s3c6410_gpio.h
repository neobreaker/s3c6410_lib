#ifndef __S3C6410_GPIO_H__
#define __S3C6410_GPIO_H__


#define GPKCON0 		   (*(volatile unsigned long *)0x7F008800)
#define GPKDAT			   (*(volatile unsigned long *)0x7F008808)

#define GPNCON0 		   (*(volatile unsigned long *)0x7F008830)
#define GPNDAT			   (*(volatile unsigned long *)0x7F008834)

#endif
