#include <SDL2/SDL.h>
#ifndef GALDERAK_H
#define GALDERAK_H

typedef struct
{
    char galdera[50][256];
    char lehenerantzuna[50][256];
    char bigarrenerantzuna[50][256];
    char hirugarrenerantzuna[50][256];
    int zuzena[50];
} Galderat;

int galdera(Galderat g, SDL_Renderer *gRenderer, int running);
void datubaseahasieratu(Galderat *g);
#endif
