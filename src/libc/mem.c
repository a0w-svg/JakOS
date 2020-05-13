#include "./include/mem.h"

void mem_cp(char *src, char *dest, int bytes_n)
{
    for(int i = 0; i < bytes_n; i++)
    {
        *(dest + i) = *(src + i);
    }
}

void mem_set(uint8 *dest, uint8 val, uint32 length)
{
     uint8 *temp = (uint8 *)dest;
    for ( ; length != 0; length--) *temp++ = val;
}