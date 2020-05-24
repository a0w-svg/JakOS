#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#define low_16(address) (uint16_t)((address) & 0xFFFF);
#define high_16(address) (uint16_t)(((address) >> 16 ) & 0xFFFF)
#define high_24(address) (uint16_t)(((address) >> 24) & 0xFFFF)
#endif