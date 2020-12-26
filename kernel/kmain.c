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


void kmain()
{
  heap_init();
  init_paging();
  init_gdt();
  isr_init();
  irq_init();
  init_serial();
  screen_clean();
  printk("\n");
  printk("welcome \n");
  printk("Successfully booted JakOS\n");
  printk("Type HELP for a list of commands\n");

  printk("JakOS>");
  while(1);
}



