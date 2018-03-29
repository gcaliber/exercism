#include "pascals_triangle.h"

#define PTR_SIZE sizeof(void *)

size_t **create_triangle(int rows)
{
    if (rows < 0) return NULL;
 
    size_t **triangle;   
    if (rows == 0) {
        triangle = malloc(PTR_SIZE);
        triangle[0] = malloc(sizeof(size_t));
        triangle[0][0] = 0;
        return triangle;
    } 
    else { 
        triangle = malloc(PTR_SIZE * rows);
    }
    
    for (int row = 0; row < rows; row++) {
        triangle[row] = malloc(sizeof(size_t) * rows);
        for (int pos = 0; pos < rows; pos++) {
            if (pos == 0 || pos == row) {
                triangle[row][pos] = 1;
            }
            else if (pos > row) {
                triangle[row][pos] = 0;
            }
            else {
                triangle[row][pos] = triangle[row - 1][pos - 1] + triangle[row - 1][pos];
            }
        }
    }
    return triangle;
}

void free_triangle(size_t **triangle, int rows)
{
    if (!triangle || rows < 0) return;
    
    if (!rows) rows = 1;
    for (int row = 0; row < rows; row++) {
        free(triangle[row]);
    }
    free(triangle);
}