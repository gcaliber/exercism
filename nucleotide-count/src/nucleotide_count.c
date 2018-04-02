#include "nucleotide_count.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * count(const char *dna)
{
    int A = 0, C = 0, G = 0, T = 0;
    char *result = malloc(sizeof(char) * 50);
    
    for (size_t i = 0; i < strlen(dna); i++) {
        switch(dna[i]) {
            case 'A':
            A++;
            break;
            
            case 'C':
            C++;
            break;
            
            case 'G': 
            G++;
            break;
            
            case 'T':
            T++;
            break;
            
            default:
            return strcpy(result, "");
        }
    }
    sprintf(result, "A:%d C:%d G:%d T:%d", A, C, G, T);
    return result;
}