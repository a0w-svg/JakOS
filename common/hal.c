#include "./include/hal.h"

void enable_interrupts()
{
    __asm__("sti");
}

void disable_interrupts()
{
    __asm__("cli");
}