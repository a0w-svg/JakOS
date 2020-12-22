#include "./include/calc.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../mm/include/kmalloc.h"

void calc(uint8_t *buf)
{
    int a = kmalloc(sizeof(int));
    int b = kmalloc(sizeof(int));

    uint8_t key;
    if(key == 6)
        key = 0;
}