#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../common/include/types.h"
#include "../../kernel/cpu/include/isr.h"
#include <stdbool.h>
//define constans
void init_keyboard();
void set_control_led(bool numlock, bool capslock, bool scroll);
void set_type_scancode(uint8_t code_set);
void kbc_reset_system();
#endif