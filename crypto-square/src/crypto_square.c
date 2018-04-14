#include "crypto_square.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * ciphertext(const char *input)
{
    char *stripped = calloc(strlen(input) + 1, sizeof(char));
    size_t char_count = 0;
    for (size_t i = 0; input[i]; i++) {
        if (isalnum(input[i])) {
            stripped[char_count++] = tolower(input[i]);
        }
    }
    
    size_t cols = (int) ceil(sqrt(char_count));
    size_t rows = cols - 1;
    if (cols * rows < char_count) rows++;
    
    char *result = calloc(cols * rows + 1, sizeof(char));
    size_t k = 0;
    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < rows; j++) {
            if (i + j * cols < char_count) {
                result[k++] = stripped[i + j * cols];
            }
            else {
                result[k++] = ' ';
            }
        }
        if (i != cols - 1) result[k++] = ' ';
    }
    
    free(stripped);
    return result;
}