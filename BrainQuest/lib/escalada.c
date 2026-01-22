#include "escalada.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"

#define MUSIC_FILE "../Debug/sound/escaladalevel.wav"

#define IMG_DIR "./img/"

#define BG_BMP "pareta.bmp"
#define LETRA_BG_BMP "letrafondo.bmp"

#define BODY_BMP "gorputza.bmp"
#define LH_BMP "lh.bmp"
#define RH_BMP "rh.bmp"
#define LF_BMP "lf.bmp"
#define RF_BMP "rf.bmp"

#define BODY_W 103
#define BODY_H 218

static void getBmpWH(const char *path, int *w, int *h)
{
    SDL_Surface *s = SDL_LoadBMP(path);
    if (!s)
    {
        *w = 1280;
        *h = 720;
        return;
    }
    *w = s->w;
    *h = s->h;
    SDL_FreeSurface(s);
}

static int isLetterKey(int ev)
{
    return (ev >= 'a' && ev <= 'z') || (ev >= 'A' && ev <= 'Z');
}

static char randLetter(void)
{
    return (char)('a' + (rand() % 26));
}

typedef struct
{
    int bg1, bg2;
    int body, lh, rh, lf, rf;
    int letraBg;
    int bgW, bgH;
    int letraBgW, letraBgH;
} Assets;

static int loadAssets(Assets *a)
{
    char path[256];

    snprintf(path, sizeof(path), "%s%s", IMG_DIR, BG_BMP);
    getBmpWH(path, &a->bgW, &a->bgH);
    a->bg1 = irudiaKargatu(path);
    a->bg2 = irudiaKargatu(path);

    snprintf(path, sizeof(path), "%s%s", IMG_DIR, LETRA_BG_BMP);
    getBmpWH(path, &a->letraBgW, &a->letraBgH);
    a->letraBg = irudiaKargatu(path);

    a->body = irudiaKargatu(IMG_DIR BODY_BMP);
    a->lh = irudiaKargatu(IMG_DIR LH_BMP);
    a->rh = irudiaKargatu(IMG_DIR RH_BMP);
    a->lf = irudiaKargatu(IMG_DIR LF_BMP);
    a->rf = irudiaKargatu(IMG_DIR RF_BMP);

    if (a->bg1 < 0 || a->bg2 < 0 || a->letraBg < 0 || a->body < 0 || a->lh < 0 || a->rh < 0 || a->lf < 0 || a->rf < 0)
    {
        fprintf(stderr, "ERROR: ezin kargatu BMPak (bg/anim/letrafondo)\n");
        return -1;
    }
    return 0;
}

static void unloadAssets(Assets *a)
{
    irudiaKendu(a->rf);
    irudiaKendu(a->lf);
    irudiaKendu(a->rh);
    irudiaKendu(a->lh);
    irudiaKendu(a->body);
    irudiaKendu(a->letraBg);
    irudiaKendu(a->bg2);
    irudiaKendu(a->bg1);
}

static void placeLimbs(const Assets *a, int pose, int bodyX, int bodyY)
{
    if (pose == 0)
    {
        irudiaMugitu(a->lh, bodyX - 10, bodyY + 30);
        irudiaMugitu(a->rh, bodyX + BODY_W - 10, bodyY + 60);
        irudiaMugitu(a->lf, bodyX + 5, bodyY + BODY_H - 10);
        irudiaMugitu(a->rf, bodyX + BODY_W - 40, bodyY + BODY_H - 35);
    }
    else
    {
        irudiaMugitu(a->lh, bodyX - 10, bodyY + 60);
        irudiaMugitu(a->rh, bodyX + BODY_W - 10, bodyY + 30);
        irudiaMugitu(a->lf, bodyX + 5, bodyY + BODY_H - 35);
        irudiaMugitu(a->rf, bodyX + BODY_W - 40, bodyY + BODY_H - 10);
    }
}

int Eskalada_Run(int running, SDL_Renderer *gRenderer)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned)time(NULL));
        seeded = 1;
    }
    char points[12];
    audioInit();
    loadTheMusic(MUSIC_FILE);
    playMusic();

    textuaGaitu();

    Assets A;
    if (loadAssets(&A) != 0)
    {
        return -1;
    }

    const int W = SCREEN_WIDTH;
    const int H = SCREEN_HEIGHT;

    int bodyX = (W - BODY_W) / 2;
    int bodyY = (H - BODY_H) / 2;
    int pose = 0;

    int scrollY = 0;

    float timerMax = 300.0f;
    float timer = timerMax;
    float speed = 1.0f;

    char letra = 'a';
    char textoLetra[2] = {'a', '\0'};
    int needsNewLetter = 1;
    int lost = 0;

    const int letraX = (W / 2) - 10;
    const int letraY = (H / 2) - 120;

    while (running > -1 && lost != 1)
    {
        SDL_Delay(16);
        snprintf(points, sizeof(points), "%d", running);

        int ev = ebentuaJasoGertatuBada();
        if (ev == TECLA_ESCAPE)
        {
            return -2;
            unloadAssets(&A);
            audioTerminate();
            break;
        }
        if (ev == GERTAERA_IRTEN)
        {
            return -3;
            unloadAssets(&A);
            audioTerminate();
            break;
        }

        if (needsNewLetter)
        {
            letra = randLetter();
            textoLetra[0] = letra;
            textoLetra[1] = '\0';

            timer = timerMax;
            needsNewLetter = 0;

            if (speed <= 6.0f)
            {
                speed += 0.1f;
            }
        }

        if (isLetterKey(ev))
        {
            char pressed = (char)tolower(ev);
            if (pressed == letra)
            {
                pose = 1 - pose;

                scrollY -= 15;
                if (scrollY < 0)
                {
                    scrollY += A.bgH;
                }

                needsNewLetter = 1;
            }
            else
            {
                lost = 1;
            }
        }

        timer -= speed;
        if (timer <= 0.0f)
        {
            lost = 1;
        }

        irudiaMugitu(A.bg1, 0, -scrollY);
        irudiaMugitu(A.bg2, 0, -scrollY + A.bgH);

        irudiaMugitu(A.body, bodyX, bodyY);
        placeLimbs(&A, pose, bodyX, bodyY);

        int letraBgX = letraX - (A.letraBgW / 2) + 10;
        int letraBgY = letraY - (A.letraBgH / 2) + 10;
        irudiaMugitu(A.letraBg, letraBgX, letraBgY);
        pantailaGarbitu();
        irudiakMarraztu();
        SDL_Rect bar;
        bar.x = (W / 2) - 150;
        bar.y = 40;
        bar.w = (int)timer;
        bar.h = 12;

        if (timer > timerMax * 0.5f)
        {
            SDL_SetRenderDrawColor(gRenderer, 0, 143, 57, 255);
        }
        else if (timer > timerMax * 0.2f)
        {
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
        }

        SDL_RenderFillRect(gRenderer, &bar);
        textuaIdatzi(letraX, letraY, textoLetra);
        textuaIdatzi(1120, 100, points);
        textuaGaitu();
        pantailaBerriztu();
        running++;
    }

    unloadAssets(&A);
    audioTerminate();
    return running;
}
