#include "secret_handshake.h"
#include <stdlib.h>

#include <stdio.h>

#define REVERSE_BIT 4



const char ** commands(int code)
{
    const char **result = calloc(REVERSE_BIT, (sizeof(char *)));
    
    if (code & (1 << REVERSE_BIT)) {
        for (int bit = REVERSE_BIT - 1, i = 0; bit >= 0; bit--) {
            if (code & (1 << bit)) {
                switch(bit) {
                    case 0:
                        result[i++] = "wink";
                        break;
                    case 1:
                        result[i++] = "double blink";
                        break;
                    case 2:
                        result[i++] = "close your eyes";
                        break;
                    case 3:
                        result[i++] = "jump";
                }
            }
        }
    }
    else {
        for (int bit = 0, i = 0; bit < REVERSE_BIT; bit++) {
            if (code & (1 << bit)) {
                switch(bit) {
                    case 0:
                        result[i++] = "wink";
                        break;
                    case 1:
                        result[i++] = "double blink";
                        break;
                    case 2:
                        result[i++] = "close your eyes";
                        break;
                    case 3:
                        result[i++] = "jump";
                }
            }
        }
    }
    
    return result;
}