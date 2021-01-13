#ifndef STRING_H
#define STRING_H

void int_to_ascii(int num, char str[]);
void hex_to_ascii(int num, char str[]);
void hex_to_dec(int num);
void reverse(char s[]);
int strlen(const char c[]);
void back_space(char c[]);
void append(char c[], char num);
int strcmp(char c[], char c2[]);
void remove_from_string(char *s, char c);
char lower_case(char ch);
char upper_case(char ch);

#endif