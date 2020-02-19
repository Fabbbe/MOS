/* Screen drivers
 *
 * This file includes functions for printing aswell as terminal control
 */

#include <stddef.h>
#include <stdint.h>

#include <io.h>
#include <video/screen.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void __stack_chk_fail() {
	//terminalPrint("HAHA");
}

static inline uint16_t 
vgaEntry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

static inline uint16_t 
getScreenOffset(int col, int row) {
	return 2*(row * MAX_COLS + col);
}

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;


void terminalClear() {
	for (size_t y = 0; y < MAX_ROWS; ++y) {
		for (size_t x = 0; x < MAX_COLS; ++x) {
			terminalPutCharAt(' ', x, y);
		}
	}
}

void terminalScroll() {
	// Shift every entry up one row
	for (uint16_t i = MAX_COLS; i < MAX_ROWS*MAX_COLS; ++i) {
		terminalBuffer[i-MAX_COLS] = terminalBuffer[i];
	}
	// Clear the bottom row
	for (uint16_t i = MAX_COLS*(MAX_ROWS-1); i < MAX_ROWS*MAX_COLS; ++i) {
		terminalBuffer[i] = vgaEntry(' ', terminalColor);
	}
}

void initTerminal() {
	/* Clears the screen and inits all terminal values */
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = 0x0f;
	terminalBuffer = (uint16_t*) VIDEO_ADDRESS;
	terminalClear();
}

void terminalPutCharAt (char c, size_t x, size_t y) {
	const size_t index = y*MAX_COLS + x;
	terminalBuffer[index] = vgaEntry(c, terminalColor);
	setCursor(getScreenOffset(x,y)+2);
}

void terminalPutChar (char c) {
	switch (c) {
		case '\n': // Newline charachter
			if (++terminalRow == MAX_ROWS) {
				--terminalRow;
				terminalScroll();
			}
			terminalColumn = 0;
			setCursor(getScreenOffset(terminalColumn,terminalRow));
			return;
		default:
			break;
	}

	terminalPutCharAt(c, terminalColumn, terminalRow);
	if (++terminalColumn == MAX_COLS) {
		terminalColumn = 0;
		if (++terminalRow == MAX_ROWS) {
			--terminalRow;
			terminalScroll();
		}
	}
}

void terminalReverseDelete() {
	terminalColumn -= 1;
	terminalPutCharAt(' ', terminalColumn, terminalRow);
	setCursor(getScreenOffset(terminalColumn,terminalRow));
}

void terminalPrint (const char* str) {
	for (size_t i = 0; str[i] != 0x00; ++i) {
		terminalPutChar(str[i]);
	}
}

void terminalPrintByte (uint8_t c) {
	 char hexOut[5] = "0x00\0";

	 {
	 uint8_t tmp = (c >> 4); // move all bits back 4 EX: 0101 1010 => 0000 0101
	 if (tmp > 0x9)
		 hexOut[2] += 7;
		 hexOut[2] += tmp;
	 }

	 {
	 uint8_t tmp = (c & 0xf); // EX: (0101 1010) & (0000 1111) => 0000 1010
	 if (tmp > 0x9) 
		 hexOut[3] += 7;
		 hexOut[3] += tmp;
	 }

	 terminalPrint(hexOut);
}

void enableCursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(REG_SCREEN_CTRL, 0x0A);
	outb(REG_SCREEN_DATA, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(REG_SCREEN_CTRL, 0x0B);
	outb(REG_SCREEN_DATA, (inb(0x3D5) & 0xE0) | cursor_end);
}
void disableCursor() {
	outb(REG_SCREEN_CTRL, 0x0A);
	outb(REG_SCREEN_DATA, 0x20);
}


unsigned int getCursor() {
	outb(REG_SCREEN_CTRL , 14);
	int offset = inb( REG_SCREEN_DATA ) << 8;
	outb(REG_SCREEN_CTRL , 15);
	offset += inb(REG_SCREEN_DATA);
	return offset*2;
}

void setCursor(uint16_t offset) {
	offset /= 2;
	// This is similar to getCursor but we write to the internal bytes
	// device registers.

	outb(REG_SCREEN_CTRL, 0x0E);
	outb(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
	outb(REG_SCREEN_CTRL, 0x0F);
	outb(REG_SCREEN_DATA, (uint8_t)(offset));
}
