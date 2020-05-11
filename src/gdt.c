#include "gdt.h"
#include "utils.h"
 struct gdt_ptr{
    uint16 limit;
    uint32_s base;
}__attribute__((packed));
 struct gdt_entry{
    uint16 limit_low;
    uint16 base_low;
    uint8 base_middle;
    uint8 access;
    uint8 granularity;
    uint8 base_high;
}__attribute__((packed));
struct gdt_entry gdt[3];
struct gdt_ptr gp;
void gdt_set_gate(int num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    gdt[num].base_low = low_16(base);
    gdt[num].base_middle = high_16(base);
    gdt[num].base_high = high_24(base);

    gdt[num].limit_low = low_16(limit);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
extern void gdt_flush();
void gdt_init()
    {
        gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
        gp.base = (uint32_s)&gdt;

        gdt_set_gate(0, 0, 0, 0, 0);
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
        //gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	    //gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
        gdt_flush();
    }

