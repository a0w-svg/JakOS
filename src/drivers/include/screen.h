#ifndef SCREEN_H
#define SCREEN_H

#include "../../common/include/types.h"

#define VIDEO_ADDR 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
//color define
#define WHITE_ON_BLACK 0x0f
//screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
/* write a single char out to the screen*/
void _put(char c);
/* Clear screen */
void screen_clean();
/* output a null-terminated string to the screen*/

void printk(char* txt);
void printk_char(char character, int row, int column, char attrib_byte);
void printk_backspace();
int get_sc_offset(int row, int column);
int get_cur();
void set_cursor_position(uint32_t offset_x);
void screen_clean();
int handle_scroll(int cursor_offset_position, char attrib_byte);
#endif