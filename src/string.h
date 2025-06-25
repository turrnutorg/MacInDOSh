#ifndef STRING_H
#define STRING_H

#include <stddef.h>

/* --- memory operations --- */
void* memcpy(void* dest, const void* src, size_t n);
void* memmove(void* dest, const void* src, size_t n);
void* memset(void* ptr, int value, size_t num);
void* memchr(const void* ptr, int value, size_t num);
int   memcmp(const void* ptr1, const void* ptr2, size_t num);

/* --- string operations --- */
size_t strlen(const char* str);

char*  strcpy(char* dest, const char* src);
char*  strncpy(char* dest, const char* src, size_t n);

char*  strcat(char* dest, const char* src);
char*  strncat(char* dest, const char* src, size_t max);

int    strcmp(const char* s1, const char* s2);

/* --- integer→string conversions --- */
void itoa(int value, char* str);
void itoa_base(int value, char* str, int base);

#endif
