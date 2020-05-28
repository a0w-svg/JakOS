#ifndef IDT_H
#define IDT_H

#include "../../../common/include/types.h"

#define KERNEL_CS 0x08

typedef struct 
{
    uint16_t low_offs;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offs;
}__attribute__((packed)) idt_gate_t;

typedef struct 
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idt_register_t;

#define IDT_ENTR 256
idt_gate_t idt[IDT_ENTR];
idt_register_t idt_regs;

void idt_set_gate(int n, uint32_t handler);
void idt_init();


#endif
