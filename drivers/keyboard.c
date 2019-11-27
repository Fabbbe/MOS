
#include <keyboard.h>
#include <io.h>
#include <video/screen.h>

#define REG_KEYBOARD_DATA 0x60
#define REG_KEYBOARD_CTRL 0x64

static char keyboardMap[256] = {
	  0,0,'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',  0, 
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',  
   	  0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', '`', 
	  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 
	  0,   0,  ' ', 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

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
		if(keyboardMap[keycode] == 0) 
			return;
		terminalPutChar(keyboardMap[keycode]);
	}
}

unsigned char readKey() { 
	unsigned char code = inb(REG_KEYBOARD_DATA);
	return code;
}
