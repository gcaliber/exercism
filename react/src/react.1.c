#include "react.h"
#include <stdlib.h>

static int next_callback_id = 0;

struct reactor *create_reactor()
{
    struct reactor *r = malloc(sizeof(struct reactor));
    if (!r) {
        printf("DEBUG: malloc for reactor failed\n");
        return NULL;
    }
    r->cells = malloc(PTR_SIZE);
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
        struct cell **new_cells = realloc(r->cells, PTR_SIZE * new_size);
        if (new_cells) {
            r->cells = new_cells;
            r->cells_size = new_size;
        }
        else {
            printf("DEBUG: realloc failed\n");
            return NULL;
        }
    }
    struct cell *c = malloc(sizeof(struct cell));
    if (!c) {
        printf("DEBUG: malloc for new cell failed\n");
        return NULL;
    }
    r->cells[r->cell_count++] = c;
    c->dependencies.cell = NULL;
    c->dependencies.next = NULL;
    c->cb = NULL;
    return c;
}

struct cell *create_input_cell(struct reactor *r, int initial_value)
{
    struct cell *c = new_cell(r);

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

void update_dependencies(struct cell_node *current)
{
    struct cell *c = current->cell;
    if (c->a && c->b) {
        c->value = ((compute2)c->f)(c->a->value, c->b->value);
    }
    else {
        c->value = ((compute1)c->f)(c->a->value);
    }
    
    if (current->next) {
        update_dependencies(current->next);
    }
    
    if (c->dependencies.cell) {
        update_dependencies(&c->dependencies);
    }
}

void set_cell_value(struct cell *c, int new_value)
{
    c->value = new_value;
    if (c->dependencies.cell) {
        update_dependencies(&c->dependencies);
    }
}

void add_dependency(struct cell *parent, struct cell *dependency)
{
    struct cell_node *node = malloc(sizeof(struct cell_node));
    if (!parent->dependencies) {
        parent->dependencies = node;
    }
    else {
        struct cell_node *current = parent->dependencies;
        while (current->next) {
            current = current->next;
        }
        current->next = malloc(sizeof(struct cell_node));
        if (!current->next) {
            printf("DEBUG: malloc for cell_node failed\n");
            return;
        }
        current->next->cell = dependency;
        current->next->next = NULL;
    }
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *a, compute1 f)
{
    struct cell *c = new_cell(r);

    c->value = f(a->value);

    add_dependency(a, c);
    
    c->f = (void (*)())f;
    c->a = a;
    c->b = NULL;

    return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *a, struct cell *b, compute2 f)
{
    struct cell *c = new_cell(r);

    c->value = f(a->value, b->value);
    
    add_dependency(a, c);
    add_dependency(b, c);
    c->f = (void (*)())f;
    c->a = a;
    c->b = b;
    
    return c;
}

callback_id add_callback(struct cell *c, void *v, callback cb)
{
    struct cb_node *node = malloc(sizeof(struct cb_node));
    if (!c->cb) { 
        c->cb = node;
    }
    else {
        struct cb_node *current = c->cb;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
    node->cb = cb;
    node->param = v;
    id = next_callback_id++;
    struct cb_node next = NULL;
}

void remove_callback(struct cell *c, callback_id id)
{
    c->cb = NULL;
    if (id) return;
}