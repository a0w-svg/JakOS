#include "utils.h"

void mem_cp(char *src, char *dest, int bytes_n)
{
    for(int i = 0; i < bytes_n; i++)
    {
        *(dest + i) = *(src + i);
    }
}

void memory_set(uint8 *dest, uint8 val, uint32 len) {
    uint8 *temp = (uint8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

void int_to_ascii(int num, char str[])
{
    int i, sign;
    if((sign = num) < 0)
    {
        num = -num;
        i = 0;
        do {
            str[i++] = num % 10 + '0';
        }while ((num /= 10) > 0);

        if(sign < 0)
        {
            str[i++] = '-';
            str[i] = '\0';
        }
    }
}