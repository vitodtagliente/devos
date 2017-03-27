#include <std/string.h>

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

char *strcpy(char *dest, char *src) {
    char *orig = dest;
    while((*dest++ = *src++)!= '\0')
        ; // <<== Very important!!!
    return orig;
}

int strcmp(const char *dst, char *src)
{
    int i = 0;

    while ((dst[i] == src[i])) {
        if (src[i++] == 0)
            return 0;
    }

    return 1;
}

void strcat(void *dest,const void *src)
{
    memcpy((char*)((int)dest+(int)strlen((char*)dest)),(char*)src,strlen((char*)src));
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