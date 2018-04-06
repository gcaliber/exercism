#include "luhn.h"
#include <string.h>
#include <ctype.h>

bool luhn(const char *input)
{
    int length = strlen(input);
    if (length <= 1) return false;
    
    int digit_count = 0;
    int sum = 0;
    for (int i = length - 2; i >= 0; i--) {
        if (input[i] == ' ')    continue;
        if (!isdigit(input[i])) return false;
        
        digit_count++;
        int digit = input[i] - '0';
        if (digit_count % 2 != 0) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
    }
    if (sum == 0 && digit_count <= 1) return false;
    
    int check_digit = input[length - 1] - '0';
    return (sum + check_digit) % 10 == 0;
}