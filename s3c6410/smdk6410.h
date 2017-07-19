/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <gj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK6400(mDirac-III) board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_S3C6410		1		/* in a SAMSUNG S3C6410 SoC */
#define CONFIG_S3C64XX		1		/* in a SAMSUNG S3C64XX Family  */
#define CONFIG_SMDK6410		1		/* on a SAMSUNG SMDK6410 Board  */

#define MEMORY_BASE_ADDRESS	 0x50000000
#define CONFIG_SYS_CLK_FREQ	 12000000	/* the SMDK6400 has 12MHz input clock */
/*
 * Architecture magic and machine type
 */
#define MACH_TYPE		1626
#define UBOOT_MAGIC		(0x43090000 | MACH_TYPE)

#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG

#define CONFIG_BOOTARGS    	"noinitrd root=/dev/nfs rw nfsroot=192.168.60.57:/huichuan1/qtopia,proto=tcp,nfsvers=3,nolock ip=192.168.60.240:192.168.60.57:192.168.60.254:255.255.255.0::eth0 console=ttySAC0,115200 init=/linuxrc video=fb:AT070TN83";
/*
 * select serial console configuration
 */

//#define CONFIG_BAUDRATE		115200

#define CONFIG_UART_66	/* default clock value of CLK_UART */

#define CONFIG_CLK_800_133_66
//#define CONFIG_CLK_666_133_66
//#define CONFIG_CLK_532_133_66
//#define CONFIG_CLK_400_133_66
//#define CONFIG_CLK_400_100_50
//#define CONFIG_CLK_OTHERS

#define CONFIG_CLKSRC_CLKUART

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)


#if defined(CONFIG_CLK_666_133_66) /* FIN 12MHz, Fout 666MHz */
#define APLL_MDIV	333
#define APLL_PDIV	3
#define APLL_SDIV	1
#undef  CONFIG_SYNC_MODE /* ASYNC MODE */

#elif defined(CONFIG_CLK_532_133_66) /* FIN 12MHz, Fout 532MHz */
#define APLL_MDIV	266
#define APLL_PDIV	3
#define APLL_SDIV	1
#define CONFIG_SYNC_MODE

#elif defined(CONFIG_CLK_400_133_66) || defined(CONFIG_CLK_800_133_66) /* FIN 12MHz, Fout 800MHz */
#define APLL_MDIV	400
#define APLL_PDIV	3
#define APLL_SDIV	1
#define CONFIG_SYNC_MODE

#elif defined(CONFIG_CLK_400_100_50) /* FIN 12MHz, Fout 400MHz */
#define APLL_MDIV	400
#define APLL_PDIV	3
#define APLL_SDIV	2
#define CONFIG_SYNC_MODE

#elif defined(CONFIG_CLK_OTHERS)
/*If you have to use another value, please define pll value here*/
/* FIN 12MHz, Fout 532MHz */
#define APLL_MDIV	266
#define APLL_PDIV	3
#define APLL_SDIV	1
#define CONFIG_SYNC_MODE

#endif

#define APLL_VAL	set_pll(APLL_MDIV, APLL_PDIV, APLL_SDIV)

/* prevent overflow */
#define Startup_APLL	(CONFIG_SYS_CLK_FREQ/(APLL_PDIV<<APLL_SDIV)*APLL_MDIV)

/* fixed MPLL 533MHz */
#define MPLL_MDIV	266
#define MPLL_PDIV	3
#define MPLL_SDIV	         1

#define MPLL_VAL	set_pll(MPLL_MDIV, MPLL_PDIV, MPLL_SDIV)
/* prevent overflow */
#define Startup_MPLL	((CONFIG_SYS_CLK_FREQ)/(MPLL_PDIV<<MPLL_SDIV)*MPLL_MDIV)

#if defined(CONFIG_CLK_800_133_66)
#define Startup_APLLdiv		0
#define Startup_HCLKx2div	2
#elif defined(CONFIG_CLK_400_133_66)
#define Startup_APLLdiv		1
#define Startup_HCLKx2div	2
#else
#define Startup_APLLdiv		0
#define Startup_HCLKx2div	1
#endif

#define Startup_PCLKdiv		3
#define Startup_HCLKdiv		1
#define Startup_MPLLdiv		1

#define CLK_DIV_VAL	((Startup_PCLKdiv<<12)|(Startup_HCLKx2div<<9)|(Startup_HCLKdiv<<8)|(Startup_MPLLdiv<<4)|Startup_APLLdiv)

#define Startup_HCLK	(Startup_APLL/(Startup_HCLKx2div+1)/(Startup_HCLKdiv+1))

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */

#define DMC1_MEM_CFG		0x00010012	/* Supports one CKE control, Chip1, Burst4, Row/Column bit */
#define DMC1_MEM_CFG2		0xB45
#define DMC1_CHIP0_CFG		0x150F8
#define DMC_DDR_32_CFG		0x0 		/* 32bit, DDR */

/* Memory Parameters */
/* DDR Parameters */
#define DDR_tREFRESH		7800		/* ns */
#define DDR_tRAS		45		/* ns (min: 45ns)*/
#define DDR_tRC 		68		/* ns (min: 67.5ns)*/
#define DDR_tRCD		23		/* ns (min: 22.5ns)*/
#define DDR_tRFC		80		/* ns (min: 80ns)*/
#define DDR_tRP 		23		/* ns (min: 22.5ns)*/
#define DDR_tRRD		15		/* ns (min: 15ns)*/
#define DDR_tWR 		15		/* ns (min: 15ns)*/
#define DDR_tXSR		120		/* ns (min: 120ns)*/
#define DDR_CASL		3		/* CAS Latency 3 */


/*
 * mDDR memory configuration
 */
#define DMC_DDR_BA_EMRS 	2
#define DMC_DDR_MEM_CASLAT	3
#define DMC_DDR_CAS_LATENCY	(DDR_CASL<<1)						// 6   Set Cas Latency to 3
#define DMC_DDR_t_DQSS		1							// Min 0.75 ~ 1.25
#define DMC_DDR_t_MRD		2							// Min 2 tck
#define DMC_DDR_t_RAS		(((Startup_HCLK / 1000 * DDR_tRAS) - 1) / 1000000 + 1)	// 7, Min 45ns
#define DMC_DDR_t_RC		(((Startup_HCLK / 1000 * DDR_tRC) - 1) / 1000000 + 1) 	// 10, Min 67.5ns
#define DMC_DDR_t_RCD		(((Startup_HCLK / 1000 * DDR_tRCD) - 1) / 1000000 + 1) 	// 4,5(TRM), Min 22.5ns
#define DMC_DDR_schedule_RCD	((DMC_DDR_t_RCD - 3) << 3)
#define DMC_DDR_t_RFC		(((Startup_HCLK / 1000 * DDR_tRFC) - 1) / 1000000 + 1) 	// 11,18(TRM) Min 80ns
#define DMC_DDR_schedule_RFC	((DMC_DDR_t_RFC - 3) << 5)
#define DMC_DDR_t_RP		(((Startup_HCLK / 1000 * DDR_tRP) - 1) / 1000000 + 1) 	// 4, 5(TRM) Min 22.5ns
#define DMC_DDR_schedule_RP	((DMC_DDR_t_RP - 3) << 3)
#define DMC_DDR_t_RRD		(((Startup_HCLK / 1000 * DDR_tRRD) - 1) / 1000000 + 1)	// 3, Min 15ns
#define DMC_DDR_t_WR		(((Startup_HCLK / 1000 * DDR_tWR) - 1) / 1000000 + 1)	// Min 15ns
#define DMC_DDR_t_WTR		2
#define DMC_DDR_t_XP		2							// 1tck + tIS(1.5ns)
#define DMC_DDR_t_XSR		(((Startup_HCLK / 1000 * DDR_tXSR) - 1) / 1000000 + 1)	// 17, Min 120ns
#define DMC_DDR_t_ESR		DMC_DDR_t_XSR
#define DMC_DDR_REFRESH_PRD	(((Startup_HCLK / 1000 * DDR_tREFRESH) - 1) / 1000000) 	// TRM 2656
#define DMC_DDR_USER_CONFIG	1							// 2b01 : mDDR

/*-----------------------------------------------------------------------
 * Physical Memory Map end
 */

#define CONFIG_NR_DRAM_BANKS	1	   /* we have 2 bank of DRAM */
#define PHYS_SDRAM_1		MEMORY_BASE_ADDRESS /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x10000000 /* 256MB */

#define CFG_UBOOT_BASE		MEMORY_BASE_ADDRESS+0x7e00000
#define CFG_UBOOT_SIZE		2*1024*1024
#define TEXT_BASE		MEMORY_BASE_ADDRESS

#define CFG_MALLOC_LEN		1*1024*1024
#define CFG_GBL_DATA_SIZE	128
#define CFG_STACK_SIZE                256*1024

#define CFG_KERNEL_NAND_BASE     0x40000
#define CFG_KERNEL_NAND_SIZE      0x400000
#define CFG_KERNEL_SDRAM_BASE  0x50008000
#endif	/* __CONFIG_H */
