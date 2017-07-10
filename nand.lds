SECTIONS {
    . = 0x50000000;
    
	.text : {
			start.o
			bsp_clock.o
			bsp_sdram.o
			bsp_nand.o
			bsp_key.o
			bsp_led.o
			* (.text)
	}

	.rodata : {
			* (.rodata)
	}

	.data : {
			* (.data)
	}

    bss_start = .;
    .bss ALIGN(4)  : { *(.bss)  *(COMMON) }
    bss_end = .;
}
