#include "./include/screen.h"
#include "../common/include/port.h"
#include "../libc/include/mem.h"
#include "../libc/include/string.h"
#include "./include/speaker.h"
//private API
int get_cur_offset();
void set_cur_offset(int offset);
int printk_char(char ch, int column, int row, char attrib);
int get_offset_mem(int column, int row);
int get_offset_row(int offset);
int get_offset_column(int offset);
uint8_t entry_color(VGA_color fg, VGA_color bg);

//public API

void printk_at(const char *txt, int column, int row, uint8_t attirb)
{
    int offset;
    if(column >= 0 && row >= 0)
    {
        offset = get_offset_mem(column, row);
    }
    else
    {
        offset = get_cur_offset();
        row = get_offset_row(offset);
        column = get_offset_column(offset);
    }
    int i = 0;
    while(txt[i] != 0)
    {
        offset = printk_char(txt[i++], column, row, attirb);
        row = get_offset_row(offset);
        column = get_offset_column(offset);
    }
}
void printk(const char *txt)
{
    printk_at(txt, -1, -1, WHITE_ON_BLACK);
}
void printk_color(char *txt, VGA_color fg, VGA_color bg)
{
    uint8_t color = entry_color(fg, bg);
    if(color == 0)
        printk_at(txt, -1, -1, WHITE_ON_BLACK);
    else
    {
        printk_at(txt, -1, -1,  color);
    }
}

void key_backspace()
{
    int offset = get_cur_offset()-2;
    int row = get_offset_row(offset);
    int column = get_offset_column(offset);
    printk_char(0x08, column, row, WHITE_ON_BLACK);
}

// private functions

int printk_char(char ch, int column, int row, char attrib)
{
    uint8_t *vram = (uint8_t*)VIDEO_ADDR;
    if(!attrib)
    {
        attrib = WHITE_ON_BLACK;
    }

    if(column >= MAX_COLS || row >= MAX_ROWS)
    {
        vram[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vram[2*(MAX_COLS)*(MAX_ROWS)-1] = WHITE_ON_BLACK;
        return get_offset_mem(column, row);
    }

    int offset;
    if(column >= 0 && row >= 0)
    {
        offset = get_offset_mem(column, row);
    }
    else
    {
        offset = get_cur_offset();
    }
    if(ch == '\t')
    {
        row = get_offset_row(offset);
        column = get_offset_column(offset);
        offset = get_offset_mem(column+4, row);
        ch = 0;
    }
    if(ch == '\a')
    {
        beep();
        ch = 0;
    }

    if(ch == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset_mem(0, row+1);
    }
    else if(ch == 0x08)
    {
        vram[offset] = ' ';
        vram[offset+1] = attrib;
    }
    else
    {
        vram[offset] = ch;
        vram[offset+1] = attrib;
        offset += 2;
    }
    
    if(offset >= MAX_ROWS * MAX_COLS * 2)
    {
        int i;
        for(i = 1; i < MAX_ROWS; i++)
        {
            memcpy((uint8_t*)(get_offset_mem(0, i) + VIDEO_ADDR),(uint8_t*)(get_offset_mem(0, i-1) + VIDEO_ADDR),
                        MAX_COLS * 2);
        }
        char *last_line = (char*) (get_offset_mem(0, MAX_ROWS-1) + (uint8_t*) VIDEO_ADDR);
        for(i = 0; i < MAX_COLS * 2; i++)
        {
            last_line[i] = 0;
        }
        offset -= 2 * MAX_COLS;
    }
    set_cur_offset(offset);
    return offset;
}
void printk_hex(uint32_t n)
{
    int32_t tmp;

    printk("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            printk_char(tmp-0xA+'a', -1, -1,WHITE_ON_BLACK );
        }
        else
        {
            noZeroes = 0;
            printk_char( tmp+'0', -1, -1, WHITE_ON_BLACK );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        printk_char(tmp-0xA+'a', -1, -1, WHITE_ON_BLACK);
    }
    else
    {
        printk_char(tmp+'0', -1, -1, WHITE_ON_BLACK);
    }

}
void printk_putchar(char data)
{
        printk_char(data, -1, -1, WHITE_ON_BLACK);
}

void printk_dec(uint32_t n)
{

    if (n == 0)
    {
        printk_char('0', -1, -1, WHITE_ON_BLACK);
        return;
    }

    int32_t acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    printk(c2);

}

int get_cur_offset()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}
void set_cur_offset(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA,(uint8_t)(offset & 0xff));
}
void screen_clean()
{
    int term_size = MAX_COLS * MAX_ROWS;
    int i;
    uint8_t *term = (uint8_t*) VIDEO_ADDR;

    for(i = 0; i < term_size; i++)
    {
        term[i*2] = ' ';
        term[i*2+1] = WHITE_ON_BLACK;
    }
    set_cur_offset(get_offset_mem(0,0));
}
int get_offset_mem(int column, int row)
{
    return 2 * (row * MAX_COLS + column);
}
int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}
int get_offset_column(int offset)
{
    return (offset - (get_offset_row(offset)*2*MAX_COLS)) / 2;
}

uint8_t entry_color(VGA_color fg, VGA_color bg)
{
    return fg | bg << 4;
}