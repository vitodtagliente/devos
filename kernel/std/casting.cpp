#include <std/casting.h>

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