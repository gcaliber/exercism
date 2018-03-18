#include "binary_search.h"
#include <stdlib.h>

int * binary_search(int n, int *arr, int length)
{
    if (!arr || length == 0) return NULL;

    int mid = length / 2;
    if (arr[mid] == n) return &arr[mid];
    if (length == 1)   return NULL;
    if (arr[mid] > n) {
        return binary_search(n, arr, mid);
    }
    else {
        return binary_search(n, &arr[mid + 1], length - (mid + 1));
    }
}