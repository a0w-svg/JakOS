#include "./include/keyboard.h"
#include "../common/include/port.h"
#include "../libc/include/string.h"
#include "../libc/include/unused.h"
#include "./include/screen.h"
#include "../kernel/kmain.h"
#define SC_MAX 57 
static char buf[256];
#define ENTER 0x1C
#define BACKSPACE 0x0E
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};
static void keyboard_callback(registers_t *regs)
{
    uint8_t scan_code = port_byte_in(0x60);

    if(scan_code > SC_MAX)
    {
        return;
    }
    else if(scan_code == ENTER)
    {
        printk("\n");
        input(buf);
        buf[0] = '\n';
    }
    else if(scan_code == BACKSPACE)
    {
        back_space(buf);
        printk_backspace();
    }
    else
    {
        char letter_key = sc_ascii[(int)scan_code];
        char str[2] = {letter_key, '\0'};
        append(buf, letter_key);
        printk(str);
    }
    UNUSED(regs);
}


void init_keyboard()
{
    reg_interrupt_handler(IRQ1, keyboard_callback);
}