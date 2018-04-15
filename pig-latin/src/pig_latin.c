#include "pig_latin.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define VOWEL_BUFFER 2

char *translate_word(char* word)
{
    char *result = calloc(strlen(word) + VOWEL_BUFFER + 1, sizeof(char));
    
    char c = word[0];
    int consonant_count = 0;
    while (c != 'a' && c != 'e' && c != 'i' && c != 'o' &&
          (c != 'u' || (c == 'u' && word[consonant_count - 1] == 'q')) &&
          (c != 'y' || (c == 'y' && consonant_count == 0 && word[1] != 't')) &&
          (c != 'x' || (c == 'x' && consonant_count == 0 && word[1] != 'r')))
    {
        c = word[++consonant_count];
    }
    
    strcpy(result, &word[consonant_count]);
    strncat(result, word, consonant_count);
    strcat(result, "ay");
    
    return result;
}

char *translate(const char* phrase)
{
    char *result = calloc((int) (strlen(phrase) * 1.25), sizeof(char));
    
    char *tokenized = malloc((strlen(phrase) + 1) * sizeof(char));
    strcpy(tokenized, phrase);
    char *token = strtok(tokenized, " ");
   
    for (;;) {
        char *pig_latinized = translate_word(token);
        strcat(result, pig_latinized);
        free(pig_latinized);
        token = strtok(NULL, " ");
        if (!token) break;
        strcat(result, " ");
    }
    
    free(tokenized);
    return result;
}