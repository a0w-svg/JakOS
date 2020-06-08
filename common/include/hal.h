#ifndef HAL_H
#define HAL_H

void enable_interrupts();
void disable_interrupts();

#define NMI_DISABLE_BIT 0x80
#endif