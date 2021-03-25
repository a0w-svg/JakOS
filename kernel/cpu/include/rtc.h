#ifndef RTC_H
#define RTC_H

#include <stdint.h>

typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint32_t year;
}time_t;

void get_time(time_t* time);
void init_rtc();

#endif