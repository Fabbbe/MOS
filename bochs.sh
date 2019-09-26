#!/bin/sh

# This compiles and runs the operating system on bochs
nasm ./boot/boot_sect.asm -f bin -o ./boot_sect.bin
bochs -q
