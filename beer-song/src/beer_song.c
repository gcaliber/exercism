#include "beer_song.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void verse(char *result, int v) {
    if (v == 2) {
        strcpy(result, "2 bottles of beer on the wall, 2 bottles of beer.\n"
                       "Take one down and pass it around, 1 bottle of beer on the wall.\n");
    }
    else if (v == 1) {
        strcpy(result, "1 bottle of beer on the wall, 1 bottle of beer.\n"
                       "Take it down and pass it around, no more bottles of beer on the wall.\n");
    }
    else if (v == 0) {
        strcpy(result, "No more bottles of beer on the wall, no more bottles of beer.\n"
                       "Go to the store and buy some more, 99 bottles of beer on the wall.\n");        
    }
    else {
        sprintf(result, "%d bottles of beer on the wall, %d bottles of beer.\n"
                        "Take one down and pass it around, %d bottles of beer on the wall.\n", v, v, v - 1);
    }
}

void sing(char *result, int start, int end) {
    char *temp = result;
    for (int i = start; i >= end; i--) {
        verse(temp, i);
        if (i != end) strcat(temp, "\n");
        temp = result + strlen(result);
    }
}