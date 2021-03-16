#include "types.h"
// read 1 byte data from port register.
uint8_t port_byte_in(uint16_t port); 
// write 1 byte data to port register
void port_byte_out(uint16_t port, uint8_t data);
// read 2 bytes data from port register
uint16_t port_word_in(uint16_t port);
// write 2 bytes data to port register
void port_word_out(uint16_t port, uint16_t data);
// read 4 bytes data from port register
uint32_t port_long_in(uint16_t  port);
// write 4 bytes data from port register
void port_long_out(uint16_t port, uint32_t data);
