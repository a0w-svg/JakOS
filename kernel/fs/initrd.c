#include "./include/initrd.h"
#include "../../libc/include/mem.h"
#include "../../libc/include/string.h"
#include "../mm/include/kmalloc.h"
initrd_header_t* initrd_header; // the initrd header
initrd_file_header_t* file_headers; // the list of file headers
Vfs_node_t* initrd_root;            // our root directory node
Vfs_node_t* initrd_dev;             // I also add a directory node for /dev, so i can mount devfs later on.
Vfs_node_t* root_nodes;             // list of file nodes
int number_root_nodes;              // number of file nodes

struct dirent Dirent;

static uint32_t initrd_read(Vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer)
{
    initrd_file_header_t header = file_headers[node->inode];
    if(offset > header.length)
        return 0;
    if(offset + size > header.length)
        size = header.length - offset;
    memcpy(buffer, (uint8_t*)(header.offset + offset), size);
    return size;
}

static struct dirent* initrd_readdir(Vfs_node_t* node, uint32_t index)
{
    if(node == initrd_root && index == 0)
    {
        strcpy(Dirent.filename, "dev");
        Dirent.filename[3] = 0;
        Dirent.inod = 0;
        return &Dirent;
    }
    if(index - 1 >= number_root_nodes)
        return 0;
    strcpy(Dirent.filename, root_nodes[index - 1].filename);
    Dirent.filename [strlen(root_nodes[index - 1].filename)] = 0;
    Dirent.inod = root_nodes[index - 1].inode;
    return &Dirent;
}

static Vfs_node_t* initrd_finddir(Vfs_node_t* node, char *name)
{
    if(node == initrd_root && !strcmp(name, "dev"))
        return initrd_dev;
    int i;
    for(i = 0; i < number_root_nodes; i++)
        if(!strcmp(name, root_nodes[i].filename))
            return &root_nodes[i];
    return 0 ;
}


Vfs_node_t* init_initrd(uint32_t location)
{
    initrd_header = (initrd_header_t*)location;
    file_headers = (initrd_file_header_t*)(location + sizeof(initrd_header_t));
    // initialise the root directory
    initrd_root = (Vfs_node_t*)kmalloc(sizeof(Vfs_node_t));
    strcpy(initrd_root->filename, "initrd");
    initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
    initrd_root->flags = VFS_DIR;
    initrd_root->read = 0;
    initrd_root->write = 0;
    initrd_root->open = 0;
    initrd_root->close = 0;
    initrd_root->readdir = &initrd_readdir;
    initrd_root->finddir = &initrd_finddir;
    initrd_root->ptr = 0;
    initrd_root->implementation = 0;
    // initialise the /dev directory (required)
    initrd_dev = (Vfs_node_t*)kmalloc(sizeof(Vfs_node_t));
    strcpy(initrd_dev->filename, "dev");
    initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
    initrd_dev->flags = VFS_DIR;
    initrd_dev->read = 0;
    initrd_dev->write = 0;
    initrd_dev->open = 0;
    initrd_dev->close = 0;
    initrd_dev->readdir = &initrd_readdir;
    initrd_dev->finddir = &initrd_finddir;
    initrd_dev->ptr = 0;
    initrd_dev->implementation = 0;

    root_nodes = (Vfs_node_t*)kmalloc(sizeof(Vfs_node_t*) * initrd_header->number_files);
    number_root_nodes = initrd_header->number_files;
    // for every file
    int i;
    for(i = 0; i < initrd_header->number_files; i++)
    {
        file_headers[i].offset += location;
        // create a new file node
        strcpy(root_nodes[i].filename, &file_headers[i].name);
        root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
        root_nodes[i].length = file_headers[i].length;
        root_nodes[i].inode = i;
        root_nodes[i].flags = VFS_FILE;
        root_nodes[i].read = &initrd_read;
        root_nodes[i].write = 0;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
        root_nodes[i].implementation = 0;
    }
    return initrd_root;
}