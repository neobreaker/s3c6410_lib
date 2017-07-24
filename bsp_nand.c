#include "s3c6410.h"

#define NAND_DISABLE_CE()	(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()	(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()		do { while(!(NFSTAT_REG & (1 << 0))); } while(0)


// Standard NAND flash commands
#define NAND_CMD_READ0		0
#define NAND_CMD_READ1		1
#define NAND_CMD_RNDOUT		5
#define NAND_CMD_PAGEPROG	0x10
#define NAND_CMD_READOOB	0x50
#define NAND_CMD_ERASE1		0x60
#define NAND_CMD_STATUS		0x70
#define NAND_CMD_STATUS_MULTI	0x71
#define NAND_CMD_SEQIN		0x80
#define NAND_CMD_RNDIN		0x85
#define NAND_CMD_READID		0x90
#define NAND_CMD_ERASE2		0xd0
#define NAND_CMD_RESET		0xff
// Extended commands for large page devices
#define NAND_CMD_READSTART	0x30
#define NAND_CMD_RNDOUTSTART	0xE0
#define NAND_CMD_CACHEDPROG	0x15

#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7E00F120))


void bsp_nand_init(void)
{
	// 设置NAND Flash控制器
	NFCONF_REG = ( (0x2<<12)|(0xf<<8)|(0x7<<4) );
	NFCONT_REG |= (0x3<<0);

}

// 读一页，即2048byte
static int nandll_read_page (unsigned char *buf, unsigned long addr)
{

	int i;
	int page_size = 2048;

	// 发片选
	NAND_ENABLE_CE();

	// 发读命令：0x00
	NFCMD_REG = NAND_CMD_READ0;
	// 发地址
	NFADDR_REG = 0;
	NFADDR_REG = 0;
	NFADDR_REG = (addr) & 0xff;
	NFADDR_REG = (addr >> 8) & 0xff;
	NFADDR_REG = (addr >> 16) & 0xff;
	// 发读命令：0x30
	NFCMD_REG = NAND_CMD_READSTART;

	// 等待数据
	NF_TRANSRnB();

	// 连续读2048个字节
	for(i=0; i < page_size; i++)
	{
		*buf++ = NFDATA8_REG;
	}

	// 取消片选
	NAND_DISABLE_CE();

	return 0;
}


// 从NAND中拷贝代码到DRAM
int copy2ddr(unsigned int nand_start, unsigned int ddr_start, unsigned int len)
{
	unsigned char *buf = (unsigned char *)ddr_start;
	int i;
	unsigned int page_shift = 11;

	// 发片选
	NAND_ENABLE_CE();

	// 使len为2048的整数倍
	len = (len/2048+1)*2048;

	// 循环拷贝，每次拷贝一页数据
	for (i = 0; i < (len>>page_shift); i++, buf+=(1<<page_shift))
	{
		// 读一页，即2048byte
		nandll_read_page(buf, i);
	}

	return 0;
}

