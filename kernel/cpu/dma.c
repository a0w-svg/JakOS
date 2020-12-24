#include "./include/dma.h"
#include "../../common/include/port.h"

void dma_set_address(uint8_t channel, uint8_t low, uint8_t high)
{
    if(channel > 8)
        return;
    
    uint16_t port  = 0;
    switch (channel)
    {
    case 0:
        port = DMA0_CHANNEL0_ADDR_REG;
        break;
    case 1:
        port = DMA0_CHANNEL1_ADDR_REG;
        break;
    case 2:
        port = DMA0_CHANNEL2_ADDR_REG;
        break;
    case 3:
        port = DMA0_CHANNEL3_ADDR_REG;
        break;
    case 4:
        port = DMA1_CHANNEL4_ADDR_REG;
        break;
    case 5:
        port = DMA1_CHANNEL5_ADDR_REG;
        break;
    case 6:
        port = DMA1_CHANNEL6_ADDR_REG;
        break;
    case 7:
        port = DMA1_CHANNEL7_ADDR_REG;
    default:
        break;
    }
    port_byte_out(port, low);
    port_byte_out(port, high);
}
void dma_set_count(uint8_t channel, uint8_t low, uint8_t high)
{
    if(channel > 8)
        return;
    uint16_t port = 0;
    switch (channel)
    {
    case 0:
        port = DMA0_CHANNEL0_COUNT_REG;
        break;
    case 1:
        port = DMA0_CHANNEL1_COUNT_REG;
        break;
    case 2:
        port = DMA0_CHANNEL2_COUNT_REG;
        break;
    case 3:
        port = DMA0_CHANNEL3_COUNT_REG;
        break;
    case 4:
        port = DMA1_CHANNEL4_COUNT_REG;
        break;
    case 5:
        port = DMA1_CHANNEL5_COUNT_REG;
        break;
    case 6:
        port = DMA1_CHANNEL6_COUNT_REG;
        break;
    case 7:
        port = DMA1_CHANNEL7_COUNT_REG;
        break;
    default:
        break;
    }
    port_byte_out(port, low);
    port_byte_out(port, high);
}
void dma_set_extern_page_register(uint8_t reg, uint8_t value)
{
    if(reg > 14)
        return;

    uint16_t port = 0;
    switch (reg)
    {
    case 1:
        port = DMA_EX_PAGE_CHANNEL1_ADDRBYTE2;
        break;
    case 2:
        port = DMA_EX_PAGE_CHANNEL2_ADDRBYTE2;
        break;
    case 3:
        port = DMA_EX_PAGE_CHANNEL3_ADDRBYTE2;
        break;
    case 4:
        return;
    case 5:
        port = DMA_EX_PAGE_CHANNEL5_ADDRBYTE2;
        break;
    case 6:
        port = DMA_EX_PAGE_CHANNEL6_ADDRBYTE2;
        break;
    case 7:
        port = DMA_EX_PAGE_CHANNEL7_ADDRBYTE2;
        break;
    default:
        break;
    }
    port_byte_out(port, value);
}

void dma_set_mode(uint8_t channel, uint8_t mode)
{
    int dma = (channel < 4) ? 0 : 1;
    int channel1 = (dma == 0)  ? channel : (channel - 4);

    dma_mask_channel(channel);
    port_byte_out((channel < 4) ? (DMA0_MODE_REG) : DMA1_MODE_REG, channel1 | (mode));
    dma_unmask_all_channels(dma);
}

void dma_set_read(uint8_t channel)
{
    dma_set_mode(channel, DMA_MODE_READ_TRANSFER | DMA_MODE_TRANSFER_SINGLE | DMA_MODE_MASK_AUTO);
}

void dma_set_write(uint8_t channel)
{
    dma_set_mode(channel, DMA_MODE_WRITE_TRANSFER | DMA_MODE_TRANSFER_SINGLE | DMA_MODE_MASK_AUTO);
}

void dma_mask_channel(uint8_t channel)
{
    if(channel <= 4)
        port_byte_out(DMA0_CHANMASK_REG, (1 << (channel - 1)));
    else
    {
        port_byte_out(DMA1_CHANMASK_REG, (1 << (channel - 5)));
    }
}
void dma_unmask_channel(uint8_t channel)
{
    if(channel <= 4)
        port_byte_out(DMA0_CHANMASK_REG, channel);
    else
    {
        port_byte_out(DMA1_CHANMASK_REG, channel);
    }
    
}

void dma_unmask_all_channels()
{
    port_byte_out(DMA1_UNMASK_ALL_REG, 0xFF);
}

void dma_reset_flip_flop(int dma)
{
    if(dma < 2)
        return;
    port_byte_out((dma == 0) ? DMA0_CLEARBYTE_FLIP_FLOP_REG : DMA1_CLEARBYTE_FLIP_FLOP_REG, 0xFF);
}

void dma_reset()
{
    port_byte_out(DMA0_TEMP_REG, 0xFF);
}