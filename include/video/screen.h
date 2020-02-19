#pragma once

void initTerminal();

void terminalPutCharAt (char c, size_t x, size_t y);

void terminalPutChar (char c);

void terminalReverseDelete ();

void terminalPrint (const char* str);

void terminalPrintByte (uint8_t c);

void enableCursor(uint8_t cursor_start, uint8_t cursor_end);
void disableCursor();
unsigned int getCursor();
void setCursor(uint16_t offset);
