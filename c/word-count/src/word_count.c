#include "word_count.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool is_apostrophe(const char *text, int index);
int add_word(char *word, int n, word_count_word_t * words);
int find_word(char *word, int n, word_count_word_t * words);

int word_count(const char *input_text, word_count_word_t * words) {
    memset(words, 0, MAX_WORDS * sizeof(*words));
    char buffer[MAX_WORD_LENGTH];
    int i = 0, bi = 0, unique_word_count = 0;

    while (input_text[i]) {
        if (bi > MAX_WORD_LENGTH) return EXCESSIVE_LENGTH_WORD;
        if (isalnum(input_text[i]) || is_apostrophe(input_text, i)) {
            buffer[bi++] = tolower(input_text[i]);
        } else if (*buffer) {
            buffer[bi] = '\0';
            if (unique_word_count >= MAX_WORDS) return EXCESSIVE_NUMBER_OF_WORDS;
            unique_word_count += add_word(buffer, unique_word_count, words);    
            memset(buffer, 0, sizeof(buffer));
            bi = 0;
        }
        i++;
    }
    if (bi) {
        buffer[bi] = '\0';
        unique_word_count += add_word(buffer, unique_word_count, words);
    }
    return unique_word_count;
}

bool is_apostrophe(const char *text, int index) {
    if (text[index] != '\'') return false;
    if (index == 0 || index == (int) strlen(text) - 1) return false;
    if (!isalpha(text[index - 1]) || !isalpha(text[index + 1])) return false;
    return true;
}

int add_word(char *word, int n, word_count_word_t * words) {
    int index = find_word(word, n, words);
    if (index == n) {
        strncpy(words[n].text, word, MAX_WORD_LENGTH);
        words[n].count = 1;
        return 1;
    } else {
        words[index].count++;
        return 0;
    }
}

int find_word(char *word, int n, word_count_word_t * words) {
    if (n == 0) return 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(word, words[i].text) == 0) {
            return i;
        }
    }
    return n;
}