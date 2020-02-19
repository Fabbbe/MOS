/*
 * The main kernel file and entrypoint of the entire OS.
 *
 * Author: Fabian Beskow
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 *
 */

#include <stddef.h> 
#include <stdint.h>

#include <io.h>
#include <keyboard.h>
#include <video/screen.h>
#include <sys/interrupt.h>

#include "shell.h"

void idt_init(void) {
	extern int keyboard_handler();
	extern int load_idt();
	unsigned long keyHandlerAdress;
	unsigned long idtAddress;
	unsigned long idtPtr[2];

	keyHandlerAdress = (unsigned long)keyboard_handler;
	IDT[0x21].offsetLowerbits = keyHandlerAdress & 0xffff;
	IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0x21].zero = 0;
	IDT[0x21].typeAttr = 0x8e; /* INTERRUPT_GATE */
	IDT[0x21].offsetHigherbits = (keyHandlerAdress & 0xffff0000) >> 16;

	// Reprogramming the PIC
	
	/*		Ports
	 *			PIC1	PIC2
	 * Command	0x20	0xA0
	 * Data		0x21	0xA1
	 */

	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	outb(0x21, 0x20);
	outb(0xA1, 0x28);

	outb(0x21, 0x00);
	outb(0xA1, 0x00);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0xff);
	outb(0xA1, 0xff);

	idtAddress = (unsigned int)IDT;
	idtPtr[0] = (sizeof (struct IDTDescr) * 256) + ((idtAddress & 0xffff) << 16);
	idtPtr[1] = idtAddress >> 16;
	
	load_idt(idtPtr);

	// KB init TODO: move this out?
	outb(0x21, 0xfd);
}

void kmain() {
	/* Entry point for the kernel! */

	idt_init(); // Initiate Interrupts

	initTerminal(); // initiate and clear terminal
	enableCursor(13, 15);

	terminalPrint(" -= Welcome to MOS =- \n");

	shellInit();
}
