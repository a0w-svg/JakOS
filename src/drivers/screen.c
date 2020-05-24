#include "./include/screen.h"
#include "../common/include/port.h"
#include "../libc/include/mem.h"


int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}
int get_offset_column(int offset)
{
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
void printk(char *txt)
{
    int i = 0;
    while(txt[i] != 0)
    {
        printk_char(txt[i++], -1, -1, WHITE_ON_BLACK);
    }
}

void printk_char(char character, int row, int column, char attrib_byte)
{
    uint8_t *vram = (uint8_t *) VIDEO_ADDR;

    if(!attrib_byte)
    {
        attrib_byte = WHITE_ON_BLACK;
    }
    int offset_mem;

    if(column >= 0 && row >= 0)
    {
        offset_mem = get_sc_offset(row, column);
    }
    else
    {
        offset_mem = get_cur();
    }
    
    if(character == '\n')
    {
        int rows_term = offset_mem / (2*MAX_COLS);
        offset_mem = get_sc_offset(rows_term, MAX_COLS-1);
    }
    else
    {
        vram[offset_mem] = character;
        vram[offset_mem+1] = attrib_byte;
    }

    offset_mem += 2;
    offset_mem = handle_scroll(offset_mem, attrib_byte);
    set_cursor_position(offset_mem);  
}

int get_sc_offset(int row, int column)
{
    return (row * 80 + column) * 2;
}

int get_cur()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset_mem = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset_mem += port_byte_in(REG_SCREEN_DATA);
    return offset_mem * 2;
}

void set_cursor_position(uint32_t offset_x)
{
    offset_x /= 2;

    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (offset_x >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, offset_x);
}

void printk_backspace()
{
    int offset_cur = get_cur()-2;
    int row = get_offset_row(offset_cur);
    int column = get_offset_column(offset_cur);
    printk_char(0x08, row, column, WHITE_ON_BLACK);
}
void screen_clean()
{
    int row = 0;
    int column = 0;

    for(row = 0; row < MAX_ROWS; row++)
    {
        for(column = 0; column < MAX_COLS; column++)
        {
            printk_char(' ', row, column, WHITE_ON_BLACK);
        }
    }
    set_cursor_position(get_sc_offset(0,0));
}


int handle_scroll(int cursor_offset_pos, char attrib_byte)
{
    char *dst_Row, *source_row;
    int i;

    if(cursor_offset_pos < MAX_ROWS * MAX_COLS * 2)
    {
        return cursor_offset_pos;
    }

    for(i = 1; i < MAX_ROWS; i++)
    {
        source_row = (char*) get_sc_offset(i, 0) + VIDEO_ADDR;
        dst_Row = (char*) get_sc_offset(i-1, 0) + VIDEO_ADDR;
        mem_cp(dst_Row, source_row, MAX_COLS * 2);
    }

    char* last_Row = (char*) get_sc_offset(MAX_ROWS-1, 0) + VIDEO_ADDR;
    for(i = 0; i < MAX_COLS; i++)
    {
        last_Row[2*i] = ' ';
        last_Row[2*i-1] = attrib_byte;
    }
    cursor_offset_pos -= 2 * MAX_COLS;
    return cursor_offset_pos;
}