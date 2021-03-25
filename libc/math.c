#include "./include/math.h"
#include "../kernel/cpu/include/rtc.h"
#include "../kernel/mm/include/kmalloc.h"
#include <stdint.h>

unsigned long next = 1;
int rand()
{
    time_t *time = kmalloc(sizeof(time_t));
    next = time->second * 10;
    next = next * 1103515245 + 12345;
    free(time);
    return (uint32_t)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}
int random_seed = 0;
int maxrand(int seed, int max)
{
    random_seed = random_seed + seed * 1103515245 + 12345;
    return (uint32_t)(random_seed / 65536) % (max + 1);
}