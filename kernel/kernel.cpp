#include "kernel.h"
#include "keys.h"

//#include <ddtrace.h>
#include <ddprint.h>
#include <ddstring.h>
#include <stdbool.h>

#define BUF_SIZE 256

void* __gxx_personality_v0 = 0;
void* _Unwind_Resume = 0;

#define CLASS(c)
#define METHOD(m)

CLASS("Kernel");

Kernel::Kernel() {
	METHOD("Kernel()");

	Print::printString("\n");
	Print::printString("\n");
	Print::printString("Starting kernel!\n");
	Print::printString("\n");
}

Kernel::~Kernel() {
	METHOD("~Kernel()");
}

void Kernel::run() {
	METHOD("run()");

	while(true) {
		char buf[BUF_SIZE];
		unsigned int len = 0;

		Print::printString("\n$ ");

		for(unsigned int i = 0; i < BUF_SIZE - 1; ++i) {
			int chr = kernel_getchar();
			Print::printChar(chr);

			if ('\n' == chr) {
				break;
			}
			buf[len++] = chr;
		}
		buf[len] = 0;

		if(strcmp(buf, "exit") == 0) {
			break;
		} 
		else if(strcmp(buf, "obj") == 0) {
			Print::printHex(this->getNumOfObjects());
		} 
		else if(strcmp(buf, "") == 0) {
		} 
		else {
			Print::printString("Unknown command: ");
			Print::printString(buf);
			Print::printString("\r\n");
		}
	}
}

void main() {

	Kernel k;
	k.run();
}
