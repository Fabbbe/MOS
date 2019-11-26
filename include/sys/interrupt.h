#pragma once

struct IDTDescr { // Interrupt Descriptor Table Descriptor

	uint16_t offsetLowerbits; 		// offset bits 0..15
	uint16_t selector; 				// code segment selector
	uint8_t zero;      				// unused, set to 0
	uint8_t typeAttr; 				// type flags and attributes
	uint16_t offsetHigherbits; 		// offset bits 16..31
};
struct IDTDescr IDT[256];
