#ifndef TTYIN_H
#define TTYIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(FILE *fp, int pagesize);
FILE *efopen(char *file, char *mode);
char ttyin();

#endif