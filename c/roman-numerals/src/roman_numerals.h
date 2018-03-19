#ifndef ROMAN_NUMERALS_H
#define ROMAN_NUMERALS_H


#define MAX_BUFFER 20

static const char roman_numerals[4][10][5] = 
{
    { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" },
    { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" },
    { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" },
    { "", "M", "MM", "MMM" }
};

char * to_roman_numeral(int n);

#endif