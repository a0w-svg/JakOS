#ifndef MEM_H
#define MEM_H
#include <stddef.h>
#include "../../common/include/types.h"

void mem_cp(char *src, char *dest, int bytes_n);
void mem_set(uint8_t *dest, uint8_t val, uint32_t length);
uint32_t malloc(size_t size, int align, uint32_t *phys_address);
#endif