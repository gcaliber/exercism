#ifndef PRIME_FACTORS_H
#define PRIME_FACTORS_H

#include <stddef.h>
#include <stdint.h>

#define MAXFACTORS 100

typedef struct {
    uint64_t *arr;
    int size;
    int count;
} primes_t;

size_t find_factors(uint64_t n, uint64_t *prime_factors);

#endif