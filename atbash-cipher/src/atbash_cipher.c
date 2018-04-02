#include "atbash_cipher.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CIPHER_SPACING 5

char * atbash_encode(char *plain_text)
{
    int len = strlen(plain_text);
    char *cipher_text = malloc(len + len / 5 + 1);
    int index = 0;
    int count = 0;
    while (plain_text[index]) {
        char c = tolower(plain_text[index]);
        if (isalnum(c)) {
            char s[2] = { '\0' };
            if (isalpha(c)) {
                int cipher_index = 12 + (13 - (c - 'a'));
                s[0] = alphabet[cipher_index];
            }
            else if (isdigit(c)) {
                s[0] = c;
            }
            strcat(cipher_text, s);
            count++;
            if (count % CIPHER_SPACING == 0 && index) {
                strcat(cipher_text, " ");
            }
        }
        index++;
    }

    int i = strlen(cipher_text) - 1;
    while (isspace(cipher_text[i])) {
        cipher_text[i--] = '\0';
    }

    return cipher_text;
}

char * atbash_decode(char *cipher_text)
{
    char *plain_text = malloc(strlen(cipher_text));
    int index = 0;
    while (cipher_text[index]) {
        char c = cipher_text[index];
        if (isalnum(c)) {
            char s[2] = { '\0' };
            if (isalpha(c)) {
                int plain_index = 12 + (13 - (c - 'a'));
                s[0] = alphabet[plain_index];
            }
            else {
                s[0] = c;
            }
            strcat(plain_text, s);
        }
        index++;
    }
    return plain_text;
}