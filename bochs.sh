#!/bin/sh

# This compiles and runs the operating system on bochs
clang -m32 -ffreestanding -O1 -c kernel/kernel.c -o kernel.o 
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary 
nasm ./boot/boot_sect.asm -f bin -o ./boot_sect.bin
cat boot_sect.bin kernel.bin > mos-image
bochs -q
