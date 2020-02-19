#pragma once

#include <stddef.h>
#include <stdint.h>

// All keycodes:

#define KEYCODE_1 0x02
#define KEYCODE_2 0x03
#define KEYCODE_3 0x04
#define KEYCODE_4 0x05
#define KEYCODE_5 0x06
#define KEYCODE_6 0x07
#define KEYCODE_7 0x08
#define KEYCODE_8 0x09
#define KEYCODE_9 0x0A
#define KEYCODE_0 0x0B

#define KEYCODE_DASH 0X0C
#define KEYCODE_EQUALS 0X0D
#define KEYCODE_BACKSPACE 0X0E
#define KEYCODE_TAB 0X0F

#define KEYCODE_Q 0X10
#define KEYCODE_W 0X11
#define KEYCODE_E 0X12
#define KEYCODE_R 0X13
#define KEYCODE_T 0X14
#define KEYCODE_Y 0X15
#define KEYCODE_U 0X16
#define KEYCODE_I 0X17
#define KEYCODE_O 0X18
#define KEYCODE_P 0X19

#define KEYCODE_OPENSQUAREBRACKET 0X1A
#define KEYCODE_CLOSESQUAREBRACKET 0X1B

#define KEYCODE_ENTER 0X1C

#define KEYCODE_LCTRL 0X1D

#define KEYCODE_A 0X1E
#define KEYCODE_S 0X1F
#define KEYCODE_D 0X20
#define KEYCODE_F 0X21
#define KEYCODE_G 0X22
#define KEYCODE_H 0X23
#define KEYCODE_J 0X24
#define KEYCODE_K 0X25
#define KEYCODE_L 0X26

#define KEYCODE_SEMICOLON 0X27
#define KEYCODE_SINGLEQUOTE 0X28
#define KEYCODE_BACKTICK 0X29

#define KEYCODE_LSHIFT 0X2A
#define KEYCODE_BACKSLASH 0X2B

#define KEYCODE_Z 0X2C
#define KEYCODE_X 0X2D
#define KEYCODE_C 0X2E
#define KEYCODE_V 0X2F
#define KEYCODE_B 0X30
#define KEYCODE_N 0X31
#define KEYCODE_M 0X32

#define KEYCODE_COMMA 0X33
#define KEYCODE_PERIOD 0X34

#define KEYCODE_FORWARDSLASH 0X35
#define KEYCODE_RSHIFT 0X36

#define KEYCODE_KEYPADASTERISK 0X37
#define KEYCODE_LALT 0X38
#define KEYCODE_SPACE 0X39

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

#define REG_KEYBOARD_DATA 0x60
#define REG_KEYBOARD_CTRL 0x64


unsigned char readKey();
void focusKeyboardHandler(void (*handler)(char));
