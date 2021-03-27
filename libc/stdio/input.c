#include "../include/stdio.h"
#include "../../drivers/include/keyboard.h"

void gets(char* buf, unsigned long size)
{
    get_string(buf, size);
}

char getch()
{
    return get_char();
}