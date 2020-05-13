#include "./include/string.h"

// K&R implementation

void int_to_ascii(int num, char str[])
{
  int i, sign;
  if((sign = num) < 0) 
  {
      num = -num;
  }
    i = 0;
      do{
          str[i++] = num %  10 + '0';
      } while ((num /= 10) > 0);
      if(sign < 0)
      {
          str[i++] = '-';
          str[i] = '\0';
      }
    reverse(str);
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
int strlen(char c[])
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