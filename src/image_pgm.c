#include <string.h>

#include "../header/image_pgm.h"

PGM initialiser_structure_image_pgm(char* format, int h, int w, int max_val){
    PGM s = malloc(sizeof(struct image_pgm)); 
    strcpy(s->format, format); 
    s->height = h; 
    s->width = w; 
    s->max_val = max_val; 
    s->image = allocate_matrix(h,w);
    return s; 
}

int** allocate_matrix(int rows, int columns) {
    int **matrix = (int**)malloc(rows*sizeof(int*)); 
    for (unsigned int row = 0; row < rows; row++)
        matrix[row] = (int*)malloc(columns*sizeof(int)); 
    return matrix; 
}

void deallocate_matrix(int** matrix, int row){
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix); 
}

void print_image_pgm(PGM s) {
    printf("%s\n%d %d\n%d\n", s->format, s->height, s->width, s->max_val);
    for(unsigned int x = 0; x < s->height; x++) {
        for(unsigned int y = 0; y < s->width; y++) {
            printf("%d ", s->image[x][y]);
        }
        printf("\n");
    }
}

