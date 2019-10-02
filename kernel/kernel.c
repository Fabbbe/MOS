void main() {
	char* video_memory = (char*) 0xb8000;

	for (int i = 0; i < 2048; ++i) {
		*video_memory = '#'; // print # to the screen
		++video_memory;
		*video_memory = 0x0f; // make # white on black
		++video_memory;
	}
}
