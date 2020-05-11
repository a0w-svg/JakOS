#include "isr.h"
#include "idt.h"
#include "screen.h"
#include "utils.h"

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
void isr_init()
{
    idt_set_gate(0, (uint32)isr0);
    idt_set_gate(1, (uint32)isr1);
    idt_set_gate(2, (uint32)isr2);
    idt_set_gate(3, (uint32)isr3);
    idt_set_gate(4, (uint32)isr4);
    idt_set_gate(5, (uint32)isr5);
    idt_set_gate(6, (uint32)isr6);
    idt_set_gate(7, (uint32)isr7);
    idt_set_gate(8, (uint32)isr8);
    idt_set_gate(9, (uint32)isr9);
    idt_set_gate(10, (uint32)isr10);
    idt_set_gate(11, (uint32)isr11);
    idt_set_gate(12, (uint32)isr12);
    idt_set_gate(13, (uint32)isr13);
    idt_set_gate(14, (uint32)isr14);
    idt_set_gate(15, (uint32)isr15);
    idt_set_gate(16, (uint32)isr16);
    idt_set_gate(17, (uint32)isr17);
    idt_set_gate(18, (uint32)isr18);
    idt_set_gate(19, (uint32)isr19);
    idt_set_gate(20, (uint32)isr20);
    idt_set_gate(21, (uint32)isr21);
    idt_set_gate(22, (uint32)isr22);
    idt_set_gate(23, (uint32)isr23);
    idt_set_gate(24, (uint32)isr24);
    idt_set_gate(25, (uint32)isr25);
    idt_set_gate(26, (uint32)isr26);
    idt_set_gate(27, (uint32)isr27);
    idt_set_gate(28, (uint32)isr28);
    idt_set_gate(29, (uint32)isr29);
    idt_set_gate(30, (uint32)isr30);
    idt_set_gate(31, (uint32)isr31);

    idt_init();
}

void isr_handler(registers *r) {
     int int_no = r->int_no;
    if(int_no != 0x0)
    {
        while(1)
        {
            screen_write("write");
        }
    }


}