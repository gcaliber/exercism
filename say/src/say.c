#include "say.h"
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_BUFFER (sizeof(char) * 200)
#define MAX_INPUT_LENGTH 13
#define MAX_PERIODS 4
#define PERIOD_SIZE 3

bool say_nonzero_digit(char *buffer, char digit)
{
    switch (digit) {
        case '1':
            strcat(buffer, "one");
            break;
        case '2':
            strcat(buffer, "two");
            break;
        case '3':
            strcat(buffer, "three");
            break;
        case '4':
            strcat(buffer, "four");
            break;
        case '5':
            strcat(buffer, "five");
            break;
        case '6':
            strcat(buffer, "six");
            break;
        case '7':
            strcat(buffer, "seven");
            break;
        case '8':
            strcat(buffer, "eight");
            break;
        case '9':
            strcat(buffer, "nine");
            break;
        case '0':
            return false;
    }
    return true;
}

void say_teens(char *buffer, char digit)
{
    switch (digit) {
        case '0':
            strcat(buffer, "ten");
            break;
        case '1':
            strcat(buffer, "elven");
            break;
        case '2':
            strcat(buffer, "twelve");
            break;
        case '3':
            strcat(buffer, "thirteen");
            break;
        case '4':
            strcat(buffer, "fourteen");
            break;
        case '5':
            strcat(buffer, "fifteen");
            break;
        case '6':
            strcat(buffer, "sixteen");
            break;
        case '7':
            strcat(buffer, "seventeen");
            break;
        case '8':
            strcat(buffer, "eighteen");
            break;
        case '9':
            strcat(buffer, "nineteen");
    }
}

void say_period(char *buffer, char *period)
{
    if (say_nonzero_digit(buffer, period[0])) {
        strcat(buffer, " hundred ");
    }
    
    bool teen = false;
    switch (period[1]) {
        case '1':
            say_teens(buffer, period[2]);
            teen = true;
            break;
        case '2':
            strcat(buffer, "twenty");
            break;
        case '3':
            strcat(buffer, "thirty");
            break;
        case '4':
            strcat(buffer, "forty");
            break;
        case '5':
            strcat(buffer, "fifty");
            break;
        case '6':
            strcat(buffer, "sixty");
            break;
        case '7':
            strcat(buffer, "seventy");
            break;
        case '8':
            strcat(buffer, "eighty");
            break;
        case '9':
            strcat(buffer, "ninety");
            break;
    }
    
    if (!teen && period[2] != '0' && !(period[0] == '0' && period[1] == '0')) {
        strcat(buffer, "-");
    }
    
    if (!teen) say_nonzero_digit(buffer, period[2]);
}

int say(int64_t n, char **ptr)
{
    char *buffer = calloc(MAX_BUFFER, sizeof(char));
    
    if (n < 0 || n > 999999999999) {
        fprintf(stderr, "Invalid input: %" PRId64 "    Valid inputs are [0..999999999999].\n", n);
        return -1;
    }
    
    if (n == 0) {
        strcpy(buffer, "zero");
        *ptr = buffer;
        return 0;
    }
    
    char n_str[MAX_INPUT_LENGTH];
    sprintf(n_str, "%" PRId64, n);

    char *period[MAX_PERIODS];
    int length = strlen(n_str);
    int first_period_size = length % PERIOD_SIZE;
    
    int period_count = length / PERIOD_SIZE;
    if (first_period_size > 0) period_count++;
    
    if (!first_period_size) first_period_size = 3;
    
    int first_period = MAX_PERIODS - period_count;
    
    for (int i = 0; i < first_period; i++) {
        period[i] = NULL;
    }
    
    period[first_period] = calloc((PERIOD_SIZE + 1), sizeof(char));
    
    period[first_period][0] = '0';
    period[first_period][1] = '0';
    
    strncpy(period[first_period] + 3 - first_period_size, &n_str[0], first_period_size);
    
    for (int i = first_period_size, p = first_period + 1; i < length; i += 3, p++) {
        period[p] = calloc((PERIOD_SIZE + 1), sizeof(char));
        strncpy(period[p], &n_str[i], PERIOD_SIZE);
    }
    
    for (int i = 0; i < MAX_PERIODS; i++) {
        if (period[i]) {
            say_period(buffer, period[i]);
            switch (i) {
                case BILLION:
                    strcat(buffer, " billion ");
                    break;
                case MILLION:
                    if (strcmp(period[i], "000")) {
                        strcat(buffer, " million ");
                    }
                    break;
                case THOUSAND:
                    if (strcmp(period[i], "000")) {
                        strcat(buffer, " thousand ");
                    }
            }
        }
    }
    
    if (buffer[strlen(buffer) - 1] == ' ') {
        buffer[strlen(buffer) - 1] = '\0';
    }
    
    for (int i = 0; i < MAX_PERIODS; i++) {
        if (period[i]) free(period[i]);
    }
    
    *ptr = buffer;
    return 0;
}