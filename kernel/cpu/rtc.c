#include <stdbool.h>
#include "./include/rtc.h"
#include "./include/isr.h"
#include "../../libc/include/mem.h"
#include "../../common/include/port.h"
#include "../../common/include/types.h"
#include "../../libc/include/stdio.h"
#include "../mm/include/kmalloc.h"
#include "../../common/include/hal.h"
#define CURRENT_YEAR 2000
#define CMOS_ADDRESS_REG 0x70
#define CMOS_DATA_REG 0x71
#define from_bcd(value) (((value >> 4) * 10) + (value & 0xF))

bool bcd;
time_t *global_time;
int century_reg = 0x00;

volatile bool interrupt = false;

void get_time(time_t* time)
{
    memcpy_w(time,  global_time, sizeof(time_t));
}

uint8_t reg_in(uint8_t reg)
{
    port_byte_out(CMOS_ADDRESS_REG, reg);
    return port_byte_in(CMOS_DATA_REG);
}

void reg_out(uint8_t reg, uint8_t value)
{
    port_byte_out(CMOS_ADDRESS_REG, reg);
    port_byte_out(CMOS_DATA_REG, value);
}
int get_update_in_progress_flag()
{
    port_byte_out(CMOS_ADDRESS_REG, 0x0A);
    return (port_byte_in(CMOS_DATA_REG) & 0x80);
}
void rtc_handler(registers_t* r)
{
   uint8_t century;
   uint8_t last_second;
   uint8_t last_minute;
   uint8_t last_hour;
   uint8_t last_day;
   uint8_t last_month;
   uint8_t last_year;
   uint8_t last_century;
   uint8_t reg_b;
   while(get_update_in_progress_flag());
   global_time->second = reg_in(0x00);
   global_time->minute = reg_in(0x02);
   global_time->hour   = reg_in(0x04);
   global_time->day    = reg_in(0x07);
   global_time->month  = reg_in(0x08);
   global_time->year   = reg_in(0x09);
   if(century_reg != 0)
        century = reg_in(century_reg);
    do{
        last_second = global_time->second;
        last_minute = global_time->minute;
        last_hour = global_time->hour;
        last_day = global_time->day;
        last_month = global_time->month;
        last_year = global_time->year;
        last_century = century;
        while(get_update_in_progress_flag());
        global_time->second = reg_in(0x00);
        global_time->minute = reg_in(0x02);
        global_time->hour = reg_in(0x04);
        global_time->day = reg_in(0x07);
        global_time->month = reg_in(0x08);
        global_time->year = reg_in(0x09);
        if(century_reg != 0)
            century = reg_in(century_reg);
    }while((last_second != global_time->second) || 
    (last_minute != global_time->minute) ||
    (last_hour != global_time->hour) ||
    (last_day != global_time->day) ||
    (last_month != global_time->month) ||
    (last_year != global_time->year) ||
    (last_century != century));
    reg_b = reg_in(0x0B);

    if(!(reg_b & 0x4))
    {
        global_time->second = (global_time->second & 0x0F) + ((global_time->second / 16) * 10);
        global_time->minute = (global_time->minute & 0x0F) + ((global_time->minute / 16) * 10);
        global_time->hour   = ((global_time->hour & 0x0F) + (((global_time->hour & 0x70) / 16) * 10)) |
         (global_time->hour & 0x80);
        global_time->day = (global_time->day & 0x0F) + ((global_time->day / 16) * 10);
        global_time->month = (global_time->month & 0x0F) + ((global_time->month / 16) * 10);
        global_time->year = (global_time->year & 0x0F) * ((global_time->year / 16) * 10);
        if(century_reg != 0)
            century = (century & 0x0F) + ((century / 16) * 10);
    }

    if(!(reg_b & 0x2) && (global_time->hour & 0x80))
        global_time->hour = ((global_time->hour & 0x7F) + 12) % 24;
    if(century_reg != 0)
        global_time->year += century * 100;
    else
    {
        global_time->year += (CURRENT_YEAR / 100) * 100;
        if(global_time->year < CURRENT_YEAR) global_time->year += 100;
    }
    UNUSED(r);
    port_byte_out(0x70, 0x0C);
    port_byte_in(0x71);
}
void init_rtc()
{
    reg_interrupt_handler(IRQ8, rtc_handler);
    disable_interrupts();
    port_byte_out(0x70, 0x8B);
    char prev = port_byte_in(0x71);
    port_byte_out(0x70, 0x8B);
    port_byte_out(0x71, prev | 0x40);
    enable_interrupts();
}