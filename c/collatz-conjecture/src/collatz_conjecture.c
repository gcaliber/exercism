#include "collatz_conjecture.h"

int steps(int start)
{
    if (start < 1) return ERROR_VALUE;
    
    int n = start;
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) 
            n /= 2; 
        else 
            n = 3 * n + 1;
        steps++;
    }
    return steps;
}