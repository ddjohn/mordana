#ifndef STRING_H
#define STRING_G

#include <stddef.h>

size_t strlen(char* str);
int strcmp(const char* s1, const char* s2);
void *memcpy(void* dest, const void* src, size_t n);
void *memmove(void* dest, const void* src, size_t n);

#endif //STRING_H