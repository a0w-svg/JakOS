#ifndef FDD_H
#define FDD_H
#include "../../../common/include/types.h"

bool fdd_initialize_dma(uint8_t* buf, unsigned length);
void fdd_dma_read();
void fdd_write();
#endif