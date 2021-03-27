#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>
/***************************************************
* loading a function wrritten in assembly that sets GDT
*****************************************************/
extern void gdt_flush();
/*****************************************************
* Sets the gate in gdt
* int num - gate number gdt
* size_t base - base address
* size_t limit - limit address
* uint8_t access - access mode
* unit8_t gran - granuality defines block size
******************************************************/
void set_gdt_gate(int num, size_t base, size_t limit,
     uint8_t access, uint8_t gran);
/******************************************************
* Initialize Global Descriptor Table
*******************************************************/
void init_gdt();



#endif