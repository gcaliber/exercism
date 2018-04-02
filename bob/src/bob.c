#include "bob.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_all_whitespace(const char *phrase);
bool is_yelling(const char *phrase);
bool is_question(const char *phrase);

char * hey_bob(const char *phrase)
{
    if (is_all_whitespace(phrase)) 
        return FINE;
    
    bool yelling  = is_yelling(phrase);
    bool question = is_question(phrase);
    
    if (yelling && question) 
        return CALM_DOWN;
    if (yelling) 
        return CHILL_OUT;
    if (question) 
        return SURE;
    return WHATEVER;
}

bool is_all_whitespace(const char *phrase)
{
    for (size_t i = 0; i < strlen(phrase); i++) {
        if (!isspace(phrase[i])) return false;
    }
    return true;
}

bool is_yelling(const char *phrase)
{
    bool has_alpha = false;
    for (size_t i = 0; i < strlen(phrase); i++) {
        if (isalpha(phrase[i])) {
            if (!isupper(phrase[i])) return false;
            has_alpha = true;
        }
    }
    return has_alpha;
}

bool is_question(const char *phrase)
{
    size_t i = strlen(phrase) - 1;
    while(isspace(phrase[i])) {
        i--;
    }
    return phrase[i] == '?';
}