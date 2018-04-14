#include "secret_handshake.h"
#include <stdlib.h>

#define REVERSE_BIT 4

int check_bit(const char **result, int code, int bit, int i)
{
    if (!(code & (1 << bit))) return 0;
    switch(bit) {
        case 0:
            result[i] = "wink";
            break;
        case 1:
            result[i] = "double blink";
            break;
        case 2:
            result[i] = "close your eyes";
            break;
        case 3:
            result[i] = "jump";
    }
    return 1;
}

const char ** commands(int code)
{
    const char **result = calloc(REVERSE_BIT, (sizeof(char *)));
    
    int i = 0;
    if (code & (1 << REVERSE_BIT)) {
        for (int bit = REVERSE_BIT - 1; bit >= 0; bit--) {
            i += check_bit(result, code, bit, i);
        }
    }
    else {
        for (int bit = 0; bit < REVERSE_BIT; bit++) {
            i += check_bit(result, code, bit, i);
        }
    }
    
    return result;
}