#ifndef VFS_H
#define VFS_H
#include <stdint.h>
#include <stddef.h>

#define VFS_FILE         0x01
#define VFS_DIR          0x02
#define VFS_CHAR_DEVICE  0x03
#define VFS_BLOCK_DEVICE 0x04
#define VFS_PIPE         0x05
#define VFS_SYMLINK      0x06
#define VFS_MOUNTPOINT   0x07

struct Vfs_node;
typedef uint32_t (*read_type_t)(struct Vfs_node*, uint32_t, uint32_t, uint8_t*);
typedef uint32_t (*write_type_t)(struct Vfs_node*, uint32_t, uint32_t, uint8_t*);
typedef void (*open_type_t)(struct Vfs_node*);
typedef void (*close_type_t)(struct Vfs_node*);
typedef struct dirent* (*readdir_type_t)(struct Vfs_node*, uint32_t);
typedef struct Vfs_node* (*finddir_type_t)(struct Vfs_node*, char* name);

typedef struct Vfs_node
{
    char filename[128];  // the filename
    uint32_t mask;   // the permissions mask.
    uint32_t uid;    // the owning user.
    uint32_t gid;    // the owning group.
    uint32_t flags;  // includes the node type. see defines 
    uint32_t inode;  // this is device-specific - provides a way for a filesystem to identify files
    uint32_t length; // size of the file, in bytes
    uint32_t implementation; // An implementation-defined number
    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;
    struct Vfs_node *ptr;
}Vfs_node_t;

struct dirent
{
    char filename[128];
    uint32_t inod;
};

extern Vfs_node_t *vfs_root; // the root of the filesystem

uint32_t vfs_read(Vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer);
uint32_t vfs_write(Vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer);
void vfs_open(Vfs_node_t* node, uint8_t read, uint8_t write);
void vfs_close(Vfs_node_t* node);
struct dirent* vfs_readdir(Vfs_node_t* node, uint32_t index);
Vfs_node_t* vfs_finddir(Vfs_node_t* node, char* name);
#endif