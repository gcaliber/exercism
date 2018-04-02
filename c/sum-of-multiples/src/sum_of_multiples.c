#include "sum_of_multiples.h"
#include "../../lib/set_int.h"
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h>

#define MIN_BUFFER_SIZE 8

int sum_ints(int *nums, int size);

int sum_of_multiples(const unsigned int *multiples, int size, int max)
{
    if (!multiples) return 0;

    struct SetInt set;
    set.buffer = malloc(sizeof(int) * MIN_BUFFER_SIZE);
    set.size = MIN_BUFFER_SIZE;
    set.items = 0;
    
    for (int i = 0; i < size; i++) {
        int n = multiples[i];
        if (n == 0) return 0;
        for (int m = n; m < max; m += n) {
            set_int_add(&set, m);
        }
    }
    int sum = sum_ints(set.buffer, set.items);
    free(set.buffer);
    return sum;
}

int sum_ints(int *nums, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += nums[i];
    }
    return sum;
}