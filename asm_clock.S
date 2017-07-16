.globl asm_clock_init

asm_clock_init:
#define	APLL_LOCK	0x7e00f000
	ldr r0, =APLL_LOCK
	ldr r1, =0x0000ffff
	str	r1, [r0]

	str r1, [r0, #4]
	str r1, [r0, #8]

#define OTHERS		0x7e00f900
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

#define CLK_DIV0	0x7E00F020
	ldr r0, =CLK_DIV0
	ldr r1, =(ARM_RATIO)|(MPLL_RATIO << 4)|(HCLK_RATIO << 8)|(HCLKX2_RATIO << 9)|(PCLK_RATIO << 12)
	str r1, [r0]

#define APLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (1))
#define APLL_CON	0x7E00F00C
	ldr r0, =APLL_CON
	ldr r1, =APLL_CON_VAL
	str r1, [r0]

#define MPLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (1))	//FOUT = MDIV * FIN / (PDIV * 2^SDIV)
#define MPLL_CON	0x7E00F010
	ldr r0, =MPLL_CON
	ldr r1, =MPLL_CON_VAL
	str r1, [r0]

#define CLK_SRC		0x7E00F01C
	ldr r0, =CLK_SRC
	ldr r1, =0x03
	str r1, [r0]

	mov pc, lr
	

