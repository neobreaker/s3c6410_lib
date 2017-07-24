// 启动代码
.global _start

_start:

	/* 0 地址 */
	b reset                 /* 复位时,cpu跳到0地址 */
	b halt     @ldr pc, =undefined_instruction  /* cpu遇到不能识别的指令时 */
	b halt     @ldr pc, _vector_swi             /* 当执行swi指令时, 进入swi模 式 */
	b halt     @ldr	pc, _prefetch_abort /* 预取中止异常 */
	b halt     @ldr	pc, _data_abort     /* 数据访问异常 */
	b halt     @ldr	pc, _not_used       /* 没用到 */
	b halt     @ldr	pc, _irq            /* 0x18 中断异常 */
	b halt     @ldr	pc, _fiq            /* 快中断异常 */

reset:

		/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0,cpsr
	bic	r0,r0,#0x1f
	orr	r0,r0,#0xd3
	msr	cpsr,r0
	
cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0

	/* Peri port setup */
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
    mcr	p15,0,r0,c15,c2,4       @ 256M(0x70000000-0x7fffffff)

	/*
	 * Go setup Memory and board specific bits prior to relocation.
	 */
	bl	lowlevel_init	/* go setup pll,mux,memory */
	
	// 初始化sdram
	bl bsp_sdram_init



	// 重定位，把程序的代码段、数据段复制到它的链接地址去
	adr r0, _start   			
	ldr r1, =_start  			
	ldr r2, =bss_start      	
	sub r2, r2, r1
	cmp r0,r1
	beq clean_bss
	bl copy2ddr	
	b  after_copy

after_copy:
		// 清BSS，把BSS段对应的内存清零
	clean_bss:
		ldr r0, =bss_start
		ldr r1, =bss_end
		mov r3, #0
		cmp r0, r1
		beq stack_setup
	clean_loop:
		str r3, [r0], #4
		cmp r0, r1	
		bne clean_loop		

		// 跳转
	stack_setup:
		ldr sp, =0x57000000
		ldr pc, =main
		@ldr	pc, _start_armboot
halt:
	b halt	
