#include "allergies.h"
#include <stdlib.h>

void get_allergens(int score, allergen_list_t *list)
{
    list->allergens = malloc(sizeof(allergen_t) * ALLERGEN_COUNT);
    
    list->count = 0;
    int allergen = 7;
    score = score % 256;
    while (score) {
        int allergen_score = 1 << allergen;
        if (allergen_score <= score) {
            score -= allergen_score;
            list->allergens[list->count++] = allergen;
        }
        allergen--;
    }
}

bool is_allergic_to(allergen_t allergen, int score)
{
    allergen_list_t list;
    get_allergens(score, &list);
    
    bool is_allergic = false;
    for (int i = 0; i < list.count; i++) {
        if (list.allergens[i] == allergen) {
            is_allergic = true;
            break;
        }
    }
    
    free(list.allergens);
    return is_allergic;
}