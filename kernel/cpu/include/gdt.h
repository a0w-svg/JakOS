#ifndef GDT_H
#define GDT_H

#include <stdint.h>


extern void gdt_flush();

void set_gdt_gate(int num, unsigned long base, unsigned long limit,
     uint8_t access, uint8_t gran);

void init_gdt();



#endif