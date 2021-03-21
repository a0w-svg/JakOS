#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../common/include/types.h"
#include "../../kernel/cpu/include/isr.h"
#include <stdbool.h>
#include <stddef.h>
//define constants
void init_keyboard();
char get_char();
char* get_string(size_t size);
#endif