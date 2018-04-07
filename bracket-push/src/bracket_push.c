#include "bracket_push.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

void push_bracket(node_t **head, bracket_t type) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->type = type;
    new_node->next = *head;
    *head = new_node;
}

bool pop_bracket(node_t **head, bracket_t type) {
    if (!*head) return false;
    
    node_t *node = *head;
    if (node->type == type) {
        *head = node->next;
        free(node);
        return true;
    }
    return false;
}

void free_node(node_t *node) {
    if (node) {
        free_node(node->next);
        free(node);
    }
}

bool is_paired(const char *input)
{
    if (strlen(input) == 0) return true;
    
    node_t *root = NULL;
    bool paired = true;
    for (int i = 0; input[i]; i++) {
        switch(input[i]) {
            case '[':
                push_bracket(&root, BRACKET);
                break;
            case '{':
                push_bracket(&root, BRACE);
                break;
            case '(':
                push_bracket(&root, PARENTHESES);
                break;
            case ']':
                paired = pop_bracket(&root, BRACKET);
                break;
            case '}':
                paired = pop_bracket(&root, BRACE);
                break;
            case ')':
                paired = pop_bracket(&root, PARENTHESES);
        }
        if (!paired) {
            free_node(root);
            return false;
        }
    }
    paired = root == NULL;
    free_node(root);
    return paired;
}