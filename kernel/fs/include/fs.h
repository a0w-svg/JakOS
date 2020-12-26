#ifndef FS_H
#define FS_H
#include "../../../common/include/types.h"

typedef struct 
{
    char file_name[32];
    uint32_t flags;
    uint32_t file_len;
    uint32_t id;
    uint32_t eof;
    uint32_t position;
    uint32_t current_clus;
    uint32_t devID;
}File, *Pfile;

typedef struct 
{
    char name[8];
    File (*directory) (const char* dir_name);
    void (*mount) ();
    void (*read) (Pfile file, uint8_t* buffer, uint32_t len);
    void (*close) (Pfile);
    File (*open) (const char* filename);
}FS, *PFS;

#define FS_FILE 0
#define FS_DIRECTORY 1
#define FS_INVALID 2

File vfs_open_file(Pfile file, const char* filename);
void vfs_read_file(Pfile file, uint8_t* buff, uint32_t len);
void vfs_close_file(Pfile file);
void vfs_register_filesystem(PFS, uint32_t deviceID);
void vfs_unregister_filesystem(PFS);
void vfs_unregister_filesystem_ID(uint32_t deviceID);
#endif