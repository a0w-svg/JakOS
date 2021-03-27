#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>
/*********************************************
* plays a sound at a specific frequency
* uint32_t num_frequency - sound frequency
*********************************************/
void play_sound(uint32_t num_frequence);
/***********************************************
* stops a sound
************************************************/
void no_sound();
/***********************************************
* plays a beep
************************************************/
void beep();
#endif