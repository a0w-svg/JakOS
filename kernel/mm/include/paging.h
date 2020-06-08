#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include "../../../drivers/include/screen.h"

typedef struct 
{
    uint32_t *page_dir;
    uint32_t page_dir_location;
    uint32_t *page_prev;
}page_t;

void paging_map(uint32_t virt, uint32_t phys_addr);
void init_paging();

#endif