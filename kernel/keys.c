#include "keys.h"

int getchar_char = GETCHAR_NOTWAITING;

int kernel_getchar() {
	getchar_char = GETCHAR_WAITING;
	while (GETCHAR_WAITING == getchar_char) {
		__asm__("hlt");
	}

	int chr = getchar_char;
	getchar_char = GETCHAR_NOTWAITING;
	return chr;
}

void handleAsciiCode(char asciicode) {
	if(GETCHAR_WAITING == getchar_char) {
		getchar_char = asciicode;
	}
}

void handleScanCode(unsigned char scancode) {

	//printChar(' ');
	//printHex(scancode);
	//printChar(' ');
	static bool done = false;
	if(0xF0 == scancode) {
		done = true;
		return;
	}

	if(0xE0 == scancode) {
		return;
	}

	if(done == false) {
		char asciicode = keyboard[scancode];
		if (0 != asciicode) {
			handleAsciiCode(asciicode);
		}
	}
	done = false;
}
