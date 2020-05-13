#include "./include/types.h"

void out_byte(uint16 port, uint8 value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8 in_byte(uint16 port)
{
    uint8 ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}
uint16 in_word(uint16 port)
{
    uint16 ret;
    asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void out_word(uint16 port, uint16 data)
{
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (port));
}