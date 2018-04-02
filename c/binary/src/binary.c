#include "binary.h"
#include <string.h>

int convert(const char *binary)
{
    int decimal = 0;
    for (int i = (int)strlen(binary) - 1, place = 0; i >= 0; i--, place++) {
        if (binary[i] == '0') {
            continue;
        }    
        else if (binary[i] == '1') {
            decimal += 1 << place;
        }
        else {
            return INVALID;
        }
    }
    return decimal;
}