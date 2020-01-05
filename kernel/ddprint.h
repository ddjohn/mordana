#ifndef DD_PRINT_H
#define DD_PRINT_H

#include "ddobject.h"

class String;
class Print {
    public:
        static void printString(String& message);
        static void printString(const char* message);
        static void printChar(char chr);
        static void printHex(unsigned int hex);

    private:
};

#endif //DD_PRINT_H
