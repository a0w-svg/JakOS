#ifndef SCREEN_H
#define SCREEN_H

#include <stddef.h>

//use this if you want clean a screen
void screen_clean();
#define printk(txt) printk_c(txt, 0)
void printk_c(const char *Txt, uint8_t Color);
//print numbers
int printk_putchar(char data, uint8_t Color);
void key_backspace();

#endif