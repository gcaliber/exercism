#include "largest_series_product.h"
#include <string.h>
#include <ctype.h>

int64_t series_product(const char *series, int length)
{
    int64_t product = 1;
    for (int i = 0; i < length; i++) {
        if (!isdigit(series[i])) return -1;
        product *= series[i] - '0';
    }
    return product;
}

int64_t largest_series_product(const char *series, size_t length)
{
    int full_length = strlen(series);
    if ((int) length > full_length) return -1;
    
    int64_t largest = 0;
    for (int start = 0; start <= (int) (strlen(series) - length); start++) {
        int64_t product = series_product(&series[start], length);
        if (product == -1) return -1;
        if (product > largest) largest = product;
    }
    return largest;
}