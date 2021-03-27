#include "./include/draw.h"
#include "../drivers/include/screen.h"
#include "../common/include/types.h"

void DrawLine(uint8_t length, uint8_t color)
{
    printk("\n");
    for(size_t i = 0; i <= length; i++)
    {
        printk_putchar(' ', color);
    }
    printk("\n");
}
