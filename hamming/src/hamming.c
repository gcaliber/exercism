#include "hamming.h"
#include <string.h>

int compute(const char *a, const char *b)
{
    if (!a || !b) return -1;
    
    size_t len;
    if ((len = strlen(a)) != strlen(b)) return -1;
    
    int hamming = 0;
    for (size_t i = 0; i < len; i++) {
        hamming += a[i] != b[i];
    }
    return hamming;
}