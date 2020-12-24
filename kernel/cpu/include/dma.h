#ifndef DMA_H
#define DMA_H

#include "../../../common/include/types.h"

#define DMA_MAX_CHANNELS 16
#define DMA_CHANNELS_PER_DMAC 8
// slave DMAC port 0
enum DMA0_IO 
{ 
    DMA0_STATUS_REG = 0x08,
    DMA0_CMD_REG = 0x08,
    DMA0_REQUEST_REG = 0x09,
    DMA0_CHANMASK_REG = 0x0A,
    DMA0_MODE_REG = 0x0B,
    DMA0_CLEARBYTE_FLIP_FLOP_REG = 0x0C,
    DMA0_TEMP_REG = 0x0D,
    DMA0_MASTER_CLEAR_REG = 0x0D,
    DMA0_CLEAR_MASK_REG = 0x0E,
    DMA0_MASK_REG = 0x0F
};
// Master DMAC port 1
enum DMA1_IO 
{
    DMA1_STATUS_REG = 0xD0,
    DMA1_CMD_REG = 0xD0,
    DMA1_REQUEST_REG = 0xD2,
    DMA1_CHANMASK_REG = 0xD4,
    DMA1_MODE_REG = 0xD6,
    DMA1_CLEARBYTE_FLIP_FLOP_REG = 0xD8,
    DMA1_INTER_REG = 0xDA,
    DMA1_UNMASK_ALL_REG = 0xDC,
    DMA1_MASK_REG = 0xDE
};
// Slave DMAC port 0
enum DMA0_CHANNEL_IO
{
    DMA0_CHANNEL0_ADDR_REG = 0,
    DMA0_CHANNEL0_COUNT_REG = 1,
    DMA0_CHANNEL1_ADDR_REG = 2,
    DMA0_CHANNEL1_COUNT_REG = 3,
    DMA0_CHANNEL2_ADDR_REG = 4,
    DMA0_CHANNEL2_COUNT_REG = 5,
    DMA0_CHANNEL3_ADDR_REG = 6,
    DMA0_CHANNEL3_COUNT_REG = 7
};
// Master DMAC port 1
enum DMA1_CHANNEL_IO
{
    DMA1_CHANNEL4_ADDR_REG = 0xC0,
    DMA1_CHANNEL4_COUNT_REG = 0xC2,
    DMA1_CHANNEL5_ADDR_REG = 0xC4,
    DMA1_CHANNEL5_COUNT_REG = 0xC6,
    DMA1_CHANNEL6_ADDR_REG = 0xC8,
    DMA1_CHANNEL6_COUNT_REG = 0xCA,
    DMA1_CHANNEL7_ADDR_REG = 0xCC,
    DMA1_CHANNEL7_COUNT_REG = 0xCE
};
// DMAC Extended Page Address Registers
enum DMA0_EX_PAGE_REG
{
    DMA_EX_PAGE_EXTRA0 = 0x80,
    DMA_EX_PAGE_EXTRA1 = 0x84,
    DMA_EX_PAGE_EXTRA2 = 0x85,
    DMA_EX_PAGE_EXTRA3 = 0x86,
    DMA_EX_PAGE_EXTRA4 = 0x8C,
    DMA_EX_PAGE_EXTRA5 = 0x8D,
    DMA_EX_PAGE_EXTRA6 = 0x8E,
    DMA_EX_PAGE_CHANNEL1_ADDRBYTE2 = 0x83,
    DMA_EX_PAGE_CHANNEL2_ADDRBYTE2 = 0x81,
    DMA_EX_PAGE_CHANNEL3_ADDRBYTE2 = 0x82,
    DMA_EX_PAGE_CHANNEL5_ADDRBYTE2 = 0x8B,
    DMA_EX_PAGE_CHANNEL6_ADDRBYTE2 = 0x89,
    DMA_EX_PAGE_CHANNEL7_ADDRBYTE2 = 0x8A,
    DMA_EX_PAGE_DRAM_REFRESH = 0x8F
};
// DMAC Commands registry masks
enum DMA_CMD_REG_MASK
{
    DMA_CMD_MASK_MEM_TO_MEM = 1,
    DMA_CMD_MASK_CHANNEL0_ADDR_HOLD = 2,
    DMA_CMD_MASK_ENABLE = 4,
    DMA_CMD_MASK_TIMING = 8,
    DMA_CMD_MASK_PRIORITY = 0x10,
    DMA_CMD_MASK_WRITESEL = 0x20,
    DMA_CMD_MASK_DREQ = 0x40,
    DMA_CMD_MASK_DACK = 0x80
};
// DMAC Mode Registry masks
enum DMA_MODE_REG_MASK
{
    DMA_MODE_MASK_SEL = 3,
    DMA_MODE_SELF_TEST = 0,
    DMA_MODE_READ_TRANSFER = 4,
    DMA_MODE_WRITE_TRANSFER = 8,
    DMA_MODE_MASK_AUTO = 0x10,
    DMA_MODE_MASK_IDEC = 0x20,
    DMA_MODE_MASK = 0xCA,
    DMA_MODE_TRANSFER_ON_DEMAND = 0,
    DMA_MODE_TRANSFER_SINGLE = 0x40,
    DMA_MODE_TRANSFER_BLOCK = 0x80,
    DMA_MODE_TRANSFER_CASCADE = 0xC0
};

void dma_set_address(uint8_t channel, uint8_t low, uint8_t high);
void dma_set_count(uint8_t channel, uint8_t low, uint8_t high);
void dma_set_extern_page_register(uint8_t reg, uint8_t value);
void dma_set_mode(uint8_t channel, uint8_t mode);
void dma_mask_channel(uint8_t channel);
void dma_unmask_channel(uint8_t channel);
void dma_unmask_all_channels();
void dma_set_read(uint8_t channel);
void dma_set_write(uint8_t channel);
void dma_reset_flip_flop(int dma);
void dma_reset();
#endif