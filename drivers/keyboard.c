#include "./include/keyboard.h"
#include "../common/include/port.h"
#include "../libc/include/string.h"
#include "../libc/include/unused.h"
#include "./include/screen.h"
#include "../kernel/kmain.h"
#include "../kernel/shell/include/shell.h"
#define SC_MAX 57 
static char buf[256];
#define ENTER 0x1C
#define BACKSPACE 0x0E
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
const char sc_ascii_small[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};
uint8_t shift = 0;
void send_command_to_kbc(uint8_t cmd);
void send_command_to_enc_kb(uint8_t cmd);
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
        shell(buf);
        buf[0] = '\0';
    }
    else if(scan_code == BACKSPACE)
    {
        back_space(buf);
        key_backspace();
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
void init_keyboard()
{
    
    reg_interrupt_handler(IRQ1, keyboard_callback);
}

