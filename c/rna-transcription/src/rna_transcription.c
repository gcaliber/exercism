#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna)
{
    size_t len = strlen(dna);
    char *rna = malloc(sizeof(dna[0]) * (len + 1));
    rna[len] = 0;
    
    for (size_t i = 0; i < len; i++) {
        switch(dna[i]) {
            case 'G': 
            rna[i] = 'C';
            break;
            
            case 'C':
            rna[i] = 'G';
            break;
            
            case 'T':
            rna[i] = 'A';
            break;
            
            case 'A':
            rna[i] = 'U';
            break;
            
            default:
            return NULL;
        }
    }
    
    return rna;
}