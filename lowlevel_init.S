#include "s3c6410.h"
#include "smdk6410.h"
 .globl lowlevel_init
lowlevel_init:
	mov	r12, lr

/* Disable Watchdog */
	ldr	r0, =0x7e000000		@0x7e004000
	orr	r0, r0, #0x4000
	mov	r1, #0
	str	r1, [r0]
	
@ External interrupt pending clear
	ldr	r0, =(ELFIN_GPIO_BASE+EINTPEND_OFFSET)	/*EINTPEND*/
	ldr	r1, [r0]
	str	r1, [r0]

	ldr	r0, =ELFIN_VIC0_BASE_ADDR 	@0x71200000
	ldr	r1, =ELFIN_VIC1_BASE_ADDR 	@0x71300000
	
 @ Disable all interrupts (VIC0 and VIC1)
	mvn	r3, #0x0
	str	r3, [r0, #oINTMSK]
	str	r3, [r1, #oINTMSK]

@ Set all interrupts as IRQ
	mov	r3, #0x0
	str	r3, [r0, #oINTMOD]
	str	r3, [r1, #oINTMOD]

@ Pending Interrupt Clear
	mov	r3, #0x0
	str	r3, [r0, #oVECTADDR]
	str	r3, [r1, #oVECTADDR]

	// ø™∆Ùicaches
#ifdef  CONFIG_SYS_ICACHE_OFF
	bic r0, r0, #0x00001000 				@ clear bit 12 (I) I-cache
#else
	orr r0, r0, #0x00001000 				@ set bit 12 (I) I-cache
#endif
	mcr p15, 0, r0, c1, c0, 0

	// …Ë÷√’ª
	ldr sp, =1024*4
	
	bl clock_asm_init

@	bl uart_asm_init

@ 	bl nand_asm_init
 
@ 	bl mem_ctrl_asm_init


 #if 0
        ldr     r0, =(ELFIN_CLOCK_POWER_BASE+RST_STAT_OFFSET)
        ldr     r1, [r0]
        bic     r1, r1, #0xfffffff7
        cmp     r1, #0x8
        beq     wakeup_reset

#endif

 	mov lr, r12
 	mov pc, lr
/*lowlevel_init end*/

#if 1
wakeup_reset:

	/*Clear wakeup status register*/
	ldr	r0, =(ELFIN_CLOCK_POWER_BASE+WAKEUP_STAT_OFFSET)
	ldr	r1, [r0]
	str	r1, [r0]

        /*LED test*/
        ldr     r0, =ELFIN_GPIO_BASE
        ldr     r1, =0x3000
        str     r1, [r0, #GPNDAT_OFFSET]

	/*Load return address and jump to kernel*/
	ldr	r0, =(ELFIN_CLOCK_POWER_BASE+INF_REG0_OFFSET)
	ldr	r1, [r0]	/* r1 = physical address of s3c6400_cpu_resume function*/
	mov	pc, r1		/*Jump to kernel (sleep-s3c6400.S)*/
	nop
	nop
#endif
/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
clock_asm_init:
	ldr r0, =APLL_LOCK
	ldr r1, =0x0000ffff
	str	r1, [r0]

	str r1, [r0, #4]
	str r1, [r0, #8]

	ldr r0, =OTHERS
	ldr r1, [r0]
	bic r1, #0xc0
	str r1, [r0]

others_loop:
	ldr r0, =OTHERS
	ldr r1, [r0]
	and	r1, #0xf00
	cmp r1, #0
	bne others_loop

#define ARM_RATIO    0   						// ARMCLK 	= DOUTAPLL / (ARM_RATIO + 1)  	= 532/(0+1) = 532 MHz
#define MPLL_RATIO   0   						// DOUTMPLL = MOUTMPLL / (MPLL_RATIO + 1)   = 532/(0+1) = 532  MHz
#define HCLKX2_RATIO 1   						// HCLKX2 	= HCLKX2IN / (HCLKX2_RATIO + 1) = 532/(1+1) = 266  MHz
#define HCLK_RATIO   1   						// HCLK 	= HCLKX2   / (HCLK_RATIO + 1)   = 266/(1+1) = 133  MHz
#define PCLK_RATIO   3   						// PCLK   	= HCLKX2   / (PCLK_RATIO + 1)   = 266/(3+1) = 66.5 MHz

	ldr r0, =CLK_DIV0
	ldr r1, =(ARM_RATIO)|(MPLL_RATIO << 4)|(HCLK_RATIO << 8)|(HCLKX2_RATIO << 9)|(PCLK_RATIO << 12)
	str r1, [r0]

#define APLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (1))
	ldr r0, =APLL_CON
	ldr r1, =APLL_CON_VAL
	str r1, [r0]

#define MPLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (1))	//FOUT = MDIV * FIN / (PDIV * 2^SDIV)
	ldr r0, =MPLL_CON
	ldr r1, =MPLL_CON_VAL
	str r1, [r0]

	ldr r0, =CLK_SRC
	ldr r1, =0x03
	str r1, [r0]

	mov pc, lr
	
/*
 * uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
 * void uart_asm_init(void)
 */
uart_asm_init:
	/* set GPIO to enable UART */
	@ GPIO setting for UART
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, =0x220022
	str   	r1, [r0, #GPACON_OFFSET]
	ldr	r1, =0x2222
	str   	r1, [r0, #GPBCON_OFFSET]
	ldr	r0, =ELFIN_UART_CONSOLE_BASE		@0x7F005000
	mov	r1, #0x0
	str	r1, [r0, #UFCON_OFFSET]
	str	r1, [r0, #UMCON_OFFSET]
	mov	r1, #0x3                	@was 0.
	str	r1, [r0, #ULCON_OFFSET]
#if defined(CONFIG_CLKSRC_CLKUART)
	ldr	r1, =0xe45			/* UARTCLK SRC = 11 => EXT_UCLK1*/
#endif
	str	r1, [r0, #UCON_OFFSET]
#if defined(CONFIG_UART_66)
	ldr	r1, =0x22
#endif
	str	r1, [r0, #UBRDIV_OFFSET]
#if defined(CONFIG_UART_66)
	ldr	r1, =0x1FFF
#endif
	str	r1, [r0, #UDIVSLOT_OFFSET]
/*
 * Nand Interface Init for SMDK6400 */
nand_asm_init:
	ldr	r0, =ELFIN_NAND_BASE
	ldr	r1, [r0, #NFCONF_OFFSET]
	orr	r1, r1, #0x70		@set TWRPH1
	orr	r1, r1, #0x7700	@set TWRPH0 TACLS
	str     r1, [r0, #NFCONF_OFFSET]

	ldr	r1, [r0, #NFCONT_OFFSET]
	orr	r1, r1, #0x03		@set MODE Reg_nCE0
	str     r1, [r0, #NFCONT_OFFSET]

	mov	pc, lr
