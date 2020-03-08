#include "char.h"

char get_ascii_char(uint8 key_code)
{
    switch(key_code)
    {
        case KEY_A : return 'A';
        case KEY_B : return 'B';
        case KEY_C : return 'C';
        case KEY_D : return 'D';
        case KEY_E : return 'E';
        case KEY_F : return 'F';
        case KEY_G : return 'G';
        case KEY_H : return 'H';
        case KEY_I : return 'I';
        case KEY_J : return 'J';
        case KEY_K : return 'K';
        case KEY_L : return 'L';
    }
}