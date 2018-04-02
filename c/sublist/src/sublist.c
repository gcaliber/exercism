#include "sublist.h"

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count)
{
    for (int i = 0; i < (int) list_to_compare_element_count; i++) {
        int comp_element = list_to_compare[i];
        for (int j = 0; j < (int) base_list_element_count; j++) {
            int base_element = base_list[j];
            if (comp_element == base_element) {
                for (int k = 1; i + k < list_to_compare_element_count && j + k < base_list_element_count; k++) {
                    if (list_to_compare[i + k] != base_list[j + k]) break;
                }
                
                // FIX: logic here is certainly not right
                if (k == list_to_compare_element_count && k == base_list_element_count) {
                    return EQUAL;
                }
                else if (k == list_to_compare_element_count) {
                    return SUBLIST;
                }
                else if (k == base_list_element_count) {
                    return SUPERLIST;
                }
                else {
                    return UNEQUAL;
                }
            }
        }
    }
}