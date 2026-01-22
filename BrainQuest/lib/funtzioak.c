#include "ebentoak.h"
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

int kolisioa(int x0, int x1, int y0, int y1, int posx, int posy)
{
    if (x0 <= posx && posx <= x1 && y0 <= posy && posy <= y1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}