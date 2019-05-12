#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ll_data_t;

typedef struct list_item {
    ll_data_t data;
    struct list_item *prev;
    struct list_item *next;
} list_item;

list_item **new_list();

void delete_list(list_item **list);

bool is_list_empty(list_item **list);

list_item *push(list_item **list, ll_data_t data);

ll_data_t pop(list_item **list);

list_item *unshift(list_item **list, ll_data_t data);

ll_data_t shift(list_item **list);

#endif
