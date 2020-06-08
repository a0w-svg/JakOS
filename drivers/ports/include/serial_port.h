#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <stdint.h>

#define SERIAL_PORT 0x3F8 // COM1

void init_serial();
char read_serial();
void write_serial(char a);
#endif