#include "grains.h"

unsigned long intpow(int n, int p)
{
    if (p == 0) return 1;
    if (p == 1) return n;
    return n * intpow(n, p - 1);
}

unsigned long square(int n)
{
    if (n < 1 || n > 64) return 0;
    return intpow(2, n - 1);
}

unsigned long total() {
    unsigned long result = 0;
    for (int i = 0; i < 64; i++) {
        result += intpow(2, i);
    }
    return result;
}