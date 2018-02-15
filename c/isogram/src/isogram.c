#include "isogram.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int length(const char* str);
void sort(char* arr, int n);

bool is_isogram(const char* phrase) {

    int n = length(phrase);

    if (n == 1)  return true;
    
    char* buffer = malloc(n * sizeof(phrase[0]));
    strcpy(buffer, phrase);
    sort(buffer, n);
    int i, j;
    for (i = 1; i < n; i++) {
        j = i - 1;
        if (buffer[i] == '-' || buffer[i] == ' ')  continue;
        if (tolower(buffer[i]) == tolower(buffer[j])) {
            free(buffer);
            return false;
        }
    }
    free(buffer);
    return true;
}

int length(const char* str) {
    int n = 0;
    char c = str[0];
    while (c != '\0') {
        c = str[n++];
    }
    return n;
}

void sort(char* arr, int n) {
   int i, j, value;
   for (i = 1; i < n; i++) {
       value = arr[i];
       j = i - 1;
       while (j >= 0 && arr[j] > value) {
           arr[j + 1] = arr[j];
           j = j - 1;
       }
       arr[j + 1] = value;
   }
}