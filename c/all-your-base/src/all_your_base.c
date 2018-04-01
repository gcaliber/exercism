#include "all_your_base.h"

#include <stdio.h>

int pow_int(int16_t n, int p) {
    if (p == 0) return 1;
    if (p == 1) return n;
    return n * pow_int(n, p - 1);
}

size_t rebase(int8_t *digits, int16_t input_base, int16_t output_base, size_t input_length)
{
    if (!digits[0] || input_base < 2 || output_base < 2) return 0;
    
    int8_t buffer[DIGITS_ARRAY_SIZE];
    size_t buffer_size = 0;
    
    int decimal = 0;
    for(int i = 0; i < (int) input_length; i++) {
        int8_t digit = digits[i];
        if (digit < 0 || digit > input_base - 1) return 0;
        decimal += (int) digit * pow_int(input_base, input_length - 1 - i);
    }

    int p = 0;
    while(pow_int(output_base, p) <= decimal) p++;
    p--;
    
    while (p >= 0) {
        int place_value = pow_int(output_base, p);
        int8_t digit = (int8_t) (decimal / place_value);
        int digit_value = digit * place_value;
        buffer[buffer_size++] = digit;
        decimal -= digit_value;
        p--;
    }
    
    for (int i = 0; i < (int) buffer_size; i++) {
        digits[i] = buffer[i];
    }
    return buffer_size;
}