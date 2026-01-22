#include "galdera.h"
#include "ebentoak.h"
#include "funtzioak.h"
#include "graphics.h"
#include "imagen.h"
#include "lehenMaila.h"
#include "soinua.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int galdera(Galderat g, SDL_Renderer *gRenderer, int running)
{
    srand(time(NULL));
    int i = rand() % 49;
    SDL_Event evento;
    int fondogaldera = irudiaKargatu("./img/galdera.bmp");
    while (running > -1)
    {
        irudiaMugitu(fondogaldera, 0, 0);
        irudiakMarraztu();
        textuaIdatzi(530, 100, g.galdera[i]);
        textuaIdatzi(575, 360, g.lehenerantzuna[i]);
        textuaIdatzi(575, 490, g.bigarrenerantzuna[i]);
        textuaIdatzi(575, 620, g.hirugarrenerantzuna[i]);
        textuaGaitu();
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = evento.button.x;
                int mouseY = evento.button.y;
                if (kolisioa(280, 980, 315, 415, mouseX, mouseY) == 1)
                {
                    if (1 == g.zuzena[i])
                    {
                        irudiaKendu(fondogaldera);
                        return running;
                        break;
                    }
                    else
                    {
                        irudiaKendu(fondogaldera);
                        return -2;
                        break;
                    }
                }

                if (kolisioa(280, 980, 440, 545, mouseX, mouseY) == 1)
                {
                    if (2 == g.zuzena[i])
                    {
                        irudiaKendu(fondogaldera);
                        return running;
                        break;
                    }
                    else
                    {
                        irudiaKendu(fondogaldera);
                        return -2;
                        break;
                    }
                }

                if (kolisioa(280, 980, 575, 680, mouseX, mouseY) == 1)
                {
                    if (3 == g.zuzena[i])
                    {
                        irudiaKendu(fondogaldera);
                        return running;
                        break;
                    }
                    else
                    {
                        irudiaKendu(fondogaldera);
                        return -2;
                        break;
                    }
                }
            }
            if (evento.type == SDL_KEYDOWN)
            {
                if (evento.key.keysym.sym == SDLK_ESCAPE)
                {

                    irudiaKendu(fondogaldera);
                    return -2;
                    break;
                }
            }

            if (evento.type == SDL_QUIT)
            {
                return -3;
                break;
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    irudiaKendu(fondogaldera);
    return -2;
}

void datubaseahasieratu(Galderat *g)
{
    FILE *archivo;
    char linea[256];
    int lineaActual = 0;
    int i = 0;

    archivo = fopen("img/galderak.txt", "r");
    if (archivo == NULL)
    {
        printf("Ezin izan da fitxategia ireki\n");
        return;
    }

    while (fgets(linea, sizeof(linea), archivo))
    {
        lineaActual++;

        if (lineaActual == 6 * i + 1)
        {
            strcpy(g->galdera[i], linea);
        }
        else if (lineaActual == 6 * i + 2)
        {
            strcpy(g->lehenerantzuna[i], linea);
        }
        else if (lineaActual == 6 * i + 3)
        {
            strcpy(g->bigarrenerantzuna[i], linea);
        }
        else if (lineaActual == 6 * i + 4)
        {
            strcpy(g->hirugarrenerantzuna[i], linea);
        }
        else if (lineaActual == 6 * i + 5)
        {
            g->zuzena[i] = atoi(linea);
            i++; // pasamos a la siguiente pregunta
        }
    }

    fclose(archivo);
}
