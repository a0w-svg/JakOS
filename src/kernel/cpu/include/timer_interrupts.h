/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+               JakOS Project                             +
+   useful resources:                                     +
+   https://wiki.osdev.org/Programmable_Interval_Timer    +
+                                                         +
+                                                         +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef TIMER_INTERRUPTS_H
#define TIMER_INTERRUPTS_H
#include "../../../common/include/types.h"
//initialize PIC
void init_timer(uint32_t frequency);
#endif