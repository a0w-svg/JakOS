#include "../drivers/include/screen.h"
#include "./cpu/include/gdt.h"
#include "./cpu/include/isr.h"
#include "./cpu/include/idt.h"
#include "../common/include/types.h"
#include "../drivers/include/keyboard.h"
#include "./cpu/include/pit.h"
#include "kmain.h"
#include "../libc/include/mem.h"
#include "../libc/include/string.h"
#include "../boot/multiboot.h"
#include "../drivers/include/speaker.h"
#include "./mm/include/kmalloc.h"
#include "../drivers/ports/include/serial_port.h"
#include "./mm/include/paging.h"
#include "./time/include/cmos.h"
#include "./shell/include/shell.h"
#include "../boot/multiboot.h"
#include <stddef.h>

typedef struct multiboot_memory_map {
  uint32_t size;
  uint32_t base_addr_low, base_addr_high;
  uint32_t length_low, length_high;
  uint32_t type;
} multiboot_map_t;

typedef multiboot_memory_map_t mmap_entry_t;
int kmain(multiboot_info_t* mboot, uint32_t magic)
{
  heap_init();
  init_paging();
  init_gdt();
  isr_init();
  irq_init();
  init_serial();
  mmap_entry_t* entry = mboot->mmap_addr;
  while(entry < (mboot->mmap_addr + mboot->mmap_length))
  {
    entry = (mmap_entry_t*) ((uint32_t) entry + 
    entry->size + sizeof(entry->size));
  }
  screen_clean();
  //beep();
  printk("memory size: ");
  printk_hex(entry->len);
  printk("\n");
  printk("welcome \n");
  printk("Successfully booted JakOS\n");
  printk("Type HELP for a list of commands\n");

  printk("JakOS>");
  while(1);
}



