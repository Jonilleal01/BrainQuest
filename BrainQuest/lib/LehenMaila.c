#include "lehenMaila.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int lehenMaila(SDL_Renderer *gRenderer, int running)
{
    int sf = 0;
    int posx = 0, posy = 1000;
    int i = 0;
    char points[12];
    SDL_Event evento;
    int basura = irudiaKargatu("./img/basura4.bmp");
    int fondo = irudiaKargatu("./img/Fondo_nivel1.bmp");
    int player1 = irudiaKargatu("./img/persona1.bmp");
    int player2 = irudiaKargatu("./img/persona2.bmp");
    SDL_Rect rects[10];
    audioInit();
    loadTheMusic("./sound/level1.wav");
    playMusic();
    irudiaMugitu(player1, posx - 3, 575);
    irudiaMugitu(player2, 1300, 575);
    while (running > -1)
    {
        snprintf(points, sizeof(points), "%d", running);

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        irudiaMugitu(fondo, 0, 0);
        irudiakMarraztu();
        irudiaMugitu(fondo, 10000, 0);
        // Basura berrbiarazi
        if (posy >= 800)
        {
            posy = 100;
            erorpen(rects);
        }

        eguneratualtura(rects, sf);
        // basura
        marraztubasura(rects, basura);
        // Jokalaria
        SDL_Rect jugador = {posx, 575, 30, 30};

        // Hitboxak
        for (i = 0; i < 10; i++)
        {
            if (SDL_HasIntersection(&jugador, &rects[i]))
            {
                GarbituMaila1(basura, fondo, player1, player2);
                audioTerminate();
                return running;
                break;
            }
        }

        while (SDL_PollEvent(&evento))
        {

            if (evento.type == SDL_KEYDOWN)
            {
                if (evento.key.keysym.sym == SDLK_LEFT)
                {
                    posx -= 10;
                    irudiaMugitu(player1, posx - 3, 575);
                    irudiaMugitu(player2, 1300, 575);
                }

                if (evento.key.keysym.sym == SDLK_RIGHT)
                {
                    posx += 10;

                    irudiaMugitu(player2, posx - 3, 575);
                    irudiaMugitu(player1, 1300, 575);
                }

                if (evento.key.keysym.sym == SDLK_ESCAPE)
                {

                    GarbituMaila1(basura, fondo, player1, player2);
                    audioTerminate();
                    return -2;
                    break;
                }
            }

            if (evento.type == SDL_QUIT)
            {
                GarbituMaila1(basura, fondo, player1, player2);
                audioTerminate();
                return -2;
                break;
            }
        }
        irudiakMarraztu();
        textuaIdatzi(1120, 100, points);
        textuaGaitu();
        SDL_RenderPresent(gRenderer);
        SDL_Delay(16);

        running++;
        sf = running / 300;
        posy += 3 + sf;
    }
    GarbituMaila1(basura, fondo, player1, player2);
    audioTerminate();
    return 0;
}

void erorpen(SDL_Rect *rects)
{
    for (int i = 0; i < 10; i++)
    {
        rects[i].x = rand() % 1201;
        rects[i].y = (rand() % 300) - 100;
        rects[i].w = 45;
        rects[i].h = 45;
    }
}

void eguneratualtura(SDL_Rect rects[], int sf)
{
    for (int i = 0; i < 10; i++)
    {
        rects[i].y = rects[i].y + 3 + sf;
    }
}
void marraztubasura(SDL_Rect *rects, int foto)
{
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        irudiaMugitu(foto, rects[i].x, rects[i].y);
        irudiakMarraztu();
    }
}
void GarbituMaila1(int basura, int fondo, int player1, int player2)
{
    irudiaKendu(basura);
    irudiaKendu(fondo);
    irudiaKendu(player1);
    irudiaKendu(player2);
}
