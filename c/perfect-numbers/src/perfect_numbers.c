#include "perfect_numbers.h"
#include <stdlib.h>

#include <stdio.h>

typedef struct {
    int *arr;
    int count;
} factors_t;

static int compare_int (const void *a, const void *b)
{
   return *(int*)a - *(int*)b;
}

static factors_t factorize(int n)
{
    int max_factors = n / 2;
    if (max_factors < 2) max_factors = 2; 
    factors_t factors;
    factors.arr = malloc(sizeof(int) * max_factors);
    factors.count = 0;
    
    for (int i = 1; i < max_factors; i++) {
        if (n % i == 0) {
            if (factors.count > 0 && factors.arr[factors.count - 1] == i) break;
            factors.arr[factors.count++] = i;
            if (n / i != i) {
                factors.arr[factors.count++] = n / i;
            }
        }
    }
    qsort(factors.arr, factors.count, sizeof(int), compare_int);

    return factors;
}

static int aliquot_sum(int n) {
    factors_t factors = factorize(n);
    
    int sum = 0;
    for (int i = 0; i < factors.count - 1; i++) {
        sum += factors.arr[i];
    }
    
    free(factors.arr);
    return sum;
}

kind classify_number(int n)
{
    if (n < 1) return ERROR;
    
    int aliquot_sum_of_n = aliquot_sum(n);
    if (aliquot_sum_of_n == n) return PERFECT_NUMBER;
    if (aliquot_sum_of_n > n)  return ABUNDANT_NUMBER;
    if (aliquot_sum_of_n < n)  return DEFICIENT_NUMBER;
    return ERROR;
}