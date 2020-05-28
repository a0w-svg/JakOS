#ifndef PAGING_H
#define PAGING_H

#include "../../cpu/include/isr.h"
#include "../../../common/include/types.h"


typedef struct k_page
{
    uint32_t present : 1;
    uint32_t rw : 1;
    uint32_t user : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t unused : 7;
    uint32_t frame : 20;
}k_page_t;

typedef struct k_page_table
{
    k_page_t pages[1024];
}k_page_table_t;

typedef struct k_page_dir
{
    k_page_table_t *k_tables[1024];
    uint32_t k_tables_phys[1024];
    uint32_t phys_addr;
}k_page_dir_t;

void init_paging();
void switch_page_dir(k_page_dir_t *new_p);
k_page_t *get_kpage(uint32_t addr, int make, k_page_dir_t *directory);
void page_err(registers_t reg);

#endif