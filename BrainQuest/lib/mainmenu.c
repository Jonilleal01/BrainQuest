#include "mainmenu.h"
#include "funtzioak.h"
#include "graphics.h"
#include "imagen.h"
#include "ourTypes.h"
#include "soinua.h"
#include <SDL.h>

#define IMG_DIR "../Debug/img/"
#define MENU_BMP IMG_DIR "menu.bmp"
#define TITLE_BMP IMG_DIR "BrainQuest.bmp"
#define PLAY_BMP IMG_DIR "Jolastu.bmp"
#define QUIT_BMP IMG_DIR "Irten.bmp"

static int dentro(int x, int y, int rx, int ry, int rw, int rh)
{
    return (x >= rx && x <= rx + rw && y >= ry && y <= ry + rh);
}

MENU_STATE MainMenu_Run(MENU_STATE egoera)
{
    int imgBg = irudiaKargatu(MENU_BMP);
    int imgTitle = irudiaKargatu(TITLE_BMP);
    int imgPlay = irudiaKargatu(PLAY_BMP);
    int imgQuit = irudiaKargatu(QUIT_BMP);
    int imgQuitH = irudiaKargatu("./img/IrtenHover.bmp");
    int imgPlayH = irudiaKargatu("./img/JolastuHover.bmp");

    if (imgBg < 0 || imgTitle < 0 || imgPlay < 0 || imgQuit < 0)
    {
        return ST_IRTEN;
    }

    int titleX = (SCREEN_WIDTH - BTN_W) / 2, titleY = 120;
    int playX = (SCREEN_WIDTH - BTN_W) / 2, playY = 320;
    int quitX = (SCREEN_WIDTH - BTN_W) / 2, quitY = 420;

    irudiaMugitu(imgBg, 0, 0);
    irudiaMugitu(imgTitle, titleX, titleY);
    irudiaMugitu(imgPlay, playX, playY);
    irudiaMugitu(imgQuit, quitX, quitY);
    int running = 1;
    SDL_Event e;
    audioInit();
    loadTheMusic("./sound/menu.wav");
    playMusic();

    while (running)
    {

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                egoera = ST_IRTEN;
                running = 0;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    egoera = ST_IRTEN;
                    running = 0;
                }
                else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
                {
                    egoera = ST_MUNDUA;
                    running = 0;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x, my = e.button.y;

                if (dentro(mx, my, playX, playY, BTN_W, BTN_H))
                {
                    egoera = ST_MUNDUA;
                    running = 0;
                }
                else if (dentro(mx, my, quitX, quitY, BTN_W, BTN_H))
                {
                    egoera = ST_IRTEN;
                    running = 0;
                }
            }
        }
        int px, py;
        SDL_GetMouseState(&px, &py);
        if (dentro(px, py, playX, playY, BTN_W, BTN_H))
        {
            irudiaMugitu(imgPlay, 1200, 800);
            irudiaMugitu(imgPlayH, playX, playY);
        }
        else
        {
            irudiaMugitu(imgPlayH, 1200, 800);
            irudiaMugitu(imgPlay, playX, playY);
        }
        if (dentro(px, py, quitX, quitY, BTN_W, BTN_H))
        {
            irudiaMugitu(imgQuit, 1200, 800);
            irudiaMugitu(imgQuitH, quitX, quitY);
        }
        else
        {
            irudiaMugitu(imgQuitH, 1200, 800);
            irudiaMugitu(imgQuit, quitX, quitY);
        }
        pantailaGarbitu();
        irudiakMarraztu();
        pantailaBerriztu();
        SDL_Delay(16);
    }

    irudiaKendu(imgQuit);
    irudiaKendu(imgQuitH);
    irudiaKendu(imgPlay);
    irudiaKendu(imgPlayH);
    irudiaKendu(imgTitle);
    irudiaKendu(imgBg);

    audioTerminate();
    return egoera;
}