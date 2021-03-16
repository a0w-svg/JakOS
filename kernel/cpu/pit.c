/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&                   JakOS Project                           &
&                                                           &
&   license: todo later                                     &
&   Module: Programmable Interval Timer                     &
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
#include "./include/pit.h"
#include "../../drivers/include/screen.h"
#include "../../common/include/types.h"
#include "./include/isr.h"
#include "../../common/include/types.h"
#include "../../libc/include/string.h"
#include "../../common/include/port.h"
//clock varivable timer

#define PIT_CHANNEL0 0x40
#define PIT_CHANNEL1 0x41
#define PIT_CHANNEL2 0x42
#define PIT_CMD_REG 0x43
uint32_t clock = 0;
//callback timer
static void time_callback(registers_t *reg)
{
    clock++;
    UNUSED(reg);
}
//initialize timer func
void init_timer(uint32_t frequency)
{
    reg_interrupt_handler(IRQ0, time_callback);

    uint32_t divisor = 1193180 / frequency;
    uint8_t low_freq = (uint8_t)(divisor & 0xFF);
    uint8_t high_freq = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(PIT_CMD_REG, 0x36);
    port_byte_out(PIT_CHANNEL0, low_freq);
    port_byte_out(PIT_CHANNEL0, high_freq);
}

void sleep(uint32_t ticks)
{
    unsigned long eticks;
    eticks = clock + ticks;
    while(clock < eticks);
}
