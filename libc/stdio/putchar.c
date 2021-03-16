#include "../include/stdio.h"
#include "../../drivers/include/screen.h"

int putchar(char n, uint8_t Color)
{
    return printk_putchar(n, Color);
}