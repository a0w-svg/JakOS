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

//clean screen
void screen_clean();

void printk_at(char *txt, int column, int row);
void printk(char *txt);

//print numbers
void printk_hex(uint32_t n);
void printk_dec(uint32_t n);
void key_backspace();

#endif