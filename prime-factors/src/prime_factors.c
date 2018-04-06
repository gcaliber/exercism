#include "prime_factors.h"
#include <stdlib.h>
#include <math.h>

#define INITIAL_PRIME_COUNT 10

uint64_t next_prime(uint64_t p, primes_t *primes)
{
    if (p == 2) return 3;
    
    int limit = ((uint64_t) log((double) p)) / 2;
    if (limit < 2) limit = 2;
    
    uint64_t *candidates = malloc(sizeof(uint64_t) * limit);
    
    uint64_t next = 0;
    while (!next) {
        p += 2;
        for (int i = 0; i < limit; i++, p += 2) {
            candidates[i] = p;
        }
        
        for (int j = 0; j < limit; j++) {
            for (int i = 0; i < primes->count; i++) {
                if (candidates[j] % primes->arr[i] == 0) {
                    candidates[j] = 0;
                    if (primes->arr[i] > (uint64_t) sqrt(candidates[j])) break;
                }
            }
            if (candidates[j]) {
                next = candidates[j];
                break;
            }
        }
    }
    free(candidates);
    
    if (primes->count == primes->size) {
        primes->size = (int) (1.5 * primes->size);
        primes->arr = realloc(primes->arr, sizeof(uint64_t) * primes->size);
    }
    
    primes->arr[primes->count++] = next;
    return next;
}

size_t find_factors(uint64_t n, uint64_t *prime_factors)
{
    size_t pf_count = 0;
    
    primes_t primes;
    primes.size = INITIAL_PRIME_COUNT;
    primes.arr = malloc(sizeof(uint64_t) * primes.size);
    primes.arr[0] = 2;
    primes.arr[1] = 3;
    primes.count = 2;
    
    uint64_t p = 2;
    while (n != 1) {
        while (n % p == 0) {
            prime_factors[pf_count++] = p;
            n /= p;
        }
        p = next_prime(p, &primes);
    }

    free(primes.arr);
    return pf_count;
}