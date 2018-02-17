#include "pangram.h"
#include <ctype.h>
#include <string.h>

bool already_seen(char c, char *seen);

bool is_pangram(const char *sentence) {
    if (!sentence) return false;

    int seen_count = 0;
    char seen[26] = {0};
    
    int i = 0;
    while (sentence[i]) {
        char c = tolower(sentence[i]);
        if (isalpha(c)) {
            if (!already_seen(c, seen)) {
                seen[seen_count++] = c;
            }
        }
        i++;
    }
    return seen_count == 26;
}

bool already_seen(char c, char *seen) {
    int i = 0;
    while (seen[i]) {
        if (c == seen[i]) return true;
        i++;
    }
    return false;
}