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
void kmain()
{
  isr_init();
  irq_init();
  screen_clean();
  printk("welcome \n");
  printk("Succesully boot JakoS\n");
  // test interupts
  printk("Testing Interrupts\n");
  asm volatile("int $0x1");
}

void input(char *input_us)
{
  if(strcmp(input_us, "END") == 0)
  {
    printk("halt\n");
    asm volatile("hlt");
  }
  printk("You said: ");
  printk(input_us);
  printk("\n>");
}
