#ifndef ATA_H
#define ATA_H
#include <stdint.h>
#include "../../../common/include/port.h"
/*************************************************************
    Read Sectors from IDE disk.                              
    uint32_t* target_addr - Destination address              
    uint32_t LBA - Logical Block Addressing 1..itd           
    uint8_t sec_count - number of sectors you want to read   
**************************************************************/
void read_sectors_ata_pio(uint32_t* target_addr, uint32_t LBA, uint8_t sec_count);
/*************************************************************
    Write Sectors to IDE disk                                
    uint32_t LBA - number of logical block                   
    uint8_t sec_count - number of sectors
    uint32* bytes - data to write on IDE disk
**************************************************************/
void write_sectors_ata_pio(uint32_t LBA, uint8_t sec_count, uint32_t* bytes);
#endif