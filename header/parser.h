#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "image_pgm.h"

#define MAX_BUFFER_LEN 4096
#define LO(num)	((num) & 0x000000FF)

PGM parser_header(FILE*, const char *);
void lire_donnees_image_pgm(FILE *, PGM);
void write_into_file(FILE *, PGM);

#endif
