/**********************************************************
*               JakOS Project                             *
*                                                         *
*                                                         *
***********************************************************/

#include "./include/idt.h"
#include "../../common/include/types.h"

idt_gate_t idt[IDT_ENTR];

idt_register_t idt_regs;

void idt_set_gate(int n, uint32_t handler)
{
    idt_gate_t* gate = &idt[n];
    gate->low_offs = LOW_16(handler);
    gate->selector = KERNEL_CS;
    gate->always0 = 0;
    gate->flags = 0x8E;
    gate->high_offs = HIGH_16(handler);
}

void idt_init()
{
    idt_regs.base = (uint32_t) &idt;
    idt_regs.limit = IDT_ENTR * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_regs));
}