#include "palindrome_products.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 128

bool is_palindrome(int n)
{
    char str[MAX_DIGITS];
    sprintf(str, "%d", n);
    int length = strlen(str);
    
    for (int left = 0, right = length - 1; left < right; left++, right--) {
        if (str[left] != str[right]) return false;
    }
    return true;
}

void destroy_factor(factor_t *f)
{
    if (f) {
        destroy_factor(f->next);
        free(f);
    }
}

void add_factor(factor_t **old, int a, int b)
{
    factor_t *new_factor = malloc(sizeof(factor_t));
    new_factor->factor_a = a;
    new_factor->factor_b = b;
    new_factor->next = *old;
    *old = new_factor;
}

product_t *get_palindrome_product(int min, int max)
{
    product_t *product = malloc(sizeof(product_t));

    if (min > max) {
        sprintf(product->error, "invalid input: min is %d and max is %d", min, max);
        return product;
    }    
    
    product->smallest = max * max;
    product->largest  = 0;
    
    for (int a = min; a <= max; a++) {
        for (int b = a; b <= max; b++) {
            int p = a * b;
            if (p <= product->smallest || p >= product->largest) {
                if (is_palindrome(p)) {
                    if (p <= product->smallest) {
                        if (p < product->smallest) {
                            product->smallest = p;
                            destroy_factor(product->factors_sm);
                            product->factors_sm = NULL;
                        }
                        add_factor(&product->factors_sm, a, b);
                    }
                    
                    if (p >= product->largest) {
                        if (p > product->largest) {
                            product->largest = p;
                            destroy_factor(product->factors_lg);
                            product->factors_lg = NULL;
                        }
                        add_factor(&product->factors_lg, a, b);
                    }
                }    
            }
        }
    }
    
    if (!product->factors_sm && !product->factors_lg) {
        sprintf(product->error, "no palindrome with factors in the range %d to %d", min, max);
    }
    
    return product;
}

void free_product(product_t *product)
{
    if (product) {
        destroy_factor(product->factors_sm);
        destroy_factor(product->factors_lg);
        free(product);
    }
}