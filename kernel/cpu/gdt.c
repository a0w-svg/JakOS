#include "./include/gdt.h"
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

gdt_entry_t gdt[5];
gdt_ptr_t gp;


void set_gdt_gate(int num, size_t base, size_t limit,
     uint8_t access, uint8_t gran)
{
    gdt_entry_t* gate = &gdt[num];
    gate->base_low = (base & 0xFFFF);
    gate->base_middle = (base >> 16) & 0xFF;
    gate->base_high = (base >> 24) & 0xFF;
    gate->limit_low = (limit & 0xFFFF);
    gate->granularity = ((limit >> 16) & 0x0F);
    gate->granularity |= (gran & 0xF0);
    gate->access = access;
}

void init_gdt()
{
   gp.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gp.base = &gdt[0];
    //NULL descriptor
   set_gdt_gate(0, 0, 0, 0, 0);
    // Code segment
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    //Data segment
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // user mode code segment
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // user mode data segment
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    // flush gdt
    gdt_flush();
}
