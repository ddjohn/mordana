#include "print.h"
#include "string.h"

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
