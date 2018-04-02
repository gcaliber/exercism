#include "isogram.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare_chars (const void *a, const void *b) {
   return ( *(char*)a - *(char*)b );
}

bool is_isogram(const char* phrase) {
    int n = strlen(phrase);

    if (n == 1) return true;
    
    char* buffer = malloc(n * sizeof(phrase[0]) + 1);
    
    for (int i = 0; i < n + 1; i++) {
        buffer[i] = tolower(phrase[i]);
    }

    qsort(buffer, (size_t) n, sizeof(phrase[0]), compare_chars);
    
    int i, j;
    for (i = 1; i < n; i++) {
        j = i - 1;
        if (buffer[i] == '-' || buffer[i] == ' ')  continue;
        if (buffer[i] == buffer[j]) {
            free(buffer);
            return false;
        }
    }
    free(buffer);
    return true;
}