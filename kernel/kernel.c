
unsigned int printPosition = 0;
void clear() {
	char* video_memory = (char*) 0xb8000; // The address for the video memory
	for (unsigned int i = 0; i < 2000; ++i) {
		*video_memory = ' ';
		video_memory += 2;
	}
}

void print(const char* str) {
	
	char* video_memory = (char*) 0xb8000 + printPosition*2; // The address for the video memory

	unsigned int i = 0;
	while (1) {
		if (str[i] == 0x00) {
			printPosition += i;
			break;
		}
		*video_memory = str[i]; // print char to the screen
		++video_memory;
		*video_memory = 0x0f; // make char white on black
		++video_memory;
		++i;
	}
}

void main() {
	/* Entry point for the kernel! */

	// The default screen size is 80x25 characters
	clear(); // Clears the screen
	print(" === MOPPERATING SYSTEM === ");
}
