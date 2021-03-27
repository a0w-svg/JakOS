#include "./include/paging.h"
#include "../../libc/include/mem.h"
#include "../../libc/include/stdio.h"
page_t page;
void paging_map(uint32_t virt, uint32_t phys_addr)
{
    uint16_t id = virt >> 22;
    int l;
    for(l = 0; l < 1024; l++)
    {
        page.page_prev[l] = phys_addr | 3;
        phys_addr += 4096;
    }
    page.page_dir[id] = ((uint32_t)page.page_prev) | 3;
    page.page_prev = (uint32_t *)(((uint32_t)page.page_prev) + 4096);
    printf("\tMapping %x : %d : %x\n", virt, id, phys_addr);
}
void init_paging()
{
    mem_set(&page,  0, sizeof(page));
    printf("enable paging\n");
    page.page_dir = (uint32_t *)0x400000;
    page.page_dir_location = (uint32_t)page.page_dir;
    page.page_prev  = (uint32_t *)0x404000;

    mem_set(page.page_dir, 0 | 2, 1024);
    paging_map(0, 0);
    paging_map(0x400000, 0x400000);
    paging_map(0x800000, 0x800000);

    asm volatile("mov %%eax, %%cr3" : : "a"(page.page_dir_location));
    asm volatile("mov %cr0, %eax");
    asm volatile("or %eax, 0x80000001");
    asm volatile("mov %eax, %cr0");
}
