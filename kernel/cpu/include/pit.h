/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+               JakOS Project                             +
+                                                         +
+                                                         +
+    Module: Programmable Interval Timer                  +
+                                                         +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef PIT_H
#define PIT_H
#include "../../../common/include/types.h"
//initialize PIC
void init_timer(uint32_t frequency);
void sleep(uint32_t ticks);
#endif