#ifndef MEM_H
#define MEM_H

#include "../../common/include/types.h"

void mem_cp(char *src, char *dest, int bytes_n);
void mem_set(uint8 *dest, uint8 val, uint32 length);
#endif