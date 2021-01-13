#include "./include/mem.h"

void* memcpy_w(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}
void memcpy (uint8_t *src, uint8_t *dest, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        *(dest + i) = *(src + i);
    }
}
void* mem_set(void *dest,  int val, size_t length)
{
     uint8_t* buf = (uint8_t*)val;
     for(size_t i = 0; i < length; i++)
        buf[i] = (uint8_t)val;
    return dest;
}
int memcmp(const void* aptr, const void* bptr, size_t size)
{
    const uint8_t* a = (uint8_t*)aptr;
    const uint8_t* b = (uint8_t*)bptr;
    for(size_t i = 0; i < size; i++)
    {
        if(a[i] < b[i])
            return -1;
        else if(b[i] < a[i])
            return 1;
    }
    return 0;
}
void* memmove(void* dstpt, const void* scrptr, size_t size)
{
    uint8_t* dst = (uint8_t*)dstpt;
    const uint8_t* src = (const uint8_t*)scrptr;
    if(dst < src)
    {
        for(size_t i = 0; i < size; i++)
            dst[i] = src[i];
    }
    else
    {
        for(size_t i = size; i != 0; i--)
            dst[i-1] = src[i-1];
    }
    return dstpt;
}

