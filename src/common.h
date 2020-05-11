#ifndef COMMON_H
#define COMMON_H

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef char int8;
typedef short int16;
typedef int int32;

void out_byte(uint16 port, uint8 value);
uint8 in_byte(uint16 port);
uint16 in_word(uint16 port);

#define low_16(address) (uint16)((address) & 0xFFFF);
#define high_16(address) (uint16)(((address) >> 16 ) & 0xFFFF)
#define high_24(address) (uint16)(((address) >> 24) & 0xFFFF)
#endif