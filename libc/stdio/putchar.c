#include "../include/stdio.h"
#include "../../drivers/include/screen.h"

int putchar(int n)
{
    char na = (char)n;
    printk_putchar(na);
    return n;
}