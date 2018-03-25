#include "phone_number.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NANP_SIZE 15
#define INVALID_NUMBER "0000000000"

bool valid(char c) {
    if (isdigit(c) || isspace(c)) return true;
    if (c == '(' || c == ')' || c == '-' || c == '.') return true;
    return false;
}

char *phone_number_clean(const char *input)
{
    char *result = calloc(NANP_SIZE, sizeof(char));

    int insert = 0;
    for (int i = 0; input[i]; i++) {
        if (!valid(input[i])) {
            strcpy(result, INVALID_NUMBER);
            return result;
        }
        if (!isdigit(input[i])) continue;

        result[insert++] = input[i];
    }
    
    if (strlen(result) == 11 && result[0] == '1') {
        char *tmp = malloc(NANP_SIZE * sizeof(char));
        strcpy(tmp, &result[1]);
        free(result);
        return tmp;
    }
    
    if (strlen(result) != 10) {
        strcpy(result, INVALID_NUMBER);
    }
    return result;
}

char *phone_number_get_area_code(const char *input)
{
    char *result = phone_number_clean(input);
    result[3] = '\0';
    return result;
}

char *phone_number_format(const char *input)
{
    char *result = phone_number_clean(input);
    
    strncpy(&result[10], &result[6], 4);
    strncpy(&result[6], &result[3], 3);
    char temp[4];
    strncpy(temp, result, 3);
    strncpy(&result[1], temp, 3);
    
    result[0] = '(';
    result[4] = ')';
    result[5] = ' ';
    result[9] = '-';
    return result;
}