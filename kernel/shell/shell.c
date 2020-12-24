#include "./include/shell.h"
#include "./include/calc.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../../drivers/ports/include/serial_port.h"
#include "../../libc/include/string.h"
#include "../../common/include/port.h"
#include "../../common/include/kpanic.h"

void shell(char* input_us)
{
  if(strcmp(input_us, "SHUTDOWN") == 0)
  {
    printk("goodbye :(\n");
    port_word_out(0xB004, 0x2000);
    port_word_out(0x604, 0x2000);
    port_word_out(0x4004, 0x3400);

  }
  else if(strcmp(input_us, "HELP") == 0)
  {
    printk("list of commands:\n");
    printk("SHUTDOWN - shutdown computer\n");
    printk("EDIT - edit file todo - currently not working\n");
    printk("REMOVE - delete file todo -currently not working\n");
    printk("MOVE - move file to indicated path - todo currently not working\n");
    printk("CREDITS - display OS version and autors\n");
    printk("XMAS - display christmas tree\n");
    printk("CLEAN -clean screen\n");
    printk("CALC - simple calculator - todo currently not working\n");
  }
  else if(strcmp(input_us, "CREDITS") == 0)
  {
    printk("JakOS Version: 0.0.3 ALPHA\n");
    printk("Authors:\n");
    printk("Main developer: a3mx_w&sa\n");
    printk("Translator: Kurokawa\n");
    printk("Testers: Saroshi, Jakub, Kurokawa\n");
    printk("By JakOS Team\n");
  }
  else if(strcmp(input_us, "XMAS") == 0)
  {
    printk_color("     *      \n", CYAN, BLACK);
    printk("    *&*     \n");
    printk("   *!*^*    \n");
    printk("  *!***!*   \n");
    printk(" **s******  \n");
    printk_color("    (_)     \n", BROWN, BLACK);
    printk_color("  The creators of JakOS wish you a Merry Christmas :)\n", LIGHT_BLUE, BLACK);
  }
  else if(strcmp(input_us, "CLEAN") == 0)
  {
    screen_clean();
  }
  else if(strcmp(input_us, "TEST") == 0)
  {
    PANIC("Noob");
  }
  else
  {
    printk("wrong command please enter currect command\n");
    write_serial('a');
  }
  printk("\nJakOS>"); 
}

void return_shell()
{
    screen_clean();
}