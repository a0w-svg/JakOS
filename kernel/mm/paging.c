#include "./include/paging.h"

k_page_dir_t *kernel_dir = 0;
k_page_dir_t *current_dir = 0;

uint32_t *frames;
uint32_t *num_frames;

extern uint32_t placement_addr;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

static void set_k_frame(uint32_t frame_address)
{
    uint32_t k_frame = frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(k_frame);
    uint32_t offset = OFFSET_FROM_BIT(k_frame);
    frames[idx] |= (0x1 << offset);
}

static void clean_k_frame(uint32_t frame_address)
{
    uint32_t k_frame = frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(k_frame);
    uint32_t offset = OFFSET_FROM_BIT(k_frame);
    frames[idx] &= ~(0x1 << offset);
}

static uint32_t test_k_frame(uint32_t frame_address)
{
    
}