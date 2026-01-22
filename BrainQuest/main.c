#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "lib/Gameover.h"
#include "lib/escalada.h"
#include "lib/funtzioak.h"
#include "lib/galdera.h"
#include "lib/lehenMaila.h"
#include "lib/mainmenu.h"
#include "lib/mundua.h"
#include "lib/ourTypes.h"
#include "soinua.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Galderat g;
    int running = sgHasieratu();
    SDL_Renderer *gRenderer = getRenderer();
    datubaseahasieratu(&g);
    MENU_STATE egoera = ST_MENU;
    int point;
    while (running != -3 && egoera != ST_IRTEN)
    {
        if (egoera == ST_MENU)
        {
            egoera = MainMenu_Run(egoera);
        }
        running = 0;

        if (egoera == ST_MUNDUA)
        {
            egoera = Mundua_Run(egoera, gRenderer);
            if (egoera == ST_MUNDUA1)
            {
                while (running != -2)
                {
                    running = lehenMaila(gRenderer, running);
                    point = running;
                    if (running != -2)
                    {
                        running = galdera(g, gRenderer, running);
                    }
                }
                GameOver(gRenderer, point);
                egoera = ST_MUNDUA;
            }
            if (egoera == ST_MUNDUA2)
            {
                while (running != -2)
                {
                    running = Eskalada_Run(running, gRenderer);
                    point = running;
                    if (running != -2)
                    {
                        running = galdera(g, gRenderer, running);
                    }
                }
                GameOver(gRenderer, point);
                egoera = ST_MUNDUA;
            }
        }
    }
}