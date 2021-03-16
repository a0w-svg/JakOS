#ifndef STDIO_H
#define STDIO_H
#define EOF (-1)
/***************************************
 *  Print function
 *  flags:
 *  %d - displaying the decimal number from the argument of the int type
 *  %z - changing the color of the displayed font from the argument of int type
 *  %s - displaying the string from the argument of the  const char* type
 *  if there are no arguments, the function displays the string by default
 ***************************************/
int printf(const char* __restrict, ...);
// Function places a char with a color attribute
int putchar(char, unsigned char Color);
// Function places a string on the screen
int puts(const char*);
#endif