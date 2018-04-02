#ifndef REACT_H
#define REACT_H

#include <stdio.h>
#include <stdbool.h>

#define PTR_SIZE sizeof(int *)

typedef int (*compute1) (int);
typedef int (*compute2) (int, int);

typedef void (*callback) (void *, int);
typedef int callback_id;

struct reactor {
    struct cell **cells;
    int cells_size;
    int cell_count;
};

struct cell_node {
    struct cell *cell;
    struct cell_node *next;
};

struct cb_node {
    callback cb;
    void *param;
    callback_id id;
    struct cb_node *next;
};

struct cell {
    int value;
    int old_value;
    bool updated;
    void (*f)();
    struct cell *a;
    struct cell *b;
    struct cb_node *cb;
    struct cell_node *dependencies;
};

struct reactor *create_reactor();
// destroy_reactor should free all cells created under that reactor.
void destroy_reactor(struct reactor *);

struct cell *create_input_cell(struct reactor *, int initial_value);
struct cell *create_compute1_cell(struct reactor *, struct cell *, compute1);
struct cell *create_compute2_cell(struct reactor *, struct cell *,
                                  struct cell *, compute2);

int get_cell_value(struct cell *);
void set_cell_value(struct cell *, int new_value);

// The callback should be called with the same void * given in add_callback.
callback_id add_callback(struct cell *, void *, callback);
void remove_callback(struct cell *, callback_id);

#endif
