#ifndef __SYSTEM_H
#define __SYSTEM_H

void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

#endif