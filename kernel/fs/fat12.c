#include "./include/fat12.h"
#include "../../libc/include/string.h"
#include "../../drivers/disks/include/fdd.h"
#include "../../libc/include/mem.h"

#define SECT_SIZE 512

FS FatFS;
Mount_info mount_info;

uint8_t FAT[SECT_SIZE * 2];

void convert_to_dos_filename(const char* filename, char* fname, uint32_t filename_len)
{
    uint32_t i = 0;
    if(filename_len > 11) return;
    if(!fname || !filename) return;
    mem_set(fname, ' ', filename_len);
    for(i = 0; i < strlen(filename)-1 && i < filename_len); i++)
    {
        if(filename[i] == '.' || i == 8)
            break;

        fname[i] =  upper_case(filename[i]);
    }
    if(filename[i] == '.')
    {
        for(int l = 0; l < 3; l++)
        {
            ++i;
            if(filename[i])
            {
                fname[8 + k] = filename[i];
            }
        }
    }
    for(i = 0; i < 3; i++)
    {
        fname[8+i] = upper_case(fname[8 + i]);
    }
}

File fatDirectory(const char* dir_name)
{
    File file;
    uint8_t* buf;
    char dos_filename[11];
    convert_to_dos_filename(dir_name, dos_filename, 11);
    dos_filename[11] = 0;
    for(int sector = 0; sector < 14; sector++)
    {
        buf = (uint8_t*) 
    }
}
void fatRead(Pfile file, uint8_t* buffer, uint32_t len);
File FatOpen(const char* filename);
void fatInitialize();
void fatMount();