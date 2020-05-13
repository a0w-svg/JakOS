#ifndef IDT_H
#define IDT_H

#include "../../../common/include/types.h"

#define KERNEL_CS 0x08

typedef struct 
{
    uint16 low_offs;
    uint16 selector;
    uint8 always0;
    uint8 flags;
    uint16 high_offs;
}__attribute__((packed)) idt_gate_t;

typedef struct 
{
    uint16 limit;
    uint32 base;
}__attribute__((packed)) idt_register_t;

#define IDT_ENTR 256
idt_gate_t idt[IDT_ENTR];
idt_register_t idt_regs;

void set_idt_gate(int n, uint32 handler);
void idt_init();


#endif
