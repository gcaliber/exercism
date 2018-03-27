#include "sieve.h"

unsigned int sieve(const unsigned int limit, primes_array_t primes)
{
    if (limit < 2) return 0;
    
    primes[0] = 2;
    int prime_count = 1;
    
    unsigned int candidates[MAX_LIMIT_TESTED];
    for (unsigned int i = 0, c = 3; c <= limit; i++, c += 2) {
        candidates[i] = c;
    }
    
    unsigned int p = 0;
    while(1) {
        unsigned int i = p / 2;
        while (!candidates[i]) i++;
        p = candidates[i];
        if (p > limit) break;
        primes[prime_count++] = p;
        for (; i < limit; i += p) {
            candidates[i] = 0;
        }
    }
    
    return prime_count;
}
