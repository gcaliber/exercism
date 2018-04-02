#include "sublist.h"

#include <stdio.h>

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count)
{
    if (!list_to_compare && !base_list) return EQUAL;
    if (!list_to_compare)               return SUBLIST;
    if (!base_list)                     return SUPERLIST;
    
    for (int i = 0; i < (int) list_to_compare_element_count; i++) {
        int comp_element = list_to_compare[i];
        for (int j = 0; j < (int) base_list_element_count; j++) {
            int base_element = base_list[j];
            if (comp_element == base_element) {
                size_t match_count;
                for (match_count = 1;
                     i + match_count < list_to_compare_element_count && j + match_count < base_list_element_count;
                     match_count++)
                {
                    if (list_to_compare[i + match_count] != base_list[j + match_count]) break;
                }
                
                if (match_count == list_to_compare_element_count && match_count == base_list_element_count) {
                    return EQUAL;
                }
                else if (match_count == list_to_compare_element_count) {
                    return SUBLIST;
                }
                else if (match_count == base_list_element_count) {
                    return SUPERLIST;
                }
            }
        }
    }
    return UNEQUAL;
}