#include "./include/vfs.h"

Vfs_node_t *vfs_root;

uint32_t vfs_read(Vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer)
{
    // check if the node has the read callback
    if(node->read != 0)
        // return read callback
        return node->read(node, offset, size, buffer);
    else
    {
        return 0;
    }
}
uint32_t vfs_write(Vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer)
{
    // check if the node has the write callback
    if(node->write != 0)
        return node->write(node, offset, size, buffer);
}
void vfs_open(Vfs_node_t* node, uint8_t read, uint8_t write)
{
    // check if the node has an open callback
    if(node->open != 0)
        return node->open(node);
}
void vfs_close(Vfs_node_t* node)
{
    // check if the node has the close callback
    if(node->close != 0)
        return node->close(node);
}
struct dirent* vfs_readdir(Vfs_node_t* node, uint32_t index)
{
    // check if the node is a directory and does it have a callback
    if((node->flags & VFS_MOUNTPOINT ) == VFS_DIR && node->readdir != 0)
        return node->readdir(node, index);
    else
    {
        return 0;
    }
}
Vfs_node_t* vfs_finddir(Vfs_node_t* node, char* name)
{
    // check if the node is a directory and does it have a callback
    if((node->flags & VFS_MOUNTPOINT) == VFS_DIR && node->finddir != 0)
        return node->finddir(node, name);
    else
    {
        return 0;
    }
}