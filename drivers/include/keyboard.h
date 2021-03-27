#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stddef.h>
/*****************************************
 * Initialize keyboard interrupt
******************************************/
void init_keyboard();
/******************************************
 * Get character from keyboard
*******************************************/
char get_char();
/******************************************
* Get string from keyboard
* char *buf - character array where you want to
* save the retrieved data
* size_t size - number of characters to read
******************************************/
void get_string(char* buf, size_t size);
#endif