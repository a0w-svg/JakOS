#include "./include/calc.h"
#include "../../libc/include/string.h"
#include "../../libc/include/stdio.h"
#include "../../common/include/types.h"
int a = 0, b = 0, result = 0;
void calc()
{
    printf("%zCalculator:\n", LIGHT_MAGENTA_ON_BLACK);
    while(1)
    {
        printf("\t\t%zoptions\n", LIGHT_BLUE_ON_BLACK);
        printf("\t\t\t= - add two numbers\n");
        printf("\t\t\t- - subtract two numbers\n");
        printf("\t\t\t; - multiply two numbers\n");
        printf("\t\t\t/ - divide two numbers\n");
        printf("\t\t\t\\ - remainer of dividing two numbers\n");
        printf("\t\t\tQ - quit\n");
        printf("%zenter your option: ", GREEN_ON_BLACK);
        char in[2];
        gets(in, 1);
        if(*in != 'Q')
        {
            if(*in == '=' || *in == '-' || *in == ';' || *in == '/' || *in == '\\')
            {
                printf("%zenter the first number: ", GREEN_ON_BLACK);
                char first[20];
                gets(first, 20);
                a = atoi(first);
                printf("%zenter the second number: ", GREEN_ON_BLACK);
                char second[20];
                gets(second, 20);
                b = atoi(second);
                if(*in == '=')
                    printf("result: %d\n", a + b);
                else if(*in == '-')
                    printf("result: %d\n", a - b);
                else if(*in == ';')
                    printf("result: %d\n", a * b);
                else if(*in == '/')
                {
                    if(b == 0)
                        printf("result: 0\n");
                    else
                    {
                        printf("result: %d\n", a / b);
                    }
                }
                else if(*in == '\\')
                {
                    if(b == 0)
                        printf("result: 0\n");
                    else
                    {
                      printf("result: %d\n", a % b);
                    }
                }
            }
            else
            {
                printf("%zWrong operation, try again\n", RED_ON_BLACK);
            }
        }
        else
            break;
    }
}