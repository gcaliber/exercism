#include "roman_numerals.h"
#include <string.h>
#include <stdlib.h>

char * to_roman_numeral(int n)
{
    char *buffer = malloc(MAX_BUFFER);
    for (int place = 1000, place_index = 3; place > 0; place /= 10, place_index--) {
        int digit = n % (place * 10) / place;
        strcat(buffer, roman_numerals[place_index][digit]);
    }
    return buffer;
}