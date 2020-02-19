/* 
 * The general idea of the keyboard driver will be to get the 
 * interrupt and forward it to the currently used application.
 */

#include <keyboard.h>
#include <io.h>
#include <video/screen.h>


// Keyboard handling function of focused app
void (*focusedKeyboardHandler)(char);

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

		focusedKeyboardHandler(keycode);
	}
}

void focusKeyboardHandler(void (*handler)(char)) {
	// Changes the function called by the keyboard interrupt
	focusedKeyboardHandler = handler;
} 

unsigned char readKey() { 
	unsigned char code = inb(REG_KEYBOARD_DATA);
	return code;
}
