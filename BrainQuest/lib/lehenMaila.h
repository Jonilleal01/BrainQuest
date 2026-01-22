#include <SDL2/SDL.h>

#ifndef LEHENMAILA_H
#define LEHENMAILA_H
int lehenMaila(SDL_Renderer *gRenderer, int running);
void erorpen(SDL_Rect *rects);
void eguneratualtura(SDL_Rect rects[], int posy);
void marraztubasura(SDL_Rect *rects, int foto);
void GarbituMaila1(int basura, int fondo, int player1, int player2);
#endif
