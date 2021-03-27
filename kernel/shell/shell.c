#include "./include/shell.h"
#include "./include/calc.h"
#include "../../drivers/ports/include/serial_port.h"
#include "../../libc/include/string.h"
#include "../../common/include/port.h"
#include "../../libc/include/mem.h"
#include "../../libc/include/stdio.h"
#include "../../drivers/disks/include/ata.h"
#include "../../libc/include/stdlib.h"
#include "../cpu/include/rtc.h"
#include "../mm/include/kmalloc.h"
#include "../../libc/include/draw.h"
#include "../cpu/include/pit.h"

void shell(char* input_us)
{
    time_t *time = kmalloc(sizeof(time_t));
    get_time(time);
    if(strcmp(input_us, "SHUTDOWN") == 0)
    {
      printf("%zgoodbye :(\n", DARK_GREY_ON_BLACK);
      sleep(200);
      port_word_out(0xB004, 0x2000);
      port_word_out(0x604, 0x2000);
      port_word_out(0x4004, 0x3400);
    }
    else if(strcmp(input_us, "HELP") == 0)
    {
      printf("%zlist of commands:\n", LIGHT_MAGENTA_ON_BLACK);
      printf("\tSHUTDOWN - shutdown computer\n");
      printf("\tEDIT - edit file todo - currently not working\n");
      printf("\tREMOVE - delete file todo -currently not working\n");
      printf("\tMOVE - move file to indicated path - todo currently not working\n");
      printf("\tCREDITS - display OS version and autors\n");
      printf("\tXMAS - display christmas tree\n");
      printf("\tHELLO - check it yourself :)\n");
      printf("\tTEST - experimental features\n");
      printf("\tEASTER - check it yourself - todo currently halfway working\n");
      printf("\tCLEAN -clean screen\n");
      printf("\tCALC - simple calculator\n");
      printf("\tDATE - this command displays the date\n");
      printf("\tTIME - this command displays the time\n");
      printf("\tRANDOM - this command displays a random number\n");
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
      printf("\t%zMain developer: %z a0w_svg\n", GREEN_ON_BLACK, LIGHT_BLUE_ON_BLACK);
      printf("\t%zTranslator: %zKurokawa\n", GREEN_ON_BLACK, LIGHT_BLUE_ON_BLACK);
      printf("\t%zTesters: %z Saroshi, Jakub, Kurokawa\n", GREEN_ON_BLACK, LIGHT_BLUE_ON_BLACK);
      printf("\t%zBy JakOS Team\n", BROWN_ON_BLACK);
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
      clean();
    }
    else if(strcmp(input_us, "CALC") == 0)
    {
      calc();
    }
    else if(strcmp(input_us, "HELLO") == 0)
    {
      printf("Enter your name: ");
      char name[80];
      gets(name, 80);
      printf("Hi, %s", name);
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
      printf("%d", max);
      DrawLine(10, LIGHT_BLUE_ON_GREEN);
    }
    else if(strcmp(input_us, "TIME") == 0)
    {
      printf("%ztime: %d:%d:%d", LIGHT_MAGENTA_ON_BLACK, time->hour + 1, time->minute, time->second);
      free(time);
    }
    else if(strcmp(input_us, "DATE") == 0)
    {
      printf("%zToday is: %d.%d.%d", LIGHT_MAGENTA_ON_BLACK, time->day, time->month, time->year+1);
      free(time);
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
    printf("%z\nJakOS>", GREEN_ON_BLACK); 
}
void return_shell()
{
    clean();
}