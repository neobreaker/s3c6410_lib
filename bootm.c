#include "setup.h"
#include "main.h"
#include "global_data.h"
#include "smdk6410.h"
 //image_header_t header;
 static struct tag *params;
 DECLARE_GLOBAL_DATA_PTR;
  uint  strlen(const char * s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}
 char * strcpy(char * dest,const char *src)
{
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return tmp;
}
 #if defined (CONFIG_SETUP_MEMORY_TAGS) || defined (CONFIG_CMDLINE_TAG) || defined (CONFIG_INITRD_TAG) 

static void setup_start_tag (bd_t *bd)
{
	params = (struct tag *) bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}


#ifdef CONFIG_SETUP_MEMORY_TAGS
static void setup_memory_tags (bd_t *bd)
{
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size (tag_mem32);

		params->u.mem.start = bd->bi_dram[i].start;
		params->u.mem.size = bd->bi_dram[i].size;

		params = tag_next (params);
	}
}
#endif /* CONFIG_SETUP_MEMORY_TAGS */


static void setup_commandline_tag (bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}

static void setup_end_tag (bd_t *bd)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

#endif /* CONFIG_SETUP_MEMORY_TAGS || CONFIG_CMDLINE_TAG || CONFIG_INITRD_TAG */

void do_bootm_linux (void)
{
	void (*theKernel)(int zero, int arch, uint params);
	bd_t *bd = gd->bd;
	int addr = CFG_KERNEL_SDRAM_BASE;
	
	char *commandline =  CONFIG_BOOTARGS;

	theKernel = (void (*)(int, int, uint))addr;

	setup_start_tag (bd);

	setup_memory_tags (bd);

	setup_commandline_tag (bd, commandline);

	setup_end_tag (bd);

	/* we assume that the kernel is in place */
	Uart_SendString ("\nStarting kernel ...\n\n");

	//cleanup_before_linux ();

	theKernel (0, bd->bi_arch_number, bd->bi_boot_params);
}
void do_bootm (void)
{

	//ulong addr;
	
	//ulong  *len_ptr = NULL; /* not to make warning. by scsuh */

	//int  verify;

	//image_header_t *hdr = &header;
	
	//addr = 0x50008000;
	//printf("Boot with zImage\n");
	//addr = virt_to_phys(addr);
	//hdr->ih_ep = ntohl(addr);
	//hdr->ih_ep =0x800050;

}
