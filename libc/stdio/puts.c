#include "../include/stdio.h"
#include "../../drivers/include/screen.h"
int puts(const char* string)
{
    return printf("%s\n", string);
}
void clean()
{
    screen_clean();
}