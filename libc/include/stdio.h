#ifndef STDIO_H
#define STDIO_H
#define EOF (-1)
/*********************************************************************************
 *  Print function
 *  flags:
 *  %d - displaying the decimal number from the argument of the int type
 *  %z - changing the color of the displayed font from the argument of int type
 *  %s - displaying the string from the argument of the  const char* type
 *  if there are no arguments, the function displays the string by default
 *********************************************************************************/
int printf(const char* __restrict, ...);
/*************************************************
* Function places a char with a color attribute
* char ch - character to print
* unsigned char Color - print color
**************************************************/
int putchar(char ch, unsigned char Color);
/*****************************************************
* Function places a string on the screen
* const char* string - the string you want to display
******************************************************/
int puts(const char* string);
/*************************************************
* clean terminal
*************************************************/
void clean();
/*************************************************
*   get the string from keyboard.
*   char *buf - character array where you want to
*   save the retrieved data
*   unsigned long size - number of characters to read
*************************************************/
void gets(char* buf, unsigned long size);
/*************************************************
 * get character from keyboard
**************************************************/
char getch();
#endif