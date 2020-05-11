#include "screen.h"
//#include "gdt.h"
#include "isr.h"
//#include "idt.h"
#include "utils.h"
#include "idt.h"
void kmain()
{
  //isr_init();
  idt_init();
  //gdt_init();
  
  screen_clean();
  screen_write("welcome \n");
  //idt_init();
  //__asm__("sti");
  //int a = 0;
  int b = 2/0;
 //__asm__("int $0x1");

  screen_write("Succesully boot JakoS");
}
