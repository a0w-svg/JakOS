#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define KERNEL_CS 0x08
// idt gate struct
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
/**************************************************
* Set idt gate max 256 gates // interrupts
**************************************************/
void idt_set_gate(int n, uint32_t handler);
/************************************************
 * Initialize Interrupt Descritor Table
*************************************************/
void idt_init();
#endif
