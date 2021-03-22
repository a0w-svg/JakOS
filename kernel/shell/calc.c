#include "./include/calc.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../../libc/include/string.h"
#include "../../libc/include/stdio.h"
int a = 0, b = 0, result = 0;
void calc()
{
    printf("Calculator:\n");
    while(1)
    {
        printf("\t\toptions\n");
        printf("\t\t\t= - add two numbers\n");
        printf("\t\t\t- - subtract two numbers\n");
        printf("\t\t\t; - multiply two numbers\n");
        printf("\t\t\t/ - divide two numbers\n");
        printf("\t\t\t\\ - remainer of dividing two numbers\n");
        printf("\t\t\tQ - quit\n");
        printf("enter your option: ");
        char in[2];
        get_string(in, 1);
        if(*in != 'Q')
        {
            if(*in == '=' || *in == '-' || *in == ';' || *in == '/' || *in == '\\')
            {
                printf("enter the first number: ");
                char first[20];
                get_string(first, 20);
                a = atoi(first);
                printf("enter the second number: ");
                char second[20];
                get_string(second, 20);
                b = atoi(second);
                if(*in == '=')
                    printf("result: %d\n", a + b);
                else if(*in == '-')
                    printf("result: %d\n", a - b);
                else if(*in == ';')
                    printf("result: %d\n", a * b);
                else if(*in == '/')
                {
                    if(a == 0 && b == 0)
                        printf("result: 0\n");
                    else
                        printf("result: %d\n", a / b);
                }
                else if(*in == '\\')
                    printf("result: %d\n", a % b);
            }
            else
            {
                printf("Wrong operation, try again\n");
            }
        }
        else
            break;
    }
}