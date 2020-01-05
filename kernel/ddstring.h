#ifndef DD_STRING_H
#define DD_STRING_H

#define MAX_STRING_LENGTH 64

#include "ddobject.h"

class String {
    public:
        String();
        String(const char* data);
        //String(const String& s);
        //String& operator = (const String& s );
        ~String();
        String& operator+(String& other);

        const char* getChars();

    private:
        char data[MAX_STRING_LENGTH + 1];
        int len;
};

#endif //DD_STRING_H