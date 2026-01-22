#include "ebentoak.h"
#include "funtzioak.h"
#include "galdera.h"
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

void GameOver(SDL_Renderer *gRenderer, int running)
{
    char points[10];
    snprintf(points, sizeof(points), "%d", running);
    SDL_Event evento;
    int fondoOver = irudiaKargatu("./img/FondoGameover.bmp");
    int irten = 0;
    irudiaMugitu(fondoOver, 0, 0);
    while (irten == 0)
    {
        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&evento))
        {

            if (evento.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = evento.button.x;
                int mouseY = evento.button.y;
                if (kolisioa(460, 800, 560, 640, mouseX, mouseY) == 1)
                {
                    irten = 1;
                }
            }
            if (evento.type == SDL_KEYDOWN)
            {
                if (evento.key.keysym.sym == SDLK_ESCAPE)
                {
                    irten = 1;
                }
            }

            if (evento.type == SDL_QUIT)
            {
                irten = 1;
                sgItxi();
            }
        }
        irudiakMarraztu();
        textuaIdatzi(280, 410, points);
        textuaGaitu();
        SDL_RenderPresent(gRenderer);
    }
    irudiaKendu(fondoOver);
}
