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
#include <stddef.h>

void kmain()
{
  init_gdt();
  isr_init();
  irq_init();
  heap_init();
  screen_clean();
  beep();
  
  printk("welcome \n");
  printk("Successfully booted JakOS\n");
  printk("Type HELP for a list of commands\n");
  printk("JakOS>"); 
}

void input(char *input_us)
{
  if(strcmp(input_us, "SHUTDOWN") == 0)
  {
    printk("halt\n");
    asm volatile("hlt");
  }
  else if(strcmp(input_us, "HELP") == 0)
  {
    printk("list of commands:\n");
    printk("SHUTDOWN - shutdown computer\n");
    printk("EDIT - edit file todo - currently not working\n");
    printk("REMOVE - delete file todo -currently not working\n");
    printk("MOVE - move file to indicated path - todo currently not working\n");
    printk("CREDITS - display OS version and autors\n");
    printk("CALC - simple calculator\n");
  }
  else if(strcmp(input_us, "CREDITS") == 0)
  {
    printk("JAKOS Version: 0.0.2 ALFA \n");
    printk("Autors: \n");
    printk("Main programmist: a0w-svg \n");
    printk("translator: Kobokue \n");
    printk("testers: SaroshiPL and JakubLeonardo \n");
  }
  else
  {
    printk("wrong command please enter currect command\n");
  }
  printk("\nJakOS>");
}

