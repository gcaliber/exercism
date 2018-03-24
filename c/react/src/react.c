#include "react.h"
#include <stdlib.h>

static int next_callback_id = 0;

struct reactor *create_reactor()
{
    struct reactor *r = malloc(sizeof(struct reactor));
    if (!r) {
        fprintf(stderr, "DEBUG: malloc for reactor failed.\n");
        return NULL;
    }
    r->cells = malloc(PTR_SIZE);
    if (!r->cells) {
        fprintf(stderr, "DEBUG: malloc for reactor->cells failed.\n");
        return NULL;
    }
    r->cells_size = 1;
    r->cell_count = 0;
    return r;
}

void destroy_nodes(struct cell *c) {
    struct cb_node *current_cb = c->cb;
    while (current_cb) {
        struct cb_node *old_cb = current_cb;
        current_cb = current_cb->next;
        free(old_cb);
    }
    
    struct cell_node *current_c = c->dependencies;
    while (current_c) {
        struct cell_node *old_c = current_c;
        current_c = current_c->next;
        free(old_c);
    }
}

void destroy_reactor(struct reactor *r) {
    for (int i = 0; i < r->cell_count; i++) {
        struct cell *c = r->cells[i];
        destroy_nodes(c);
        free(c);
    }
    free(r->cells);
    free(r);
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
        fprintf(stderr, "DEBUG: malloc for new cell failed\n");
        return NULL;
    }
    r->cells[r->cell_count++] = c;
    c->updated = false;
    c->dependencies = NULL;
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
    if (!c->updated) {
        c->old_value = c->value;
        c->updated = true;
    }
    if (c->a && c->b) {
        c->value = ((compute2)c->f)(c->a->value, c->b->value);
    }
    else {
        c->value = ((compute1)c->f)(c->a->value);
    }

    if (c->dependencies && c->old_value != c->value) {
        update_dependencies(c->dependencies);
    }

    if (current->next) {
        update_dependencies(current->next);
    }
}

void do_callbacks(struct cb_node *node, int value)
{
    if (!node) return;
    (node->cb)(node->param, value);
    do_callbacks(node->next, value);
}

void fire_callbacks(struct cell *c) {
    if (!c->updated) return;
    
    if (c->value == c->old_value) {
        c->updated = false;
        return;
    }
    
    do_callbacks(c->cb, c->value);
    c->updated = false;
    
    struct cell_node *current = c->dependencies;
    while (current) {
        fire_callbacks(current->cell);
        current = current->next;
    }
}

void set_cell_value(struct cell *c, int new_value)
{
    c->value = new_value;
    c->updated = true;
    if (c->dependencies) {
        update_dependencies(c->dependencies);
        fire_callbacks(c);
    }
}

void add_dependency(struct cell *parent, struct cell *dependency)
{
    struct cell_node *node = malloc(sizeof(struct cell_node));
    if (!node) {
        fprintf(stderr, "DEBUG: malloc for cell_node failed.\n");
        return;
    }
    if (!parent->dependencies) {
        parent->dependencies = node;
    }
    else {
        struct cell_node *current = parent->dependencies;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
    
    node->cell = dependency;
    node->next = NULL;
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
    if (!node) {
        fprintf(stderr, "DEBUG: malloc for cell_node failed.\n");
        return -1;
    }
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
    node->id = next_callback_id++;
    node->next = NULL;
    return node->id;
}

void remove_callback(struct cell *c, callback_id id)
{
    if (!c || !c->cb) return;
    
    struct cb_node *current = c->cb;
    struct cb_node *prev = NULL;
    
    while (current->next && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (!current || current->id != id) return;
    
    if (prev) {
        prev->next = current->next;
    }
    else {
        c->cb = current->next;
    }
    
    free(current);
    return;
}