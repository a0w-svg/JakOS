#include "./include/gdt.h"

gdt_entry_t gdt[3];
gdt_ptr_t gp;


void set_gdt_gate(int num, unsigned long base, unsigned long limit,
     uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0xFFFF);
    
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void init_gdt()
{
   gp.limit = (sizeof(gdt_entry_t) * 3) - 1;
   gp.base = &gdt[0];
    //NULL descriptor
   set_gdt_gate(0, 0, 0, 0, 0);
    // Code segment
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    //Data segment
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_flush();
}
