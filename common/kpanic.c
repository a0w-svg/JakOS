#include "./include/kpanic.h"

void kpanic(const char * msg, const char *file, uint32_t line)
{
    printk_color(msg, RED, BLACK);
    printk("\n");
    printk_color(file, LIGHT_MAGENTA, BLACK);
    printk("    ");
    printk_dec(line);
    while(1);
}
void kpanic_assert(const char *file, uint32_t line, const char *descript)
{
    printk_color(file, RED, BLACK);
    printk("   ");
    printk_dec(line);
    printk_color(descript, CYAN, BLACK);
    while(1);
}