#ifndef SCREEN_H
#define SCREEN_H

#include "../../common/include/types.h"

/* write a single char out to the screen*/
void screen_put(char c);
/* Clear screen */
void screen_clean();
/* output a null-terminated string to the screen*/
void screen_write(char *c);
void screen_write_dec(uint32 n);
void screen_write_hex(uint32 n);
#endif