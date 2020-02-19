CC=c99 # clang gave me cleaner binaries
CFLAGS=-I./include/ -m32 -ffreestanding -fno-pie -O1 -ggdb

# default make target
all: mos-image

run: all
	bochs -q

mos-image: boot_sect.bin kernel.bin
	cat $^ > $@

kernel.bin: kernel_entry.o interrupt.o kernel.o screen.o keyboard.o shell.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.o: kernel/kernel.c 
	$(CC) $(CFLAGS) -o $@ -c $^

shell.o: kernel/shell.c 
	$(CC) $(CFLAGS) -o $@ -c $^

interrupt.o: kernel/interrupt.asm
	nasm -f elf -o $@ $^

kernel_entry.o: boot/kernel_entry.asm
	nasm -f elf -o $@ $^

%.o: drivers/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

boot_sect.bin: boot/boot_sect.asm
	nasm ./boot/boot_sect.asm -f bin -o ./boot_sect.bin

clean:
	rm *.bin *.o mos-image
