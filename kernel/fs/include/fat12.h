#ifndef FAT12_H
#define FAT12_H

#include "../../../common/include/types.h"
#include "fs.h"
// directory entry
typedef struct 
{
    uint8_t filename[8];
    uint8_t exet[3];
    uint8_t attrib;
    uint8_t reserved;
    uint8_t time_created_ms;
    uint16_t time_created;
    uint16_t data_created;
    uint16_t data_last_accessed;
    uint16_t first_clus_hi_bytes;
    uint16_t last_modify_time;
    uint16_t last_modify_date;
    uint16_t first_cluster;
    uint32_t filesize;
}DIRECTORY, *Pointer_DIR;

// filesystem mount info
typedef struct 
{
    uint32_t num_sect;
    uint32_t fat_offset;
    uint32_t num_root_entries;
    uint32_t root_offset;
    uint32_t root_size;
    uint32_t fat_size;
    uint32_t fat_entry_size;
} Mount_info, *Mount_info_p;

File fatDirectory(const char* dir_name);
void fatRead(Pfile file, uint8_t* buffer, uint32_t len);
File FatOpen(const char* filename);
void fatInitialize();
void fatMount();
#endif