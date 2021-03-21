#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <stdint.h>

void init_serial();
char read_serial();
void write_serial(char a);
void write_serial_string(const char* txt);
#endif