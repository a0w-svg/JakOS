#include "idt.h"

void idt_set_gate(int num, uint32 handler)
{
    idt[num].offset_low = low_16(handler);
    idt[num].sel = 0x08;
    idt[num].zero = 0;
    idt[num].type_attr = 0x8E;
    idt[num].offset_high = high_16(handler);
}

void idt_init()
{
    idt_reg.limit = IDT_SIZE * sizeof(idt_entry) - 1;
    idt_reg.base = (uint32)&idt;
    mem_set(&idt, 0, sizeof(idt_entry)*256);
    idt_flush((uint32)&idt_reg);
}