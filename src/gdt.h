#ifndef GDT_H
#define GDT_H
#include "common.h"


extern void gdt_flush();
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_init();
#endif