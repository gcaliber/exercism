#include <math.h>
#include "nth_prime.h"

int nth(int n)
{
    if (!n) return 0;
    
    int prime_count_guess = 0;
    int limit = 100;
    do {
        prime_count_guess = (int) (limit / log((double) limit));
        limit += limit / 10;
    } while (prime_count_guess < n);
    
    int candidates[limit];
    for (int i = 0, c = 3; c <= limit; i++, c += 2) {
        candidates[i] = c;
    }
    
    int p = 2;
    int prime_count = 1;
    int i;
    while(prime_count != n) {
        i = p / 2 - 1;
        while (!candidates[i]) i++;
        p = candidates[i];
        prime_count++;
        for (; i < limit; i += p) {
            candidates[i] = 0;
        }
    }
    
    return p;
}