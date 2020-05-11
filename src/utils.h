#ifndef UTILS_H
#define UTILS_H

#include "common.h"

void mem_cp(char *src, char *dest, int bytes_n);
void mem_set(uint8 *dest, uint8 value, uint32 len);
void int_to_ascii(int num, char str[]);
#endif