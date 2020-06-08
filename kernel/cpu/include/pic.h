#ifndef PIC_H
#define PIC_H

#include <stdint.h>
#define PIC1 0x20 // master
#define PIC2 0xA0 // slave
#define PIC1_CMD PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_CMD PIC2
#define PIC2_DATA (PIC2+1)

#define PIC_EOI 0x20

void pic_send_EOI(uint8_t irq);
//reinitialize the PIC controllers
#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10
#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

void pic_remap(int offset_1, int offset_2);
void irq_set_mask(uint8_t IRQline);
void irq_clear_mask(uint8_t IRQline);

//isr and irr
#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define PIC_READ_IRR 0x0a
#define PIC_READ_ISR 0x0b

uint16_t __pic_get_irq_reg(int ocw3);
uint16_t pic_get_irr(void);
uint16_t pic_get_isr(void);

#endif