#ifndef SET_INT_H
#define SET_INT_H

struct SetInt {
    int *buffer;
    int size;
    int items;
};

int set_int_find(struct SetInt *set, int n);
void set_int_add(struct SetInt *set, int n);
void set_int_remove(struct SetInt *set, int n);

#endif