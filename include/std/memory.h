#ifndef __STD_MEMORY_H
#define __STD_MEMORY_H

void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

#endif