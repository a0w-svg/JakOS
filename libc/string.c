#include "./include/string.h"
#include <stdint.h>
// K&R implementation

void int_to_ascii(char* buffer, int base, int d)
{
    char* p = buffer;
    char* p1, *p2;
    unsigned long unsignedSrc = d;
    int divisor = 10;
    if(base == 'd' && d < 0)
    {
        *p++ = '-';
        buffer++;
        unsignedSrc = -d;
    }
    else if(base == 'x')
        divisor = 16;
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

void hex_to_ascii(int num, char str[])
{
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t temp;
    int i;
    for(i = 28; i > 0; i-= 4)
    {
        temp = (num >> i) & 0xF;
        if(temp == 0 && zeros == 0)
        {
            continue;
        }
        zeros = 1;
        if(temp > 0xA)
        {
            append(str, temp - 0xA + 'a');
        }
        else
        {
            append(str, temp + '0');
        }
    }
    temp = num & 0xF;
    if(temp >= 0xA)
    {
        append(str, temp - 0xA + 'a');
    }
    else
    {
        append(str, temp + '0');
    }
}
// K&R
void reverse(char s[])
{
    int c, i, j;
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
    int len = strlen(c);
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
    if(ch >= 'a' && ch <= 'z')
        ch = ch - 'a' + 'A';
    return ch;
}