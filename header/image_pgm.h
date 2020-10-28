#ifndef IMAGE_PGM_H
#define IMAGE_PGM_H

#include <stdlib.h>
#include <stdio.h>

struct image_pgm {
    char format[3];     
    int height, width;  
    int max_val;        
    int ** image;       
};

typedef struct image_pgm* PGM;

PGM initialiser_structure_image_pgm(char*, int, int, int); 
int** allocate_matrix(int, int); 
void deallocate_matrix(int**, int); 
void print_image_pgm(PGM); 

#endif
