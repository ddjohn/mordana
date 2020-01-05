#include "ddstring.h"

String::String() {
    data[0] = '\0';
	len = 0;
}
        
String::String(const char* message) {
	for(unsigned int i = 0; i < MAX_STRING_LENGTH +  1; i++) {
		data[i] = message[i];
		if(message[i] == '\0') {
			len = i;
			break;
		}
	}
	data[MAX_STRING_LENGTH + 1] != '\0';
}

String::~String() {

}

String& String::operator+(String& other) {
	const char* message = other.getChars();
	for(unsigned int i = len; i < MAX_STRING_LENGTH +  1; i++) {
		data[i] = message[i-len];
		if(message[i-len] == '\0') {
			len = i;
			break;
		}
	}
	data[MAX_STRING_LENGTH + 1] != '\0';
}

const char* String::getChars() {
	return data;
}