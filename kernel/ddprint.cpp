#include "ddprint.h"
#include "print.h"

#include "ddstring.h"

void Print::printString(String& message) {
	::printString(message.getChars());
}

void Print::printString(const char* message) {
	::printString(message);
}

void Print::printChar(char chr) {
	::printChar(chr);
}

void Print::printHex(unsigned int hex) {
	::printHex(hex);
}
