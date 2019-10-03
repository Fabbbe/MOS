CC=clang # clang gave me cleaner binaries

# default make target
all: mos-image

run: all
	bochs -q

mos-image: boot_sect.bin kernel.bin
	cat $^ > $@

kernel.bin: kernel_entry.o kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.o: kernel/kernel.c
	$(CC) -m32 -ffreestanding -O1 -o $@ -c $^

kernel_entry.o: boot/kernel_entry.asm
	nasm -f elf $@ $^

boot_sect.bin: boot/boot_sect.asm
	nasm ./boot/boot_sect.asm -f bin -o ./boot_sect.bin

clean:
	rm *.bin *.o
