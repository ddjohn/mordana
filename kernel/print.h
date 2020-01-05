#ifndef PRINT_H
#define PRINT_H

struct {
	unsigned char x;
	unsigned char y;
} cursor = {0, 0};

void printCharAt(char chr, unsigned int color, unsigned int x, unsigned int y);
void printChar(char chr);
extern "C" void printString(const char *str);
extern "C" void printHex(unsigned int hex);

#endif //PRINT_H
