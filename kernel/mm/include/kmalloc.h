#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>
#include <stddef.h>

int heap_init(void);
void *kmalloc(size_t size);
void free(void *bp);
void *realkalloc(void *pointer, size_t size);

extern void *heap;
#define HEAP_SIZE (1 << 22)

#endif