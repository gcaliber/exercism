#include "anagram.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int compare_chars (const void *a, const void *b) {
   return ( *(char*)a - *(char*)b );
}

void str_tolower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void anagrams_for(const char *word, struct candidates *candidates)
{
    printf("\n\n     Word: %s\n", word);
    for (int i = 0; i < (int)candidates->count; i++) {
        printf("Candidate: %s\n", candidates->candidate[i].candidate);
    }
    printf("\n");
    
    size_t length = strlen(word);
    
    for (int i = 0; i < (int)candidates->count; i++) {
        struct candidate *c = &candidates->candidate[i];
        if (strlen(c->candidate) != length) {
            c->is_anagram = NOT_ANAGRAM;
        }
    }
    
    char word_lower[MAX_STR_LEN];
    strcpy(word_lower, word);
    str_tolower(word_lower);
    
    char word_sorted[MAX_STR_LEN];
    strcpy(word_sorted, word_lower);
    qsort(word_sorted, length, sizeof(char), compare_chars);
    
    printf("Sorted Word: %s\n", word_sorted);
    
    for (int i = 0; i < (int)candidates->count; i++) {
        struct candidate *c = &candidates->candidate[i];
        if (c->is_anagram == UNCHECKED) {
            char candidate_lower[MAX_STR_LEN];
            strcpy(candidate_lower, c->candidate);
            str_tolower(candidate_lower);
            
            char candidate_sorted[MAX_STR_LEN];
            strcpy(candidate_sorted, candidate_lower);
            qsort(candidate_sorted, length, sizeof(char), compare_chars);

            printf("Sorted Candidate: %s\n", candidate_sorted);
            if (strcmp(word_sorted, candidate_sorted) == 0 && strcmp(word_lower, candidate_lower) != 0) {
                c->is_anagram = IS_ANAGRAM;
            }
            else {
                c->is_anagram = NOT_ANAGRAM;
            }
        }
    }
}