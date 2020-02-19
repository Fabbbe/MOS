# MOS
## The Original Mopperating System

A small x86 based operating system that currently does nothing. Run `make run` on 
linux to assemble and run the boot sector.

### Disclaimer
**Do not** try to use this as an actual operating system! Only test in emulators 
or virtual machines.

### Dependencies
This project uses **bochs** as a simple and fast VM to test the OS and **NASM** to 
compile the assembly code and **gcc** for C.

### Goals
I've implemented interrupt-based keyboard input which was a huge goal for me. Now
I'm looking at getting a simple filesystem up and running. Threading would also be
nice to have.

### Documentation and useful links

+ [Easy to understand but unfinished PDF](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
+ [OSDev wiki](https://wiki.osdev.org/)
+ [Interrupts](https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard)
+ [Interrupts 2: Electric Bogaloo](https://wiki.osdev.org/Interrupts_tutorial)

