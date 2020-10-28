#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "header/image_pgm.h"
#include "header/transforms.h"
#include "header/parser.h"

void filtrer(PGM pgm, void(*filtre)(PGM pgm), const char* output_img_path){
    const char* img_rel_path_ecriture = output_img_path;
    FILE *_file_pointer_ecriture = fopen(img_rel_path_ecriture, "wb");
    
    filtre(pgm); 
    write_into_file(_file_pointer_ecriture, pgm); 
    free(pgm);
}

int main(int argc, char* argv[]) {
    const char* img_rel_path_lecture = "img_pgm_docs/lena.pgm";
    FILE *_file_pointer_lecture = fopen(img_rel_path_lecture, "rb");

    PGM image_pgm = parser_header(_file_pointer_lecture, img_rel_path_lecture); 
    filtrer(image_pgm, negatif, "img_out/negatif.pgm"); 

    return 0;
}
