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

typedef enum {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
}VGA_color;
//clean screen
void screen_clean();

void printk_at(char *txt, int column, int row, uint8_t attirb);
void printk(char *txt);
void printk_color(char *txt, VGA_color fg, VGA_color bg);
//print numbers
void printk_hex(uint32_t n);
void printk_dec(uint32_t n);
void key_backspace();

#endif