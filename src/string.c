 #include "string.h"
 #include <stddef.h> 
 
 /* --- memory operations --- */
 
 void* memcpy(void* dest, const void* src, size_t n) {
     unsigned char* d = (unsigned char*)dest;
     const unsigned char* s = (const unsigned char*)src;
     while (n--) {
         *d++ = *s++;
     }
     return dest;
 }
 
 void* memmove(void* dest, const void* src, size_t n) {
     unsigned char* d = (unsigned char*)dest;
     const unsigned char* s = (const unsigned char*)src;
     if (d < s) {
         /* copy forward */
         while (n--) {
             *d++ = *s++;
         }
     } else if (d > s) {
         /* copy backward */
         d += n;
         s += n;
         while (n--) {
             *--d = *--s;
         }
     }
     return dest;
 }
 
 void* memset(void* ptr, int value, size_t num) {
     unsigned char* p = (unsigned char*)ptr;
     unsigned char v = (unsigned char)value;
     while (num--) {
         *p++ = v;
     }
     return ptr;
 }
 
 void* memchr(const void* ptr, int value, size_t num) {
     const unsigned char* p = (const unsigned char*)ptr;
     unsigned char v = (unsigned char)value;
     for (size_t i = 0; i < num; i++) {
         if (p[i] == v) {
             return (void*)(p + i);
         }
     }
     return NULL;
 }
 
 int memcmp(const void* ptr1, const void* ptr2, size_t num) {
     const unsigned char* a = (const unsigned char*)ptr1;
     const unsigned char* b = (const unsigned char*)ptr2;
     for (size_t i = 0; i < num; i++) {
         if (a[i] != b[i]) {
             return (int)a[i] - (int)b[i];
         }
     }
     return 0;
 }
 
 /* --- string operations --- */
 
 size_t strlen(const char* str) {
     size_t len = 0;
     while (str[len]) {
         len++;
     }
     return len;
 }
 
 char* strcpy(char* dest, const char* src) {
     char* ret = dest;
     while ((*dest++ = *src++)) {
         /* copy until null terminator */
     }
     return ret;
 }
 
 char* strncpy(char* dest, const char* src, size_t n) {
     size_t i;
     for (i = 0; i < n && src[i]; i++) {
         dest[i] = src[i];
     }
     for (; i < n; i++) {
         dest[i] = '\0';
     }
     return dest;
 }
 
 char* strcat(char* dest, const char* src) {
     char* d = dest + strlen(dest);
     while ((*d++ = *src++)) {
         /* append until null terminator */
     }
     return dest;
 }
 
 char* strncat(char* dest, const char* src, size_t max) {
     size_t dest_len = strlen(dest);
     size_t i = 0;
     /* leave room for final '\0' */
     while (src[i] && dest_len + i + 1 < max) {
         dest[dest_len + i] = src[i];
         i++;
     }
     dest[dest_len + i] = '\0';
     return dest;
 }
 
 int strcmp(const char* s1, const char* s2) {
     while (*s1 && *s1 == *s2) {
         s1++; s2++;
     }
     return (int)(unsigned char)*s1 - (int)(unsigned char)*s2;
 }
 
 int strncmp(const char* s1, const char* s2, size_t n) {
     for (size_t i = 0; i < n; i++) {
         unsigned char c1 = (unsigned char)s1[i];
         unsigned char c2 = (unsigned char)s2[i];
         if (c1 != c2) {
             return (int)c1 - (int)c2;
         }
         if (c1 == '\0') {
             return 0;
         }
     }
     return 0;
 }

 /* --- integer→string conversions --- */
 
 void itoa_base(int value, char* str, int base) {
     char* p = str;
     char* p1;
     char* p2;
     unsigned int abs_value;
 
     if (value < 0 && base == 10) {
         *p++ = '-';
         abs_value = (unsigned int)(-value);
     } else {
         abs_value = (unsigned int)(value);
     }
 
     if (base < 2 || base > 36) {
         *str = '\0';
         return;
     }
 
     p1 = p;
     do {
         int digit = abs_value % base;
         *p++ = (char)((digit < 10) ? ('0' + digit) : ('a' + digit - 10));
         abs_value /= base;
     } while (abs_value);
 
     *p = '\0';
     p2 = p - 1;
     while (p1 < p2) {
         char tmp = *p1;
         *p1++ = *p2;
         *p2-- = tmp;
     }
 }
 
 void itoa(int value, char* str) {
     itoa_base(value, str, 10);
 }
 