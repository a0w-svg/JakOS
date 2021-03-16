#include "./include/ata.h"
#include "../../common/include/port.h"
//  Status Registers
#define STATUS_BSY 0x80 // busy... executing a command
#define STATUS_RDY 0x40 // ready to accept command
#define STATUS_DRQ 0x08 // controller expecting data
#define STATUS_DF 0x20
#define STATUS_ERROR 0x01 // error
// Wait if the Controller is busy. If the controller finishes the task, the wait is terminated
static void ata_wait_bsy();
// Wait until the drive has PIO data to transfer, or is ready to accept PIO data
static void ata_wait_drq();

void read_sectors_ata_pio(uint32_t* target_addr, uint32_t LBA, uint8_t sec_count)
{
    ata_wait_bsy();
    port_byte_out(0x1F6, 0xE0 | ((LBA >> 24) & 0xF));
    port_byte_out(0x1F2, sec_count);
    port_byte_out(0x1F3, (uint8_t)LBA);
    port_byte_out(0x1F4, (uint8_t)(LBA >> 8));
    port_byte_out(0x1F5, (uint8_t)(LBA >> 16));
    port_byte_out(0x1F7, 0x20);

    uint16_t* target = (uint16_t*)target_addr;
    for(int i = 0; i < sec_count; i++)
    {
        ata_wait_bsy();
        ata_wait_drq();
        for(int j = 0; j < 256; j++)
            target[j] = port_word_in(0x1F0);
        target += 256;
    }
}
void write_sectors_ata_pio(uint32_t LBA, uint8_t sec_count, uint32_t* bytes)
{
    ata_wait_bsy();
    port_byte_out(0x1F6, 0xE0 | ((LBA >> 24) & 0xF));
    port_byte_out(0x1F2, sec_count);
    port_byte_out(0x1F3, (uint8_t)LBA);
    port_byte_out(0x1F4, (uint8_t)(LBA >> 8));
    port_byte_out(0x1F5, (uint8_t)(LBA >> 16));
    port_byte_out(0x1F7, 0x30);

    for(int i = 0; i < sec_count; i++)
    {
        ata_wait_bsy();
        ata_wait_drq();
        for(int j = 0; j < 256; j++)
        {
            port_long_out(0x1F0, bytes[j]);
        }
    }
}

static void ata_wait_bsy() // wait for bsy to be 0
{
    while(port_byte_in(0x1F7) & STATUS_BSY);
}
static void ata_wait_drq() // wait for drq to be 1
{
    while(!(port_byte_in(0x1F7) & STATUS_RDY));
}