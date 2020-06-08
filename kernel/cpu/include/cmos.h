#ifndef CMOS_H
#define CMOS_H

#include <stdint.h>
#include "../../../common/include/hal.h"
//define CMOS  addresses
#define CMOS_ADDRESS_REG 0x70
#define CMOS_DATA_REG 0x71

#define from_bcd(value) ((value / 16) * 10 + (value & 0xF))

#endif