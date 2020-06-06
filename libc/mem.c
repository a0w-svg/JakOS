#include "./include/mem.h"

void memcpy (uint8_t *src, uint8_t *dest, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        *(dest + i) = *(src + i);
    }
}
void memset(uint8_t *dest, uint8_t val, uint32_t length)
{
     uint8_t *temp = (uint8_t *)dest;
    for( ; length != 0; length--) 
    {
        *temp++ = val;
    }
}

