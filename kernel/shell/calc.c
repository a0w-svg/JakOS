#include "./include/calc.h"
#include "../../drivers/include/keyboard.h"
#include "../../drivers/include/screen.h"
#include "../../libc/include/string.h"
#include "../../libc/include/stdio.h"

void calc()
{
    printf("Calculator:\n");
    while(1)
    {
        printf("\t\toptions\n");
        printf("\t\t\t= - add two numbers\n");
        printf("\t\t\t- - subtract two numbers\n");
        printf("\t\t\t* - multiply two numbers\n");
        printf("\t\t\t/ - divide two numbers\n");
        printf("\t\t\tQ - quit\n");
        printf("enter your option: ");
        char *in = get_string(3);
        if(*in != 'Q')
        {
            int result = 0;
            if(*in == '=')
            {
                printf("enter the first number: ");
                char *first = get_string(20);
                int a = atoi(first);
                printf("enter the second number: ");
                char *second = get_string(20);
                int b = atoi(second);
                result = a + b;
            }
            if(*in == '-')
            {
                printf("enter the first number: ");
                char *first = get_string(20);
                int a = atoi(first);
                printf("enter the second number: ");
                char *second = get_string(20);
                int b = atoi(second);
                result = a - b;
            }
            if(*in == '*')
            {
                printf("enter the first number: ");
                char *first = get_string(20);
                int a = atoi(first);
                printf("enter the second number: ");
                char *second = get_string(20);
                int b = atoi(second);
                result = a * b;
            }
            if(*in == '/')
            {
                printf("enter the first number: ");
                char *first = get_string(20);
                int a = atoi(first);
                printf("enter the second number: ");
                char *second = get_string(20);
                int b = atoi(second);
                result = a / b;
            }
            if(*in == '%')
            {
                printf("enter the first number: ");
                char *first = get_string(20);
                int a = atoi(first);
                printf("enter the second number: ");
                char *second = get_string(20);
                int b = atoi(second);
                result = a % b;
            }
            printf("result: %d\n", result);
        }
        else
        {
            break;
        }
    }
}