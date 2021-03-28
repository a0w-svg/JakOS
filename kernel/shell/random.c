#include "./include/shell_func.h"
#include "../../libc/include/stdio.h"
#include "../../libc/include/stdlib.h"
#include "../../common/include/types.h"
#include "../../libc/include/string.h"

void check_out(int number)
{
    char ch[12];
    int i = 0;
    while (i < 3)
    {
        printf("The number I'm thinking about is: ");
        gets(ch, 10);
        int a = atoi(ch);
        if(a < number)
        {
            printf("This number is too small\n");
        }
        if(a > number)
        {
            printf("This number is too big\n");
        }
        if(a == number)
        {
            printf("You win\n");
            break;
        }
        i++;
    }
    
}
void random()
{  
    while(1)
    {
        int num = rand();
        printf("%zRandom game\n", LIGHT_MAGENTA_ON_BLACK);
        printf("\t%zyou only have 3 tries\n", RED_ON_BLACK);
        printf("\t\tA.Easy level 1-10\n");
        printf("\t\tB.medium 1-100\n");
        printf("\t\tC.hard level 1-1000\n");
        printf("\t\tQ.quit\n");
        printf("%zYour option: ", GREEN_ON_BLACK);
        char in[2];
        gets(in, 1);
        if(*in != 'Q')
        {
            if(*in == 'A')
            {
                check_out(1 + (num % 10));
            }
            if(*in == 'B')
            {
                check_out(1 + (num % 100));
            }
            if(*in == 'C')
            {
                check_out(1 + (num % 1000));
            }
        }
       else
       {
            printf("Goodbye");
            break;
       }
    }
}