#ifndef MEM_H
#define MEM_H
#include <stddef.h>
#include "../../common/include/types.h"

void memcpy (uint8_t *src, uint8_t *dest, int count);
void* memcpy_w(void* restrict dstptr, const void* restrict srcptr, size_t size);
void* mem_set(void *dest,  int val, size_t length);
int memcmp(const void* aptr, const void* bptr, size_t size);
void* memmove(void* dstpt, const void* scrptr, size_t size);
#endif