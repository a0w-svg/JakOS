#include "./include/shell.h"
#include "./include/calc.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../../drivers/ports/include/serial_port.h"
#include "../../libc/include/string.h"
#include "../../common/include/port.h"
#include "../../libc/include/mem.h"
#include "../../libc/include/stdio.h"
#include "../../drivers/disks/include/ata.h"
#include "../../libc/include/math.h"
#include "../cpu/include/rtc.h"
#include "../mm/include/kmalloc.h"

void shell(char* input_us)
{
    time_t *time = kmalloc(sizeof(time_t));
    get_time(time);
    if(strcmp(input_us, "SHUTDOWN") == 0)
    {
      printf("goodbye :(\n");
      port_word_out(0xB004, 0x2000);
      port_word_out(0x604, 0x2000);
      port_word_out(0x4004, 0x3400);
    }
    else if(strcmp(input_us, "HELP") == 0)
    {
      printf("list of commands:\n");
      printf("SHUTDOWN - shutdown computer\n");
      printf("EDIT - edit file todo - currently not working\n");
      printf("REMOVE - delete file todo -currently not working\n");
      printf("MOVE - move file to indicated path - todo currently not working\n");
      printf("CREDITS - display OS version and autors\n");
      printf("XMAS - display christmas tree\n");
      printf("HELLO - check it yourself :)\n");
      printf("TEST - experimental features\n");
      printf("EASTER - check it yourself - todo currently halfway working\n");
      printf("CLEAN -clean screen\n");
      printf("CALC - simple calculator\n");
      printf("DATE - this command displays the date\n");
      printf("TIME - this command displays the time\n");
      printf("RANDOM - this command displays a random number\n");
    }
    else if(strcmp(input_us, "CREDITS") == 0)
    {
      printf("%z\t\t\t_      _     ___   ___\n", BLUE_ON_BLACK);  
      printf("%z\t\t    | |  __| | __/ _ \\/ ___|\n", RED_ON_BLACK);
      printf("%z\t\t _  | |/ _ | |/ / | | \\___ \\ \n", GREEN_ON_BLACK);
      printf("%z\t\t| |_| | (_|| | <| |_| |___) |\n", CYAN_ON_BLACK);
      printf("%z\t      \\___/\\ _,_|_|\\_\\\\___/|____/\n\n", MAGENTA_ON_BLACK);
      printf("JakOS Version: %z0.0.3 ALPHA\n", CYAN_ON_BLACK);
      printf("%zAuthors:\n", LIGHT_BLUE_ON_BLACK);
      printf("\t%zMain developer: %z a0w_svg\n", LIGHT_CYAN_ON_BLACK, RED_ON_BLACK);
      printf("\t%zTranslator: %zKurokawa\n", GREEN_ON_BLACK, LIGHT_MAGENTA_ON_BLACK);
      printf("\t%zTesters: %z Saroshi, Jakub, Kurokawa\n", LIGHT_CYAN_ON_BLACK, LIGHT_RED_ON_BLACK);
      printf("%zBy JakOS Team\n", BROWN_ON_BLACK);
    }
    else if(strcmp(input_us, "XMAS") == 0)
    {
      printf("%z     *      \n", GREEN_ON_BLACK);
      printf("%z    *&*     \n", CYAN_ON_BLACK);
      printf("%z   *!*^*    \n", LIGHT_BLUE_ON_BLACK);
      printf("%z  *!***!*   \n", RED_ON_BLACK);
      printf("%z **s******  \n", LIGHT_CYAN_ON_BLACK);
      printf("%z    (_)     \n", BROWN_ON_BLACK);
      printf("%z  The creators of JakOS wish you a Merry Christmas :)\n", LIGHT_RED_ON_BLACK);
    }
    else if(strcmp(input_us, "SERIALTEST") == 0)
    {
      printf("Write \"hello world\" to the serial port\n");
      write_serial_string("hello world");
      printf("Read data from the serial port\n%c", read_serial());
    }
    else if(strcmp(input_us, "CLEAN") == 0)
    {
      screen_clean();
    }
    else if(strcmp(input_us, "CALC") == 0)
    {
      calc();
    }
    else if(strcmp(input_us, "HELLO") == 0)
    {
      printf("Podaj imie: ");
      char name[80];
      get_string(name, 80);
      printf("Witaj %s", name);
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
    else if(strcmp(input_us, "RANDOM") == 0)
    {
      int max = rand();
      printf("%d\n", max);
    }
    else if(strcmp(input_us, "TIME") == 0)
    {
      printf("%ztime: %d:%d:%d", LIGHT_MAGENTA_ON_BLACK, time->hour + 1, time->minute, time->second);
      free(time);
    }
    else if(strcmp(input_us, "DATE") == 0)
    {
      printf("%zToday is: %d.%d.%d", LIGHT_MAGENTA_ON_BLACK, time->day, time->month, time->year+1);
    }
    else if(strcmp(input_us, "EASTER") == 0)
    {
      printf("%z               _      _     ___   ___\n", BLUE_ON_BLACK);  
      printf("%z              | |  __| | __/ _ \\/ ___|\n", RED_ON_BLACK);
      printf("%z           _  | |/ _ | |/ / | | \\___ \\ \n", GREEN_ON_BLACK);
      printf("%z          | |_| | (_|| | <| |_| |___) |\n", CYAN_ON_BLACK);
      printf("%z           \\___/\\ _,_|_|\\_\\\\___/|____/%z\n", MAGENTA_ON_BLACK);
    }
    else
    {
      printf("wrong command please enter currect command\n");
    }
    printf("\nJakOS>"); 
}
void return_shell()
{
    screen_clean();
}