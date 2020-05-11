#ifndef IDT_H
#define IDT_H

#include "common.h"
#define IDT_SIZE 256
typedef struct 
{
    uint16 offset_low;
    uint16 sel;
    uint8 zero;
    uint8 type_attr;
    uint8 offset_high;
}__attribute__((packed)) idt_entry;

typedef struct 
{
    uint16 limit;
    uint32 base;
}__attribute__((packed)) idt_regs;

idt_entry idt[IDT_SIZE];
idt_regs idt_reg;
extern void idt_flush();
void idt_init();
void idt_set_gate(int n, uint32 handler);

#endif