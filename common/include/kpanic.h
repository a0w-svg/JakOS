#ifndef KPANIC_H
#define KPANIC_H

#include "types.h"
#include "../../drivers/include/screen.h"

#define PANIC(msg) kpanic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : kpanic_assert(__FILE__, __LINE__, #b))

extern void kpanic(const char *, const char *file, uint32_t line);
extern void kpanic_assert(const char *file, uint32_t line, const char *descript);

#endif