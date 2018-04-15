#include "minesweeper.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

void increase_mine_count(char **field, int row, int col, int rows, int cols)
{
    int r_end = row + 1;
    int c_end = col + 1;
    if (r_end >= rows) r_end = row;
    if (c_end >= cols) c_end = col;
    
    for (int r = row - 1; r <= r_end; r++) {
        for (int c = col - 1; c <= c_end; c++) {
            if (c >= 0 && r >= 0) {
                if (field[r][c] == '*') 
                    continue;
                else if (field[r][c] == ' ')
                    field[r][c] = '1';
                else 
                    field[r][c]++;
            }
        }
    }
}

char ** annotate(const char **minefield, int rows)
{
    if (!minefield) return NULL;
    
    int cols = strlen(minefield[0]);
    char **annotated_field = malloc(rows * sizeof(char *));
    
    for (int i = 0; i < rows; i++) {
        annotated_field[i] = malloc(cols * sizeof(char));
        strcpy(annotated_field[i], minefield[i]);
    }
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (annotated_field[row][col] == '*') {
                increase_mine_count(annotated_field, row, col, rows, cols);
            }
        }
    }
    
    return annotated_field;
}