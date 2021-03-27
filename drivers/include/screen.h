#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

/**********************************************
* use this if you want clean a screen
***********************************************/
void screen_clean();
/***********************************************************
* displays the string on the screen in the default color
**********************************************************/
#define printk(txt) printk_c(txt, 0)
/***********************************************************
* displays the string on the screen in the specified color
************************************************************/
void printk_c(const char *Txt, uint8_t Color);
/************************************************************
* displays the character with specified color
************************************************************/
int printk_putchar(char data, uint8_t Color);
/*************************************************************
* removes a character from the screen
**************************************************************/
void key_backspace();

#endif