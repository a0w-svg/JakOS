#include "./include/isr.h"
#include "./include/idt.h"
#include "../../drivers/include/screen.h"
#include "../../common/include/types.h"
#include "./include/timer_interrupts.h"
#include "../../libc/include/string.h"
isr_t interrupt_handler[256];
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
    set_idt_gate(0, (uint32)isr0);
    set_idt_gate(1, (uint32)isr1);
    set_idt_gate(2, (uint32)isr2);
    set_idt_gate(3, (uint32)isr3);
    set_idt_gate(4, (uint32)isr4);
    set_idt_gate(5, (uint32)isr5);
    set_idt_gate(6, (uint32)isr6);
    set_idt_gate(7, (uint32)isr7);
    set_idt_gate(8, (uint32)isr8);
    set_idt_gate(9, (uint32)isr9);
    set_idt_gate(10, (uint32)isr10);
    set_idt_gate(11, (uint32)isr11);
    set_idt_gate(12, (uint32)isr12);
    set_idt_gate(13, (uint32)isr13);
    set_idt_gate(14, (uint32)isr14);
    set_idt_gate(15, (uint32)isr15);
    set_idt_gate(16, (uint32)isr16);
    set_idt_gate(17, (uint32)isr17);
    set_idt_gate(18, (uint32)isr18);
    set_idt_gate(19, (uint32)isr19);
    set_idt_gate(20, (uint32)isr20);
    set_idt_gate(21, (uint32)isr21);
    set_idt_gate(22, (uint32)isr22);
    set_idt_gate(23, (uint32)isr23);
    set_idt_gate(24, (uint32)isr24);
    set_idt_gate(25, (uint32)isr25);
    set_idt_gate(26, (uint32)isr26);
    set_idt_gate(27, (uint32)isr27);
    set_idt_gate(28, (uint32)isr28);
    set_idt_gate(29, (uint32)isr29);
    set_idt_gate(30, (uint32)isr30);
    set_idt_gate(31, (uint32)isr31);

    //remap PIC
    out_byte(0x20, 0x11);
    out_byte(0xA0, 0x11);
    out_byte(0x21, 0x20);
    out_byte(0xA1, 0x28);
    out_byte(0x21, 0x04);
    out_byte(0xA1, 0x02);
    out_byte(0x21, 0x01);
    out_byte(0xA1, 0x01);
    out_byte(0x21, 0x0);
    out_byte(0xA1, 0x0);
    //init irq
    set_idt_gate(32, (uint32)irq0);
    set_idt_gate(33, (uint32)irq1);
    set_idt_gate(34, (uint32)irq2);
    set_idt_gate(35, (uint32)irq3);
    set_idt_gate(36, (uint32)irq4);
    set_idt_gate(37, (uint32)irq5);
    set_idt_gate(38, (uint32)irq6);
    set_idt_gate(39, (uint32)irq7);
    set_idt_gate(40, (uint32)irq8);
    set_idt_gate(41, (uint32)irq9);
    set_idt_gate(42, (uint32)irq10);
    set_idt_gate(43, (uint32)irq11);
    set_idt_gate(44, (uint32)irq12);
    set_idt_gate(45, (uint32)irq13);
    set_idt_gate(46, (uint32)irq14);
    set_idt_gate(47, (uint32)irq15);

    idt_init();
}

void isr_handler(registers_t r) {
    screen_write("received interrupt: ");
    char s[3];
    int_to_ascii(r.err_code, s);
    screen_write(s);
    screen_write("\n");
    screen_write(exception_messages[r.err_code]);
    screen_write("\n");
}

void reg_interrupt_handler(uint8 n, isr_t handler)
{
    interrupt_handler[n] = handler;
}

void irq_handler(registers_t r)
{
    if(r.int_no >= 40)
    {
        // slave mode
        out_byte(0xA0, 0x20);
        // master mode 
        out_byte(0x20, 0x20);
    }
    if(interrupt_handler[r.int_no] != 0)
    {
        isr_t handler = interrupt_handler[r.int_no];
        handler(r);
    }
}

/*void irq_init()
{
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
}
*/