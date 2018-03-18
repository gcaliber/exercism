#include "difference_of_squares.h"

int sum_of_squares(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return n * n + sum_of_squares(n - 1);
}

int sum(int n) {
    if (n == 1) return 1;
    return n + sum(n - 1);
}

int square_of_sum(int n)
{
    if (n == 0) return 0;
    int s = sum(n);
    return s * s;
}

int difference_of_squares(int n)
{
    return square_of_sum(n) - sum_of_squares(n);
}