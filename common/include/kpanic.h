#ifndef KPANIC_H
#define KPANIC_H

#include "types.h"
#include "../../drivers/include/screen.h"
// displays the location of the error and the type of error
#define PANIC(msg) kpanic(msg, __FILE__, __LINE__);
// This is a macro that performs kernel panic if the value entered into it is other than 0
#define ASSERT(b) ((b) ? (void)0 : kpanic_assert(__FILE__, __LINE__, #b))
// Do not use these functions instead use the PANIC or ASSERT macros!
void kpanic(char * msg, char *file, uint32_t line);
void kpanic_assert(char *file, uint32_t line, char *descript);

#endif