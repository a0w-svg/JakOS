#include "utils.h"

void mem_cp(char *src, char *dest, int bytes_n)
{
    for(int i = 0; i < bytes_n; i++)
    {
        *(dest + i) = *(src + i);
    }
}

void mem_set(uint8 *dest, uint8 value, uint32 len)
{
    uint8 *tmp = (uint8*)dest;
    for(; len != 0; len--)
    {
        *tmp++ = value;
    }
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