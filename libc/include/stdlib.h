#ifndef STDLIB_H
#define STDLIB_H
/*****************************************
* Get a random number
******************************************/
int rand();
/*******************************************
* Set the start point of the number generator
********************************************/
void srand(unsigned int seed);
/*********************************************
* Simple number generator
*  
*********************************************/
int maxrand(int seed, int max);
/*************************************************************
 * stops the program for the specified number of milliseconds
**************************************************************/
void Sleep(unsigned int ticks);
/**************************************************************
 * Encrypt string
***************************************************************/
void encrypt(char plainText[]);
#endif