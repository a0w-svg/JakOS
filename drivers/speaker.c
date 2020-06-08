#include "./include/speaker.h"
#include "../kernel/cpu/include/pit.h"
void play_sound(uint32_t num_frequence)
{
    uint32_t Division;
    uint8_t buffer;

    Division = 1193180 / num_frequence;
    port_byte_out(0x43, 0xb6);
    port_byte_out(0x42, (uint8_t) (Division));
    port_byte_out(0x42, (uint8_t) (Division >> 8));

    buffer = port_byte_in(0x61) & 0xFC;
    if(buffer != (buffer | 3))
    {
        port_byte_out(0x61, buffer | 3);
    }
}
void no_sound()
{
    uint8_t buffer = port_byte_in(0x61) & 0xFC;
    port_byte_out(0x61, buffer);
}
void beep()
{
    play_sound(1000);
    sleep(10);
    no_sound();
}