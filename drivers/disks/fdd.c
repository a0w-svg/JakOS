#include "./include/fdd.h"
#include "../../kernel/cpu/include/dma.h"
#include "../../common/include/kpanic.h"
#include "../../common/include/port.h"
#include <stdbool.h>

enum FDD_REGISTERS
{
    STATUS_REG_A = 0x3F0,
    STATUS_REG_B = 0x3F1,
    DIGITAL_OUTPUT_REG = 0x3F2,
    TAPE_DRIVE_REG = 0x3F3,
    MAIN_STATUS_REG = 0x3F4,
    DATARATE_SELECT_REG = 0x3F4,
    DATA_FIFO = 0x3F5,
    DIGITAL_INPUT_REG = 0x3F7,
    CONF_CONTROL_REG = 0x3F7
};

enum FDD_CMD
{
    READ_TRACK = 2,
    SPECIFY = 3,
    SENSE_DRIVE_STATUS = 4,
    WRITE_DATA = 5,
    READ_DATA = 6,
    RECALIBRATE = 7,
    SENSE_INTERRUPT = 8,
    WRITE_DELETED_DATA = 9,
    READ_ID = 10,
    READ_DELETED_DATA = 12,
    FORMAT_TRACK = 13,
    DUMPREG = 14,
    SEEK = 15,
    VERSION = 16,
    SCAN_EQUAL = 17,
    PERPENDICULAR_MODE = 18,
    CONFIGURE = 19,
    LOCK = 20,
    VERIFY = 22,
    SCAN_LOW_OR_EQUAL = 25,
    SCAN_HIGH_OR_EQUAL = 29
};
enum FDD_CMD_EXENT
{
    FDD_CMD_EXT_SKIP = 0x20,
    FDD_CMD_EXT_DENSITY = 0x40,
    FDD_CMD_EXT_MULTITRACK = 0x80
};
enum GAP3_LEN
{
    GAP3_LEN_STD = 42,
    GAP3_LEN_5_14 = 32,
    GAP3_LEN_3_5 = 27
};
enum FDD_SECTOR_DTL
{
    FDD_SECTOR_DTL_128 = 0,
    FDD_SECTOR_DTL_256 = 1,
    FDD_SECTOR_DTL_512 = 2,
    FDD_SECTOR_DTL_1024 = 4
};
enum MSR_MASK
{
    MSR_MASK_DRIVE1_POS_MODE = 1,
    MSR_MASK_DRIVE2_POS_MODE = 2,
    MSR_MASK_DRIVE3_POS_MODE = 4,
    MSR_MASK_DRIVE4_POS_MODE = 8,
    MSR_MASK_BUSY = 16,
    MSR_MASK_DMA = 32,
    MSR_MASK_DATA_IO = 64,
    MSR_MASK_DATA_REG = 128
};
enum DOR_MASK
{
    DOR_MASK_DRIVE0 = 0,
    DOR_MASK_DRIVE1 = 1,
    DOR_MASK_DRIVE2 = 2,
    DOR_MASK_DRIVE3 = 3,
    DOR_MASK_RESET = 4,
    DOR_MASK_DMA = 8,
    DOR_MASK_DRIVE0_MOTOR = 16,
    DOR_MASK_DRIVE1_MOTOR = 32,
    DOR_MASK_DRIVE2_MOTOR = 64,
    DOR_MASK_DRIVE3_MOTOR = 128
};
#define FDD_SECTORS_PER_TRACK = 18
#define  FDC_DMA_CHANNEL  2
#define  DMA_BUF  0x1000
static  uint8_t _current_drive = 0;
static volatile uint8_t _FDD_IRQ = 0;
bool fdd_initialize_dma(uint8_t* buf, unsigned length)
{
    union 
    {
        uint8_t byte[4];
        uint64_t len;
    }a, b;
    a.len = (unsigned)buf;
    b.len = (unsigned)length;
    if((a.len >> 24) || (b.len >> 16) || (((a.len & 0xFFFF) + b.len) >> 16))
    {
        return false;
    }

    dma_reset();
    dma_mask_channel(FDC_DMA_CHANNEL);
    dma_reset_flip_flop(1);
    dma_set_address(FDC_DMA_CHANNEL, a.byte[0], a.byte[1]);
    dma_reset_flip_flop(1);
    dma_set_count(FDC_DMA_CHANNEL, b.byte[0], b.byte[1]);
    dma_set_read(FDC_DMA_CHANNEL);
    dma_unmask_all_channels();
    return true;
}

uint8_t fdc_read_status()
{
    return port_byte_in(MAIN_STATUS_REG);
}
void fdd_write_dor(uint8_t value)
{
    port_byte_out(DIGITAL_OUTPUT_REG, value);
}

void fdc_send_cmd(uint8_t cmd)
{
    for(int i = 0; i < 500; i++)
    {
        if(fdc_read_status() && MSR_MASK_DATA_REG)
        {
            return port_byte_out(DATA_FIFO, cmd);
        }
    }
}

uint8_t fdc_read_data()
{
    for(int i = 0; i < 500; i++)
    {
        if(fdc_read_status() && MSR_MASK_DATA_REG)
            return port_byte_in(DATA_FIFO);
    }
    return 0;
}

void fdc_write_ccr(uint8_t value)
{
    port_byte_out(CONF_CONTROL_REG, value);
}

inline void fdc_wait_irq()
{
    while (_FDD_IRQ == 0) {};
    _FDD_IRQ = 0;
}

void fdd_irq_handler()
{
    asm("add esp, 12");
    asm("pushad");
}
void fdd_dma_read()
{
}

void fdd_write();