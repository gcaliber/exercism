#ifndef ATBASH_CIPHER_H
#define ATBASH_CIPHER_H

static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

char * atbash_encode(char *plain_text);
char * atbash_decode(char *cipher_text);

#endif