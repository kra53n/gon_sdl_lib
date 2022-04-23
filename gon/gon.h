#include <SDL.h>
#include <math.h>   
#include <stdio.h>
#include <malloc.h>

#pragma once

struct MegagonVertex
{
    int pos;
    int size;
};

struct Megagon
{
    SDL_Point pos;
    SDL_Color color;

    int vertexesNum;
    MegagonVertex* vertexes = NULL;
    float size;
    bool selected = false;
};

void MegagonInit(Megagon& meg, SDL_Point pos, int vertexesNum, float size);
void MegagonFree(Megagon meg);

void MegagonDraw(Megagon meg);
bool MegagonIsClicked(Megagon meg, int x, int y);