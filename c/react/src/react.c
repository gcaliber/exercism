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

struct cell *new_cell(struct reactor *r) {
    if (r->cells_size == r->cell_count) {
        int new_size = r->cells_size * 2;
        struct cell *new_cells = realloc(r->cells, sizeof(struct cell) * new_size);
        if (new_cells) {
            r->cells = new_cells;
            r->cells_size = new_size;
        }
        else {
            return NULL;
        }
    }
    struct cell *c = &(r->cells[r->cell_count++]);
    c->next = NULL;
    c->cb = NULL;
    return c;
}

struct cell *create_input_cell(struct reactor *r, int initial_value)
{
    struct cell *c = new_cell(r);
    if (!c) return NULL;
    
    c->value = initial_value;
    c->f = NULL;
    c->a = NULL;
    c->b = NULL;
    return c;
}

int get_cell_value(struct cell *c)
{
    return c->value;
}

void update_dependencies(struct cell *c)
{
    if (c->a && c->b) {
        c->value = ((compute2)c->f)(c->a->value, c->b->value);
    }
    else {
        c->value = ((compute1)c->f)(c->a->value);
    }
    
    if (c->next) {
        update_dependencies(c->next);
    }
}

void set_cell_value(struct cell *c, int new_value)
{
    c->value = new_value;
    if (c->next) {
        update_dependencies(c->next);
    }
}

void add_child(struct cell *current, struct cell *child)
{
    while (current->next) {
        current = current->next;
    }
    current->next = child;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *a, compute1 f)
{
    struct cell *c = new_cell(r);
    if (!c) return NULL;
    
    c->value = f(a->value);

    add_child(a, c);
    c->f = (void (*)())f;
    c->a = a;
    c->b = NULL;

    return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *a, struct cell *b, compute2 f)
{
    struct cell *c = new_cell(r);
    if (!c) return NULL;
    
    c->value = f(a->value, b->value);
    
    add_child(a, c);
    add_child(b, c);
    c->f = (void (*)())f;
    c->a = a;
    c->b = b;
    
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