#ifndef INITRD_H
#define INITRD_H

#include <stdint.h>
#include <vfs.h>

typedef struct 
{
   uint32_t number_files;
}initrd_header_t;

typedef struct 
{
    uint8_t magic;   // Magic number, for error checking
    int8_t name[64]; // filename
    uint32_t offset; // offset int the initrd that the file starts
    uint32_t length; // length of the file
}initrd_file_header_t;

Vfs_node_t* init_initrd(uint32_t location);
#endif