#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../common/include/types.h"
#include "../../kernel/cpu/include/isr.h"
#include <stdbool.h>
#include <stddef.h>
//define constants
void init_keyboard();
char get_char();
void get_string(char* buf, size_t size);
#endif