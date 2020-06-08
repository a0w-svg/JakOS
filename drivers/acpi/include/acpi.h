#ifndef ACPI_H
#define ACPI_H

#include <stddef.h>
#include <stdint.h>
#include "../../../drivers/include/screen.h"
#include "../../../common/include/port.h"
#include "../../../kernel/cpu/include/pit.h"
#include "../../../libc/include/string.h"
#include "../../../libc/include/mem.h"

typedef struct 
{
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t *RsdtAddress;
}__attribute__((packed)) RSDPDescritor_t;

#endif