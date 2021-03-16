#include "./include/shell.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../../drivers/ports/include/serial_port.h"
#include "../../libc/include/string.h"
#include "../../common/include/port.h"
#include "../../common/include/kpanic.h"
#include "../../libc/include/mem.h"
#include "../../libc/include/stdio.h"
#include "../../drivers/disks/include/ata.h"

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
    printk("Main developer: a0w_svg\n");
    printk("Translator: Kurokawa\n");
    printk("Testers: Saroshi, Jakub, Kurokawa\n");
    printk("By JakOS Team\n");
  }
  else if(strcmp(input_us, "XMAS") == 0)
  {
    printk_c("     *      \n", CYAN_ON_BLACK);
    printk("    *&*     \n");
    printk("   *!*^*    \n");
    printk("  *!***!*   \n");
    printk(" **s******  \n");
    printk_c("    (_)     \n", BROWN_ON_BLACK);
    printk_c("  The creators of JakOS wish you a Merry Christmas :)\n", GREEN_ON_BLACK);
  }
  else if(strcmp(input_us, "CLEAN") == 0)
  {
    screen_clean();
  }
  
  else if(strcmp(input_us, "TEST") == 0)
  {
    uint32_t* target = 0;
    read_sectors_ata_pio(target, 0x0, 1);
    for(int i = 0; i < 128; i++)
    {
      printf("%x ", target[i] & 0xFF);
      printf("%x ", (target[i] >> 8) & 0xFF);
    }
    printf("\n Writing 0...\n");
    uint32_t bwrite[512];
    for(int i = 0; i < 512; i++)
    {
        bwrite[i] = 0;
    }
    write_sectors_ata_pio(0x0, 0, bwrite);
    printf("\n reading\n");
    read_sectors_ata_pio(target, 0x0, 1);
    int i = 0;
    while(i < 128)
    {
        printf("%d ", target[i] & 0xFF);
        printf("%d ", (target[i] >> 8) & 0xFF);
        i++;
    }
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