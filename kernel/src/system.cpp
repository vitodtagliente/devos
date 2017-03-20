
#include <system.h>

void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

char *strcpy(char *dest, char *src) {
    char *orig = dest;
    while((*dest++ = *src++)!= '\0')
        ; // <<== Very important!!!
    return orig;
}

void reverse(char *s)
{
   char *j;
   int i = strlen(s);

   strcpy(j,s);
   while (i-- >= 0)
      *(s++) = j[i];
   *s = '\0';
}

/* itoa()
* converts an integer into a string */

void itoa(int n, char *buffer, int base)
{
   char *ptr = buffer;
   int lowbit;

   base >>= 1;
   do
   {
      lowbit = n & 1;
      n = (n >> 1) & 32767;
      *ptr = ((n % base) << 1) + lowbit;
      if (*ptr < 10)
         *ptr +='0';
      else
         *ptr +=55;
      ++ptr;
   }
   while (n /= base);
   *ptr = '\0';
   reverse (buffer);   /* reverse string */
}