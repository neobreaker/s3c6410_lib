CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

INCLUDEDIR 	:= $(shell pwd)/include
S3C63XXDIR 	:= $(shell pwd)/s3c6410
CFLAGS 		:= -Wall -Os -fno-builtin-printf 
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR) -I$(S3C63XXDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o lowlevel_init.o bsp_sdram.o main.o bsp_nand.o bsp_led.o bsp_key.o bsp_lcd.o bsp_uart.o

a.bin: $(objs)
	${LD} -Tnand.lds -o a.elf $^
	${OBJCOPY} -O binary -S a.elf $@
	${OBJDUMP} -D a.elf > a.dis

.PHONY : lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f a.bin a.elf a.dis *.o
	


