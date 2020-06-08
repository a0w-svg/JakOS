#include "./include/cmos.h"
#include ".././cpu/include/idt.h"
#include "../../common/include/port.h"

static int centry_reg = 0x00;

int check_update_cmos()
{
    port_byte_out(0x70, 0x0A);
    return (port_byte_in(0x71) & 0x80);
}

uint8_t get_reg(int reg)
{
    port_byte_out(0x70, reg);
    return (port_byte_in(0x71));
}

cmos_time_date_t cmos_rtc_get_time()
{
    while (check_update_cmos());
    cmos_time_date_t last;
    cmos_time_date_t current;

    current.second = get_reg(0x00);
    current.minute = get_reg(0x02);
    current.hour = get_reg(0x04);
    current.day = get_reg(0x07);
    current.month = get_reg(0x08);
    current.year = get_reg(0x09);

    if(centry_reg != 0x00)
    {
        current.century = get_reg(centry_reg);
    }

    do
    {
        last = current;
        if(centry_reg != 0x00)
        {
            current.century = get_reg(centry_reg);
        }
        
    } while ((last.second != current.second) || (last.minute != current.minute) ||
                (last.hour != current.hour) || (last.day != current.day) || 
                (last.month != current.month) || (last.year != current.year) ||
                (last.century != current.century));

    uint8_t regb = get_reg(0x0B);
    if((regb & 0x04) == 0)
    {
        current.second = (current.second &0x0F) + ((current.second / 16) * 10);
        current.minute = (current.minute & 0x0F) + ((current.minute / 16) * 10);
        current.hour = ((current.hour & 0x0F) + (((current.hour & 0x70) / 16) * 10)) | (current.hour & 0x80);
        current.day = (current.day & 0x0F) + ((current.day / 16) * 10);
        current.month = (current.month & 0x0F) + ((current.month / 16) * 10);
        current.year = (current.year & 0x0F) + ((current.century / 16) * 10);
        if(centry_reg != 0x00)
        {
            current.century = (current.century & 0x0F) + ((current.century / 16) * 10);
        }
    }
    if(!(regb & 0x02) && (current.hour & 0x80))
    {
        current.hour = ((current.hour & 0x7F) + 12) % 24;
    }
    return current;
}