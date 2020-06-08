#ifndef MEM_H
#define MEM_H
#include <stddef.h>
#include "../../common/include/types.h"

void memcpy (uint8_t *src, uint8_t *dest, int count);
void mem_set(void *dest, uint8_t val, uint32_t length);

#endif