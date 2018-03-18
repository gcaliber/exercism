#include "sum_of_multiples.h"
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MIN_BUFFER_SIZE 8;

struct IntSet {
    int *buffer;
    int size;
    int items;
};

int find (IntSet *set, int n) {
    for (int i = 0; i < set->items - 1; i++) {
        if (set->buffer[i] == n)
            return 1;
    }
    return 0;
}

void add (IntSet *set, int n) {
    if (find(set, n) == 0) {
        if (set->items < set->size) {
            set->buffer[set->items++] = n;
        }
        else {
            set->size = floor(size * 1.5);
            set->buffer = (int *) realloc(set->buffer, sizeof(int) * set->size);
            set->buffer[items++] = n;
        }
    }
}


int sum_of_multiples(const unsigned int *multiples, int size, int max)
{
    struct IntSet *set;
    set->buffer = malloc(sizeof(int) * MIN_BUFFER_SIZE);
    set->size = MIN_BUFFER_SIZE;
    set->items = 0;
    
    for (int i = 0; i < size; i++) {
        int n = multiples[i];
        for (int m = n; m < max; m += n) {
            add(set, m);
        }
    }
}