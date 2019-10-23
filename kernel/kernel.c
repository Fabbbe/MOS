#include <stddef.h>
#include <stdint.h>

#include <io.h>
#include <video/screen.h>

void main() {
	/* Entry point for the kernel! */


	initTerminal();
	terminalPrint(" -= Welcome to MOS =- \n");
	enableCursor(13, 15);
	terminalPrint(" $ ");
}
