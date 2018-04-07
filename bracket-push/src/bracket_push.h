#ifndef BRACKET_PUSH_H
#define BRACKET_PUSH_H

#include <stdbool.h>

typedef enum {
    BRACKET,
    PARENTHESES,
    BRACE,
} bracket_t;

typedef struct bracket_stack{
    bracket_t type;
    struct bracket_stack *next;
} node_t;

bool is_paired(const char *input);

#endif