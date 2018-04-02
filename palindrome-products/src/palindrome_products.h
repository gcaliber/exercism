#ifndef PALINDROME_PRODUCTS_H
#define PALINDROME_PRODUCTS_H

#define MAX_ERROR_LENGTH 255

typedef struct factor {
    int factor_a;
    int factor_b;
    struct factor *next;
} factor_t;

typedef struct {
    int smallest;
    int largest;
    factor_t *factors_sm;
    factor_t *factors_lg;
    char error[MAX_ERROR_LENGTH];
} product_t;

product_t *get_palindrome_product(int min, int max);
void free_product(product_t *product);

#endif