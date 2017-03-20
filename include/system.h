#ifndef __SYSTEM_H
#define __SYSTEM_H

void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
char *strcpy(char *dest, char *src);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

// reverse a string
void reverse(char *s);
// Implementation of itoa()
void itoa(int n, char *buffer, int base);

#endif