#include "etl.h"
#include <stdlib.h>
#include <ctype.h>

#define MAX_OUTPUT_LENGTH 26

static int compare_new_map (const void *a, const void *b)
{
   return (*(new_map*)a).key - (*(new_map*)b).key;
}

int convert(legacy_map *input, int input_len, new_map **output)
{
    *output = malloc(sizeof(new_map) * MAX_OUTPUT_LENGTH);
    int output_len = 0;
    for (int map_i = 0; map_i < input_len; map_i++) {
        for (int char_i = 0; input[map_i].letters[char_i]; char_i++) {
            (*output)[output_len].key   = tolower(input[map_i].letters[char_i]);
            (*output)[output_len].value = input[map_i].score;
            output_len++;
        }
    }
    
    qsort(*output, output_len, sizeof(new_map), compare_new_map);
    
    return output_len;
}