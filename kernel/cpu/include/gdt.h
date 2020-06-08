#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct 
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
}__attribute((packed)) gdt_entry_t;

typedef struct 
{
    uint16_t limit;
    gdt_entry_t *base;
}__attribute__((packed)) gdt_ptr_t;

extern void gdt_flush();

void set_gdt_gate(int num, unsigned long base, unsigned long limit,
     uint8_t access, uint8_t gran);

void init_gdt();



#endif