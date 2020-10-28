#include <string.h> 

#include "../header/parser.h"

void lire_donnees_image_pgm(FILE* _file_pointer, PGM p) {
    const int OCTETS_A_LIRE = p->max_val < 256 ? 1 : 2;
    for(int i = 0; i < p->height; ++i) {
        for(int j = 0; j < p->width; ++j) {
            if(fread(&p->image[i][j], OCTETS_A_LIRE, 1, (FILE*)_file_pointer) == 0)
                exit(1); 
        }
    }
    fclose(_file_pointer); 
}

// équivalente
void read_pgm(FILE* _file_pointer, PGM p){
    int c; 
    for(int x = 0; x < p->height; ++x){
        for(int y = 0; y < p->width; ++y){
            c = fgetc(_file_pointer);
            p->image[x][y] = c; 
        }
    }
    fclose(_file_pointer); 
}

PGM parser_header(FILE * _file_pointer, const char * source_file) {
    enum etats { INIT, MAGIC_NUMBER_FOUND, WIDTH_HEIGHT_FOUND, MAX_VAL_FOUND, ERROR };
    enum etats etat = INIT;  
    char * buffer = malloc(sizeof(char)*MAX_BUFFER_LEN);
    bool read = true;
    char* format = (char*)malloc(sizeof(char)*3); 
    int hauteur;
    int largeur;
    int valeur_max;

    _file_pointer = fopen(source_file,"r"); 

    while(read){ 
        fgets(buffer, MAX_BUFFER_LEN, (FILE*)_file_pointer);
        switch(etat) {
            case INIT:
                if(strncmp(buffer,"P",1) == 0) {
                    etat = MAGIC_NUMBER_FOUND;
                    strcpy(format, buffer); 
                }
                break;
            case MAGIC_NUMBER_FOUND:
                while(strncmp(buffer,"#",1) == 0) 
                    fgets(buffer, MAX_BUFFER_LEN, _file_pointer);
                if(sscanf(buffer,"%d %d", &largeur, &hauteur) == 2) etat = WIDTH_HEIGHT_FOUND; 
                else read = false;
                break;
            case WIDTH_HEIGHT_FOUND:
                if(sscanf(buffer,"%d", &valeur_max) == 1) {
                    if(valeur_max == 0) fprintf(stderr, "Entete PGM : une valeur max de 0 n'est pas autorisee.");
                    else etat = MAX_VAL_FOUND;
                }
                read = false;
                break;
            default:
                etat = ERROR;
                read = false;
        } 
    }
    if(etat != MAX_VAL_FOUND) {
        fprintf(stdout, "Entete PGM incorrect, evaluation terminee a l'etat %d\n", etat);
        return 0;
    }   

    PGM p = initialiser_structure_image_pgm("P5", hauteur, largeur, valeur_max);
    lire_donnees_image_pgm(_file_pointer, p); 
    fclose(_file_pointer);
    free(buffer);  

    return p; 
}

void write_into_file(FILE* _file_pointer, PGM p) {
    /*seul le format P5 pris en compte : putc() (binaire) sinon fprintf()*/
    int lo; // dépend de la MAX_VAL, seul < 256 traité. 

    fprintf(_file_pointer, "%s \n", p->format);
    fprintf(_file_pointer, "%d %d \n", p->height, p->width);
    fprintf(_file_pointer, "%d \n", p->max_val);

    for(int x = 0; x < p->height; x++){
        for(int y = 0; y < p->width; y++){
            lo = LO(p->image[x][y]); 
            fputc(lo, _file_pointer); 
        }
    }
    fclose(_file_pointer); 
    deallocate_matrix(p->image, p->width); 
}
