#include "./include/kpanic.h"
#include "../libc/include/stdio.h"
void kpanic(char * msg, char *file, uint32_t line)
{
    printf("%z%s : %s line: %d", RED_ON_BLACK, msg, file, line);
    while(1);
}
void kpanic_assert(char *file, uint32_t line, char *descript)
{
   printf("%z%s : line: %d : %s", RED_ON_BLACK, file, line, descript);
    while(1);
}