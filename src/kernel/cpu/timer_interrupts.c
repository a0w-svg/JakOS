/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&                   JakOS Project                           &
&                                                           &
&   license: todo later                                     &
&                                                           &
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

#include "../../drivers/include/screen.h"
#include "../../common/include/types.h"
#include "./include/isr.h"
#include "../../libc/include/unused.h"
#include "../../libc/include/string.h"
//clock varivable timer
uint32 clock = 0;
//callback timer
static void time_callback(registers_t reg)
{
    clock++;
    screen_write("Time: ");

    char time_ascii[256];
    int_to_ascii(clock, time_ascii);
    screen_write(time_ascii);
    screen_write("\n");
    UNUSED(reg);
}
//initialize timer func
void init_timer(uint32 frequency)
{
    reg_interrupt_handler(IRQ0, time_callback);

    uint32 divisor = 1193180 / frequency;
    uint8 low_freq = (uint8)(divisor & 0xFF);
    uint8 high_freq = (uint8)((divisor >> 8) & 0xFF);

    out_byte(0x43, 0x36);
    out_byte(0x40, low_freq);
    out_byte(0x40, high_freq);
}