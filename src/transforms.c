#include "../header/transforms.h"

void negatif(PGM s) {
    for(int x = 0; x < s->height; x++)
        for(int y = 0; y < s->width; y++)
            s->image[x][y] = s->max_val - s->image[x][y]; 
}   

void horizontal_gradient(PGM s) {
    for(int x = 0; x < s->height-1; x++)
        for(int y = 0; y < s->width; y++)
            s->image[x][y] = s->image[x+1][y] - s->image[x][y]; 
}

void vertical_gradient(PGM s) {
    for(int x = 0; x < s->height; x++)
        for(int y = 0; y < s->width-1; y++)
            s->image[x][y] = s->image[x][y+1] - s->image[x][y]; 
}
