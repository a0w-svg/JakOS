#ifndef STRING_H
#define STRING_H
/****************************************
convert int type to ascii
int base atrributs:
    d - decimal number
    x - hexadecimal number
int d - source int type
char* buffer - destination product
******************************************/
void int_to_ascii(char* buffer, int base, int d);
/*********************************************
 * convert ascii to int and return int
**********************************************/
int atoi(const char* str);
/*******************************************
 reverses a string
    example:
        before: Hello
        after: olleH
********************************************/
void reverse(char s[]);
/*******************************************
    return the string length
********************************************/
int strlen(const char c[]);
/*******************************************
 * removes the last char from the string
********************************************/
void back_space(char c[]);
/********************************************
 * Appends a character to a string
*********************************************/
void append(char c[], char num);
/**************************************************
    Compares two strings and if c[] and c2[] are 
    equal return 0 or if c[] and c2[] are not equal
    return 1.
*****************************************************/
int strcmp(char c[], char c2[]);
char *strcpy(char *dest, const char *src);
/*************************************************************
 * Removes the character from the string.
 * char *s - the string from which you want to remove a character
 * char c - the character you want to remove from the string
**************************************************************/
void remove_from_string(char *s, char c);
/*********************************************
 * Convert uppercase to lowercase
 *********************************************/
char lower_case(char ch);
/*********************************************
 * Convert lowercase to uppercase
**********************************************/
char upper_case(char ch);

#endif