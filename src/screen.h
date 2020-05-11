#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"

/* write a single char out to the screen*/
void screen_put(char c);
/* Clear screen */
void screen_clean();
/* output a null-terminated string to the screen*/
void screen_write(char *c);

#endif