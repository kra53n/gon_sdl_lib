#include <SDL.h>
#include <stdio.h>

#pragma once

struct MegagonVertex
{
    int pos;
    int size;
};

struct Megagon
{
    SDL_Point pos;
    int vertexesNum;
    MegagonVertex* vertexes = NULL;
    float size;
};

void MegagonDraw(Megagon meg);
void MegagonInit(Megagon& meg, SDL_Point pos, int vertexesNum, float size);
void MegagonFree(Megagon meg);
