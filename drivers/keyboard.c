
#include <keyboard.h>
#include <io.h>
#include <video/screen.h>

#define REG_KEYBOARD_DATA 0x60
#define REG_KEYBOARD_CTRL 0x64

void keyboardHandlerMain(void) {
	unsigned char status;
	char keycode;

	// End of Input
	outb(0x20, 0x20);

	status = inb(REG_KEYBOARD_CTRL);
	if (status & 0x01) { 
		keycode = inb(REG_KEYBOARD_DATA);
		if(keycode < 0) // if signed
			return;
		if(keycode == 0x10)
			terminalPutChar('Q');
	}
}

unsigned char readKey() { 
	unsigned char code = inb(REG_KEYBOARD_DATA);
	return code;
}
