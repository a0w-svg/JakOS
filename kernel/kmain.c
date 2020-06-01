#include "../drivers/include/screen.h"
//#include "gdt.h"
#include "./cpu/include/isr.h"
#include "./cpu/include/idt.h"
#include "../common/include/types.h"
#include "../drivers/include/keyboard.h"
#include "./cpu/include/timer_interrupts.h"
#include "kmain.h"
#include "../libc/include/mem.h"
#include "../libc/include/string.h"
#include "../boot/multiboot.h"

void kmain(multiboot_info_t *mbd)
{
  isr_init();
  irq_init();
  screen_clean();
  printk("Welcome! \n");
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
  if(strcmp(input_us, "HELP") == 0)
  {
    printk("list of commands:\n");
    printk("SHUTDOWN - shutdown computer\n");
    printk("EDIT - edit file todo – currently not working\n");
    printk("REMOVE - delete file todo – currently not working\n");
    printk("MOVE - move file to indicated path - todo – currently not working\n");
    printk("CREDITS - display OS version and authors\n");
    printk("CALC - simple calculator\n");

  }
  if(strcmp(input_us, "CALC") == 0)
  {
    printk("Welcome to JakOS calculator\n");
    printk("Options: /n");
    printk("1. add two numbers\n");
    printk("2. subtract two nubers\n");
    printk("3. divide two numbers\n");
    printk("4. multiply two numbers\n");
    input_us[0] = '\0';
    printk("your option: ");
    printk(input_us);
    int a, b, sum;
    char num[3];
    if(strcmp(input_us, "1") == 0)
    {
      printk("please enter first number: ");
      a =(int)input_us;
      printk(input_us);
      printk("please enter second number: ");
      b = (int)input_us;
      printk(input_us);
      sum = a + b;
      int_to_ascii(a, num);
      printk("score: ");
      printk(num);
      
    }
    if(strcmp(input_us, "2") == 0)
    {
      printk("please enter first number: ");
      a =(int)input_us;
      printk(input_us);
      printk("please enter second number: ");
      b = (int)input_us;
      printk(input_us);
    }
  }
  else
  {
    printk("wrong command please enter currect command\n");
  }
  printk("\nJakOS>");
}
