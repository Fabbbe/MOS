/* The main shell */

#include "shell.h"

#define COMMANDBUFFER_SIZE 255

uint8_t commandBuffer[COMMANDBUFFER_SIZE] = {0};
uint8_t cursorPosition = 0;

#define COMMAND_COUNT 2

const char* commandThing = "HELLO";

int parseCommand(char* commandString) {
	char commandList[2][10] = {
		"help\0",
		"?\0"
	};

	int commandLength;
	for(int i = 0; 
			commandString[i] != 0x00 && 
			commandString[i] != ' ' && 
			commandString[i] != '\n'; 
			++i) {
		++commandLength;
	}

	for(int i = 0; i < COMMAND_COUNT; ++i) {
		//terminalPrint(commandList[i]);

		for(int j = 0; 
				j < commandLength; ++j) {
			

			if (commandList[i][j] != commandString[j]) {
				break;
			}
			if (commandList[i][j+1] == 0x00) {
				terminalPrint("EXECUTED\n");
				return 0;
			}
		}
	}

	return 1;
}

void shellKeyboardHandler(char keycode) {
	if (keyboardMap[keycode] != 0x00) {
		terminalPutChar(keyboardMap[keycode]);
		commandBuffer[cursorPosition] = keyboardMap[keycode];
		++cursorPosition;
	}

	switch (keycode) {
		case KEYCODE_ENTER:
			// Check for commands to run

			if (parseCommand(commandBuffer)) {
				terminalPrint("Command not found: ");
				terminalPrint(commandBuffer);
			}
			// Clear command buffer
			for (uint8_t i = 0; i < COMMANDBUFFER_SIZE; ++i) {
				commandBuffer[i] = 0x00;
			}
			cursorPosition = 0;
			terminalPrint("$ ");
			break;
		case KEYCODE_BACKSPACE:
			if (cursorPosition > 0) {
				terminalReverseDelete();
				commandBuffer[cursorPosition] = 0x00;
				--cursorPosition;
			}
		default:
			break;
	}
	
}

void shellInit() {
	// Initialize the shell

	// Set up keyboard
	focusKeyboardHandler(&shellKeyboardHandler);
	terminalPrint("$ ");
}
