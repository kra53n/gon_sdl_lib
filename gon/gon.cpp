#include <SDL2/SDL.h>
#include <malloc.h>
#include <stdio.h>
#include "gon.h"

const float RADIAN = M_PI / 180;

struct MegagonVertex
{
    int pos;
    int size;
};

struct Megagon
{
    SDL_Point pos;
    int vertexesNum;
    MegagonVertex* vertexes;
    float size;
};

void MegagonDraw(Megagon meg)
{
    for (int vert = 0; vert < meg.vertexesNum; vert++)
    {
        SDL_RenderDrawLine(
            ren,
            cos(meg.vertexes[vert].pos * RADIAN) 
                * meg.vertexes[vert].size + meg.pos.x,
            sin(meg.vertexes[vert].pos * RADIAN)
                * meg.vertexes[vert].size + meg.pos.y,
            cos(meg.vertexes[(vert+1)%meg.vertexesNum].pos * RADIAN)
                * meg.vertexes[(vert+1)%meg.vertexesNum].size + meg.pos.x,
            sin(meg.vertexes[(vert+1)%meg.vertexesNum].pos * RADIAN)
                * meg.vertexes[(vert+1)%meg.vertexesNum].size + meg.pos.y
        );
    }
}

void MegagonInit(Megagon &meg, int vertexesNum, int size)
{
    meg.vertexesNum = vertexesNum;
    meg.vertexes = (MegagonVertex*)malloc(sizeof(MegagonVertex) * meg.vertexesNum);
    if (meg.vertexes == NULL) { printf("Memory error int RectInit!"); exit(1); }

    int dist = 360 / meg.vertexesNum;
    for (int vert = 0; vert < meg.vertexesNum; vert++)
    {
        meg.vertexes[vert].pos = dist*vert + dist/2;
        meg.vertexes[vert].size = size;
    }
}

void MegagonFree(Megagon meg)
{
    free(meg.vertexes);
}
