#include "kernel.h"

#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 256

void * __gxx_personality_v0=0;
void * _Unwind_Resume =0;

Kernel::Kernel() {
	printString("Kernel");
}


Kernel::~Kernel() {
	printString("~Kernel");
}

void main() {
	printString("\n");
	printString("\n");
	printString("Starting kernel!\n");
	printString("\n");

	Kernel k;

	while(true) {
		char buf[BUF_SIZE];
		unsigned int len = 0;

		printString("$ ");

		for(unsigned int i = 0; i < BUF_SIZE - 1; ++i) {
			int chr = kernel_getchar();
			printChar(chr);

			if ('\n' == chr) {
				break;
			}
			buf[len++] = chr;
		}
		buf[len] = 0;

		if(strcmp(buf, "exit") == 0) {
			break;
		} 
		else {
			printString("Unknown command: ");
			printString(buf);
			printString("\r\n");
		}
	}
}

int kernel_getchar() {
	getchar_char = GETCHAR_WAITING;
	while (GETCHAR_WAITING == getchar_char) {
		__asm__("hlt");
	}

	int chr = getchar_char;
	getchar_char = GETCHAR_NOTWAITING;
	return chr;
}

void printCharAt(char chr, unsigned int color, unsigned int x, unsigned int y) {
	unsigned char* videomem_start = (unsigned char*)0xb8000;
	unsigned int offset = 160 * y + 2 * x;

	videomem_start[offset] = (unsigned char)chr;
	videomem_start[offset + 1] = color;
}

void printChar(char chr) {
	if(chr ==  '\n') {
		cursor.y++;
		cursor.x = 0;
	}
	else {
		printCharAt(chr, 0x09, cursor.x++, cursor.y);
	}
}

void printString(const char* message) {
	unsigned char* videomem = (unsigned char*)0xb8000;

	if(cursor.y >= 24) {
		memmove(videomem, videomem + 160, 160 * 24);
	}

	for(unsigned int i = 0; i < strlen((char*)message); i++) {
		printChar(message[i]);
	}
}

void printHex(unsigned int hex) {
	static int iters = 0;
	char hex_str[] = "0x00000000";

	for (int i = 9; i >= 2; --i) {
		unsigned char nibble = hex & 0xF;
		char hex_chr = '0' + nibble;
		if (nibble > 9) {
			hex_chr += 7;
		}
		hex_str[i] = hex_chr;
		hex /= 16;
	}
	printString(hex_str);

	iters++;
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
