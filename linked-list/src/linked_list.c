#include "linked_list.h"

list_item **new_list()
{
    list_item **list = malloc(2 * sizeof(list_item));
    list[0] = NULL;
    list[1] = NULL;
    return list;
}

void delete_list(list_item **list)
{
    list_item *node = *list;
    while (node) {
        list_item *temp = node;
        free(temp);
        node = node->next;
    }
}

bool is_list_empty(list_item **list)
{
    return !list || !list[0];
}

list_item *push(list_item **list, ll_data_t data)
{
    if (!list) return NULL;
    list_item *tail = list[1];
    list_item *new_node = malloc(sizeof(list_item));
    if (is_list_empty(list)) {
        list[0] = new_node;
    }
    else {
        tail->next = new_node;
    }
    new_node->prev = tail;
    new_node->next = NULL;
    list[1] = new_node;
    new_node->data = data;
    return new_node;
}

ll_data_t pop(list_item **list)
{
    if (list[0] == list[1]) {
        list[0] = NULL;
    }
    list_item *temp = list[1];
    ll_data_t data = temp->data;
    list[1] = temp->prev;
    if (list[1]) list[1]->next = NULL;
    free(temp);
    return data;
}

list_item *unshift(list_item **list, ll_data_t data)
{
    if (!list) return NULL;
    list_item *head = list[0];
    list_item *new_node = malloc(sizeof(list_item));
    if (is_list_empty(list)) {
        list[1] = new_node;
    }
    else {
        head->prev = new_node;
    }
    new_node->prev = NULL;
    new_node->next = head;
    list[0] = new_node;
    new_node->data = data;
    return new_node;
}

ll_data_t shift(list_item **list)
{
    if (list[0] == list[1]) {
        list[1] = NULL;
    }
    list_item *temp = list[0];
    ll_data_t data = temp->data;
    list[0] = temp->next;
    if (list[0]) list[0]->prev = NULL;
    free(temp);
    return data;
}



