#ifndef __STD_STRING_H
#define __STD_STRING_H

#include <std/memory.h>

int strlen(const char *str);
char *strcpy(char *dest, char *src);
int strcmp(const char *dst, char *src);
void strcat(void *dest,const void *src);
/* reverse a string */
void reverse(char *s);

#endif