/* The main kernel file and entrypoint of the entire OS.
 *
 * TODO: Get interrupts working!!
 *   + Set up interrupt vector
 *
 */

#include <stddef.h> 
#include <stdint.h>

#include <io.h>
#include <keyboard.h>
#include <video/screen.h>
#include <sys/interrupt.h>

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

void main() {
	/* Entry point for the kernel! */

	initTerminal();
	enableCursor(13, 15);

	idt_init();

	terminalPrint(" -= Welcome to MOS =- \n");

	char lastKey = 0x00;
	while (1) {
		/*
		const char key = readKey();
		if (key != lastKey) {
			//terminalPrintByte(key);
			//terminalPrint("\n");
			lastKey = key;
		}
		*/
	}
}
