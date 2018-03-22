#include "series.h"
#include <stdlib.h>
#include <string.h>

series_results_t series(char *input_text, unsigned int substring_length)
{
    series_results_t result;
    if (substring_length > 0) {
        result.substring_count = 1 + strlen(input_text) - substring_length;
    }
    else {
        result.substring_count = 0;
    }
    result.substring = malloc(result.substring_count * sizeof(char *));
    
    for (int i = 0; i < (int) result.substring_count; i++) {
        result.substring[i] = calloc(substring_length + 1, sizeof(char));
        strncpy(result.substring[i], &input_text[i], substring_length);
    }
    return result;
}
