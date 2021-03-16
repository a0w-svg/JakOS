#include "./include/port.h"

uint8_t port_byte_in(uint16_t port)
{
    uint8_t result;
     asm volatile("inb %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}
void port_byte_out(uint16_t port, uint8_t data)
{
    asm volatile("outb %%al, %%dx" : : "a" (data), "d" (port));
}
uint16_t port_word_in(uint16_t port)
{
    uint16_t result;
    asm volatile("inw %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}
void port_word_out(uint16_t port, uint16_t data)
{
    asm volatile("outw %%ax, %%dx" : : "a" (data), "d" (port));
}
uint32_t port_long_in(uint16_t  port)
{
    unsigned data;
    asm volatile("inl %1, %0" : "=a" (data) : "d"(port));
    return data;
}
void port_long_out(uint16_t port, uint32_t data)
{
    asm volatile("outl %0, %1" : : "a"(data), "d"(port));
}