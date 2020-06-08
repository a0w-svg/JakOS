#ifndef CMOS_H
#define CMOS_H

#include <stdint.h>

// CMOS time struct
typedef struct 
{  
    uint8_t century;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    unsigned year;
}cmos_time_date_t;

typedef long cmos_time_sec_t;
cmos_time_date_t cmos_rtc_get_time();
void cmos_timoe_normal(cmos_time_date_t *time_time);
#endif