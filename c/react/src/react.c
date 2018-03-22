#include "react.h"
#include <stdlib.h>

struct reactor *create_reactor()
{
    struct reactor *r = malloc(sizeof(struct reactor));
    r->cells = malloc(sizeof(struct cell));
    r->cells_size = 1;
    r->cell_count = 0;
    return r;
}

void destroy_reactor(struct reactor *r) {
    if (r) return;
}

struct cell *create_input_cell(struct reactor *r, int initial_value)
{
    struct cell *c = malloc(sizeof(struct cell));
    r->cells[r->cell_count++] = *c;
    c->value = initial_value;
    c->a = NULL;
    c->b = NULL;
    c->f1 = NULL;
    c->f2 = NULL;
    c->cb = NULL;
    return c;
}

int get_cell_value(struct cell *c)
{
    return c->value;
}

void set_cell_value(struct cell *c, int new_value)
{
    c->value = new_value;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *a, compute1 f)
{
    struct cell *c = malloc(sizeof(struct cell));
    r->cells[r->cell_count++] = *c;
    c->value = f(a->value);
    c->a = a;
    c->b = NULL;
    c->f1 = &f;
    c->f2 = NULL;
    c->cb = NULL;
    return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *a, struct cell *b, compute2 f)
{
    struct cell *c = malloc(sizeof(struct cell));
    r->cells[r->cell_count++] = *c;
    c->value = f(a->value, b->value);
    c->a = a;
    c->b = b;
    c->f1 = NULL;
    c->f2 = &f;
    c->cb = NULL;
    return c;
}

// The callback should be called with the same void * given in add_callback.
callback_id add_callback(struct cell *c, void *v, callback cb)
{
    c->cb = &cb;
    if (v) return 0;
    return 0;
}

void remove_callback(struct cell *c, callback_id id)
{
    c->cb = NULL;
    if (id) return;
}