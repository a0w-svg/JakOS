#include "./include/keyboard.h"
#include "../common/include/port.h"
#include "../libc/include/string.h"
#include "../common/include/types.h"
#include "./include/screen.h"
#include "../kernel/kmain.h"
#include "../kernel/shell/include/shell.h"
#include <stddef.h>
#define SC_MAX 57 
static char temp[256];
size_t i = 0;
static int write = -1;
#define ENTER 0x1C
#define BACKSPACE 0x0E
#define SHIFT_PRESS 0x2A
#define SHIFT_RELEASE 0xAA
// KBC constans
enum KB_ENCODER_IO {
    KB_ENC_INPUT_BUFFER = 0x60,
    KB_ENC_CMD_REG = 0x60
};
enum KBC_IO{
    KBC_STATS_REG = 0x64,
    KBC_CMD_REG = 0x64
};
enum KBC_STATS_MASK{
    KBC_STATS_MASK_OUT_BUFFER = 1,
    KBC_STATS_MASK_IN_BUFFER = 2,
    KBC_STATS_MASK_SYSTEM = 4,
    KBC_STATS_MASK_CMD_DATA = 8,
    KBC_STATS_MASK_LOCKED = 0x10,
    KBC_STATS_MASK_AUX_BUFFER = 0x20,
    KBC_STATS_MASK_TIMEOUT = 0x40,
    KBC_STATS_MASK_PARITY = 0x80
};
enum KB_ENC_CMD{
    SET_LEDS = 0xED,
    ECHO_CMD = 0xEE,
    SET_ALT_SCANCODE_SET = 0xF0,
    SEND_2_BYTE_KB_ID = 0xF2,
    SET_AUTOREPEAT_DELAY_AND_REPEAT_RATE = 0xF3,
    ENABLE_KB = 0xF4,
    RESET_POWER_ON_CONDITION_WAIT_TO_ENABLE_CMD = 0xF5,
    RESET_POWER_ON_CONDITION_AND_BEGIN_SCANNING_KB = 0xF6,
    SET_ALL_KEYS_TO_AUTOREPEAT_PS2_ONLY  = 0xF7,
    SET_ALL_KEYS_TO_SEND_MAKE_CODE_AND_BREAK_CODE_PS2_ONLY = 0xF8,
    SET_ALL_KEYS_TO_GEN_ONLY_MAKE_CODES = 0xF9,
    SET_ALL_KEYS_TO_AUTOREPAT_AND_GEN_MAKE_BREAK_CODES = 0xFA,
    SET_A_SINGLE_KEY_TO_AUTOREPEAT = 0xFB,
    SET_A_SINGLE_KEY_TO_GEN_MAKE_AND_BREAK_CODES = 0xFC,
    SET_A_SINGLE_KEY_TO_GEN_ONLY_BREAK_CODES = 0xFD,
    RESEND_LAST_RESULT = 0xFE,
    RESET_KB_TO_POWER_ON_STATE_AND_START_SELF_TEST = 0xFF
};
enum KBC_CMD{ // Onboard Keyboard Controller Commands
    // Common Commands
    READ_CMD_BYTE = 0x20, // Read command byte
    WRITE_CMD_BYTE = 0x60, // Write command byte
    SELF_TEST = 0xAA, // self test
    INTERFACE_TEST = 0xAB, // interface test
    DISABLE_KB = 0xAD, // disable keyboard
    ENABLE_KBC_KB = 0xAE, // enable keyboard 
    READ_INPUT_PORT = 0xC0, // read  input port
    READ_OUTPUT_PORT = 0xD0,
    WRITE_OUTPUT_PORT = 0xD1,
    READ_TEST_INPUTS = 0xE0,
    SYSTEM_RESET = 0xFE,
    DISABLE_MOUSE_PORT = 0xA7,
    ENABLE_MOUSE_PORT = 0xA8,
    TEST_MOUSE_PORT = 0xA9,
    WRITE_TO_MOUSE = 0xD4,
    /* 
    Non Standard Commands:
            |
    0x00-0x1F "Read controller RAM"
    0x20-0x3F "Read controller RAM"
    0x40-0x5F "Write controller RAM"
    0x60-0x7F "Write controller RAM"
    0x90-0x93 "Synaptics Multiplexer Prefix"
    0x90-0x9F "Write port  13-Port 10"
    */
    READ_COPYRIGHT = 0xA0,
    READ_FIRMWARE_VER = 0xA1,
    CHANGE_SPEED = 0xA2,
    CHANGE_SPEED2 = 0xA3,
    CHECK_IF_PASSWORD_IS_INSTALLED = 0xA4,
    LOAD_PASSWORD = 0xA5,
    CHECK_PASSWORD = 0xA6,
    DISAGNOSTIC_DUMP = 0xAC,
    READ_KB_VERSION = 0xAF,
    // 0xB0-0xB5 "Reset controller line"
    // 0xB8-0xBD "Set controller line"
    CONTINUOUS_IN_PORT_POLL_LOW = 0xC1,
    CONTINUOUS_IN_PORT_POLL_HIGH = 0xC2,
    UNBLOCK_CONTROLLER_LINES_P22_AND_P23 = 0xC8,
    BLOCK_CONTROLLER_LINES_P22_AND_P23 = 0xC9,
    READ_CONTROLLER_MODE = 0xCA,
    WRITE_CONTROLLER_MODE = 0xCB,
    WRITE_OUTPUT_BUFFER = 0xD2,
    WRITE_MOUSE_OUTPUT_BUFFER = 0xD3,
    DISABLE_A20_LINE = 0xDD,
    ENABLE_A20_LINE = 0xDF,
    // 0xF0-0xFF "Pulse output bit"
};

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { 0, 0, '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', 0, 0, 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', 0, 0, 0, ' '};
const char sc_ascii_small[] = { 0, 0, '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', 0, 0, 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0};
// proto functions
void send_command_to_kbc(uint8_t cmd);
void send_command_to_enc_kb(uint8_t cmd);
bool kb_self_test();
void kb_disable();
void kb_enable();
int kbd_irq = 0;
char last_key = 0;
static void keyboard_callback(registers_t *regs)
{
    uint8_t scan_code = port_byte_in(0x60);
    static int shift = 0;
    if(scan_code > SC_MAX)
    {
        return;
    }
    if(scan_code == ENTER)
    {
        printk("\n");
        last_key = '\n';
        kbd_irq = 1;
    }
    else if(scan_code == BACKSPACE)
    {
        if(write >= 0)
        {
            back_space(temp);
            i--;
            key_backspace();
            write--;
        }
    }
    else
    {
        if(sc_ascii[(int)scan_code] != 0)
        {
            char letter_key = sc_ascii[(int)scan_code];
            last_key = letter_key;
            kbd_irq = 1;
        }
    }
    UNUSED(regs);
}

void set_control_led(bool numlock, bool capslock, bool scroll)
{
    uint8_t data = 0;
    data = (scroll) ? (data | 1) : (data & 1);
    data = (numlock) ? (numlock | 2) : (numlock & 2);
    data = (capslock) ? (capslock | 4) : (capslock & 4);

    send_command_to_enc_kb(SET_LEDS);
    send_command_to_enc_kb(data);
}

uint8_t keyboard_read_status()
{
    return port_byte_in(KBC_STATS_REG);
}
void send_command_to_kbc(uint8_t cmd)
{
    while(1)
    {
        if ((keyboard_read_status() & KBC_STATS_MASK_IN_BUFFER) == 0)
            break;
    }
    port_byte_out(KBC_CMD_REG, cmd);
}
uint8_t kb_enc_read_buf()
{
    return port_byte_in(KB_ENC_INPUT_BUFFER);
}
void send_command_to_enc_kb(uint8_t cmd)
{
    while (1)
    {
        if((keyboard_read_status() & KBC_STATS_MASK_IN_BUFFER) == 0)
            break;
    }
    port_byte_out(KB_ENC_CMD_REG, cmd);
}
bool kb_self_test()
{
    send_command_to_kbc(SELF_TEST);
    while (1)
    {
        if((keyboard_read_status() & KBC_STATS_MASK_OUT_BUFFER))
            break;
    }
    return (kb_enc_read_buf() == 0x55) ? true : false;
}
void kb_disable()
{
    send_command_to_kbc(DISABLE_KB);
}
void kb_enable()
{
    send_command_to_kbc(ENABLE_KBC_KB);
}
void kbc_reset_system()
{
    send_command_to_kbc(WRITE_OUTPUT_PORT);
    send_command_to_enc_kb(0xfe);
}
void set_type_scancode(uint8_t code_set)
{
    send_command_to_enc_kb(SET_ALT_SCANCODE_SET);
    send_command_to_enc_kb(code_set);
}

void init_keyboard()
{
   reg_interrupt_handler(IRQ1, keyboard_callback);
}

char get_char()
{
    while(kbd_irq != 1);
    kbd_irq = 0;
    return last_key;
}

char* get_string(size_t size)
{
    temp[0] = '\0';
    write = -1;
    for(i = 0; i < size - 1; i++)
    {
        append(temp, get_char());
        if(temp[i] == '\n')
        {
            temp[i] = '\0';
            return temp;
        }

        else
        {
            write++;
            char a[2] = {temp[i], '\0'};
            printk(a);
        }
    }
    temp[size] = '\0';
    return temp;
}