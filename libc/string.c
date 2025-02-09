#include "./include/string.h"
#include <stdint.h>
#include <limits.h>

/****************************************
convert int type to ascii
int base atrributs:
    d - decimal number
    x - hexadecimal number
int d - source int type
char* buffer - destination product
******************************************/
void int_to_ascii(char* buffer, int base, int d)
{
    char* p = buffer;
    char* p1, *p2;
    unsigned long unsignedSrc = d;
    int divisor = 10; // decimal
    if(base == 'd' && d < 0)
    {
        *p++ = '-';
        buffer++;
        unsignedSrc = -d;
    }
    else if(base == 'x')
        divisor = 16; // hexadecimal 
    do{
        int remainer = unsignedSrc % divisor;
        *p++ = (remainer < 10) ? remainer + '0' : remainer + 'a' - 10;
    }while(unsignedSrc /= divisor);
    *p = 0;
    p1 = buffer;
    p2 = p - 1;
    while(p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

}
int atoi(char* str)
{
    int sign = 1, base = 0, i = 0;
    // if a string contains whitespace, ignore it
    while(str[i] == ' ')
        i++;
    // check the sign of number
    if(str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }
    // checking for valid input
    while(str[i] >= '0' && str[i] <= '9')
    {
        // handing overflow test case
        if((base > INT_MAX / 10) || (base == INT_MAX / 10 &&
            str[i] - '0' > 7))
        {
            if(sign == 1)
                return INT_MAX;
            else
            {
                return INT_MIN;
            }
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}
/*******************************************
 reverses a string
    example:
        before: Hello
        after: olleH
********************************************/
void reverse(char* s)
{
    int c, i, j; // declare  variables
    for(i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[i];
        s[j] = c;
    }
}
// K&R
int strlen(const char c[])
{
    int i = 0;
    while(c[i] != '\0')
    {
        ++i;
    }
    return i;
}

void append(char c[], char num)
{
    int len = strlen(c);
    c[len] = num;
    c[len+1] = '\0';
}

void back_space(char c[])
{
    int len = strlen(c); // get the string length
    c[len-1] = '\0';
}

// K&R

int strcmp(char c[], char c2[])
{
    int i;
    for(i = 0; c[i] == c2[i]; i++)
    {
        if(c[i] == '\0')
        {
            return 0;
        }
    }
    return c[i] - c2[i];
}
char *strcpy(char *dest, const char *src)
{
   do
   {
      *dest++ = *src++;
   } while (*src != 0);
   
    return dest;
}
void remove_from_string(char *s, char c)
{
    int writer = 0, reader = 0;

    while (s[reader])
    {
        if (s[reader]!=c) 
        {   
            s[writer++] = s[reader];
        }

        reader++;       
    }

    s[writer]=0;
}

char lower_case(char ch)
{
    if(ch >= 'A' && ch <= 'Z')
        ch = ch + 'a' - 'A';
    return ch;
}
char upper_case(char ch)
{
    // if ch is greather than a or if is 
    if(ch >= 'a' && ch <= 'z')
        ch = ch - 'a' + 'A';
    return ch;
}