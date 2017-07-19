SECTIONS {
    . = 0x50000000;
    
	.text : {
			start.o
			lowlevel_init.o
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
