#include "./include/serial_port.h"
#include "../../common/include/port.h"
#define SERIAL_PORT 0x3F8 // COM1
void init_serial()
{
   port_byte_out(SERIAL_PORT + 1, 0x00);
   port_byte_out(SERIAL_PORT + 3, 0x80);
   port_byte_out(SERIAL_PORT + 0, 0x03);
   port_byte_out(SERIAL_PORT + 1, 0x00);
   port_byte_out(SERIAL_PORT + 3, 0x03);
   port_byte_out(SERIAL_PORT + 2, 0xC7);
   port_byte_out(SERIAL_PORT + 4, 0x0B);
}

int serial_received()
{
    return port_byte_in(SERIAL_PORT + 5) & 1;
}
char read_serial()
{
    while (serial_received() == 0);
    return port_byte_in(SERIAL_PORT);
}
int is_transmit_empty()
{
    return port_byte_in(SERIAL_PORT + 5) & 0x20;
}
void write_serial(char a)
{
    while(is_transmit_empty() == 0);
    port_byte_out(SERIAL_PORT, a);
}

void write_serial_string(const char* txt)
{
    int i = 0;
    while(txt[i] != 0)
    {
        write_serial(txt[i]);
        i++;
    }
}