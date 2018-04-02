#include "set_int.h"
#include <stdlib.h>
#include <math.h>

#include <stdio.h>

int set_int_find(struct SetInt *set, int n) {
    for (int i = 0; i < set->items; i++) {
        if (set->buffer[i] == n)
            return i;
    }
    return -1;
}

void set_int_add(struct SetInt *set, int n) {
    if (set_int_find(set, n) == -1) {
        if (set->items == set->size) {
            set->size = (int) floor(set->size * 1.5);
            set->buffer = realloc(set->buffer, sizeof(int) * set->size);
        }
        set->buffer[set->items++] = n;
    }
}

void set_int_remove(struct SetInt *set, int n) {
    int index = set_int_find(set, n);
    if (index != -1) {
        set->buffer[index] = set->buffer[--set->items];
        if (set->size > set->items * 2) {
            set->size = (int) floor(set->items * 1.5);
            set->buffer = realloc(set->buffer, sizeof(int) * set->size);
        }
    }
}


