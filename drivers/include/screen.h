#ifndef SCREEN_H
#define SCREEN_H

#include "../../common/include/types.h"
#include <stddef.h>

//use this if you want clean a screen
void screen_clean();
#define printk(txt) printk_c(txt, 0)
void printk_c(const char *Txt, uint8_t Color);
//print numbers
int printk_putchar(char data, uint8_t Color);
void printk_hex(uint32_t n);
void printk_dec(uint32_t n);
void key_backspace();

#endif