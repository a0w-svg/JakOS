#include "./include/mem.h"

void mem_cp(char *src, char *dest, int bytes_n)
{
    for(int i = 0; i < bytes_n; i++)
    {
        *(dest + i) = *(src + i);
    }
}

void mem_set(uint8_t *dest, uint8_t val, uint32_t length)
{
     uint8_t *temp = (uint8_t *)dest;
    for ( ; length != 0; length--) *temp++ = val;
}
uint32_t free_memory_addr = 0x10000;
uint32_t malloc_k(size_t size, int align, uint32_t *phys_address)
{
    if(align == 1 && (free_memory_addr & 0xFFFFF000))
    {
        free_memory_addr &= 0xFFFFF000;
        free_memory_addr += 0x1000;
    }
    if(phys_address)
    {
        *phys_address = free_memory_addr;
    }
    uint32_t ret = free_memory_addr;
    free_memory_addr += size;
    return ret;
}