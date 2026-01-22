#include "mundua.h"
#include "graphics.h"
#include "imagen.h"
#include "ourTypes.h"
#include <SDL.h>

static int dentro(int mx, int my, int x, int y)
{
    return (mx >= x && mx <= x + BTN_W && my >= y && my <= y + BTN_H);
}

MENU_STATE Mundua_Run(MENU_STATE emaitza, SDL_Renderer *gRenderer)
{
    // Cargar imágenes
    int bg = irudiaKargatu(IMG_DIR "mundua.bmp");
    int b1 = irudiaKargatu(IMG_DIR "nibela.bmp");
    int b2 = irudiaKargatu(IMG_DIR "nibela.bmp");
    int t1 = irudiaKargatu("./img/BrainQuesta.bmp");

    int b1x = 360, b1y = 540;
    int b2x = 650, b2y = 140;

    irudiaMugitu(bg, 0, 0);
    irudiaMugitu(b1, b1x, b1y);
    irudiaMugitu(b2, b2x, b2y);
    irudiaMugitu(t1, 490, 50);

    SDL_Event e;
    int running = 1;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                emaitza = ST_IRTEN;
                running = 0;
                break;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                emaitza = ST_MENU;
                running = 0;
                break;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x;
                int my = e.button.y;

                if (dentro(mx, my, b1x, b1y))
                {
                    emaitza = ST_MUNDUA1;
                    running = 0;
                    break;
                }
                if (dentro(mx, my, b2x, b2y))
                {
                    emaitza = ST_MUNDUA2;
                    running = 0;
                    break;
                }
            }
        }

        SDL_RenderClear(gRenderer);
        irudiakMarraztu();
        pantailaBerriztu();
        SDL_Delay(16);
    }
    irudiaKendu(bg);
    irudiaKendu(b1);
    irudiaKendu(b2);
    irudiaKendu(t1);

    return emaitza;
}
