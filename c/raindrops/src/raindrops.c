#include "raindrops.h"
#include <string.h>
#include <stdio.h>

void convert(char *result, int n) 
{
    if (n % 3 == 0) {
        strcat(result, "Pling");
    }
    if (n % 5 == 0) {
        strcat(result, "Plang");
    }
    if (n % 7 == 0) {
        strcat(result, "Plong");
    }
    if (strcmp(result, "") == 0) {
        sprintf(result, "%d", n);
    }
}