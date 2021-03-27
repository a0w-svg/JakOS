#include "../drivers/include/screen.h"
#include "./cpu/include/gdt.h"
#include "./cpu/include/isr.h"
#include "./cpu/include/idt.h"
#include "../common/include/types.h"
#include "./cpu/include/pit.h"
#include "./cpu/include/rtc.h"
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
#include "../libc/include/stdio.h"
#include "../boot/multiboot.h"
#include <stddef.h>

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))
void kmain(unsigned long magic, unsigned long addr)
{ 
  multiboot_info_t* mbi;
  screen_clean();
  printf("\t\t\t\t\tTEST configuration\n");
  if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    printf("Invalid magic number %x\n", (unsigned)magic);
  }
  mbi = (multiboot_info_t*)addr;
  printf("\tflags = %x\t", (unsigned)mbi->flags);
  if(CHECK_FLAG(mbi->flags, 0))
  {
    printf("mem_lower: %dKB \tmem_upper: %dKB\n", mbi->mem_lower, (unsigned) mbi->mem_upper);
  }
  if(CHECK_FLAG(mbi->flags, 1))
  {
    printf("\tBoot device: %x\t", (unsigned) mbi->boot_device);
  }
  if(CHECK_FLAG(mbi->flags, 2))
  {
    printf("kernel file: %s\n\n", (char*)mbi->cmdline);
  }

  heap_init();
  //init_paging();
  init_gdt();
  isr_init();
  irq_init();
  init_serial();
  printf("%zType HELP for a list of commands\n", LIGHT_BLUE_ON_BLACK);
  printf("%zJakOS>", GREEN_ON_BLACK);
  static char input[257];
  while(1)
  {
    input[0] = '\0';
    gets(input, 256);
    shell(input);
  }
  while(1);
}



