#include "acronym.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *abbreviate(const char *phrase) {
    if (!phrase || !phrase[0]) return NULL;

    char *abbr = malloc(10);

    abbr[0] = toupper(phrase[0]);
    int abbr_i = 1, i = 1;
    while (phrase[i]) {
        if (phrase[i] == ' ' || phrase[i] == '-') {
            abbr[abbr_i++] = toupper(phrase[i + 1]);
        }
        i++;
    }
    abbr[abbr_i] = '\0';
    return abbr;
}