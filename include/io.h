/* 
 * A set of assembly I/O wrapper functions meant to make hardware programming a
 * lot easier
 *
 */

static __inline unsigned char
inb (unsigned short int port) {
	unsigned char result;
	__asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
} 
static __inline void
outb (unsigned short int port, unsigned char value) {
	__asm__ ("out %%al, %%dx" : : "a" (value), "d" (port));
} 
