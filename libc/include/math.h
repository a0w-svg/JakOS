#ifndef MATH_H
#define MATH_H
/*****************************************
 * Get a random number
******************************************/
int rand();
/*******************************************
 * Set the start point of the number generator
 * *****************************************/
void srand(unsigned int seed);
/*********************************************
 * Simple number generator
 *  
 *********************************************/
int maxrand(int seed, int max);
#endif