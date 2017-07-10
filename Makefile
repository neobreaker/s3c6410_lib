nand.bin : start.o bsp_clock.o bsp_sdram.o main.o bsp_nand.o bsp_led.o bsp_key.o
	arm-linux-ld  -T nand.lds -o a.elf $^
	arm-linux-objcopy -O binary a.elf a.bin
	arm-linux-objdump -D a.elf > a.dis

%.o : %.S
	arm-linux-gcc -g -c -O2 -o $@ $^

%.o : %.c
	arm-linux-gcc -g -c -O2 -o $@ $^ -fno-builtin 

clean:
	rm -f *.o *.bin *.elf *.dis	
