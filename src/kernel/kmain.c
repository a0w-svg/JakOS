#include "../drivers/include/screen.h"
//#include "gdt.h"
#include "./cpu/include/isr.h"
#include "./cpu/include/idt.h"
#include "../common/include/types.h"
#include "../drivers/include/keyboard.h"
#include "./cpu/include/timer_interrupts.h"

void kmain()
{
  isr_init();
  
  screen_clean();
  screen_write("welcome \n");
  asm volatile("sti");
  init_timer(50);
  
    //init_keyboard();
  //screen_write("Succesully boot JakoS");
  
}
