#include "window.h"
#include "gon.h"

const float RADIAN = M_PI / 180;

// Transform coords from position at trigonometric circle multpiplied on scale
// to screen coords
void transformCoords(int centerx, int centery, float degreepos,
    float size, int& x, int& y)
{
    x = cos(degreepos * RADIAN) * size + centerx;
    y = sin(degreepos * RADIAN) * size + centery;
}

void MegagonInit(Megagon& meg, SDL_Point pos, int vertexesNum, float size)
{
    meg.pos = pos;
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

int** getTransformedCoordsFromMegagonToPolygon(const Megagon& meg, int mouse_x, int mouse_y)
{
    int** polygon = (int**)malloc(sizeof(int*) * (meg.vertexesNum+1));
    for (int i = 0; i < meg.vertexesNum + 1; i++)
    {
        polygon[i] = (int*)malloc(sizeof(int) * 2);

        int x, y;
        transformCoords(meg.pos.x, meg.pos.y, meg.vertexes[i%meg.vertexesNum].pos,
            meg.vertexes[i % meg.vertexesNum].size, x, y);
        polygon[i][0] = x - mouse_x;
        polygon[i][1] = y - mouse_y;
    }
    return polygon;
}

void freeTransformedCoordsFromMegagonToPolygon(int** polygon, int vertexes)
{
    for (int i = 0; i < vertexes + 1; i++)
        free(polygon[i]);
    free(polygon);
}

float getVectorLen(int* v)
{
    return sqrt(v[0]*v[0] + v[1]*v[1]);
}

float getAngleBetweenVectors(int* v1, int* v2)
{
    float cosine = (v1[0]*v2[0] + v1[1]*v2[1]) / (getVectorLen(v1) * getVectorLen(v2));
    return acos(cosine);
}

void MegagonDraw(Megagon meg)
{
    for (int vertidx = 0; vertidx < meg.vertexesNum; vertidx++)
    {
        int vertx1, verty1;
        int vertx2, verty2;
        transformCoords(meg.pos.x, meg.pos.y,
            meg.vertexes[vertidx].pos,
            meg.vertexes[vertidx].size,
            vertx1, verty1
        );
        transformCoords(meg.pos.x, meg.pos.y,
            meg.vertexes[(vertidx + 1) % meg.vertexesNum].pos,
            meg.vertexes[(vertidx + 1) % meg.vertexesNum].size,
            vertx2, verty2
        );
        SDL_RenderDrawLine(ren, vertx1, verty1, vertx2, verty2);
    }
}

bool MegagonIsClicked(Megagon meg, int x, int y)
{
    int** polygon = getTransformedCoordsFromMegagonToPolygon(meg, x, y);
    float sumAngles = 0;

    for (int i = 0; i < meg.vertexesNum; i++)
        sumAngles += getAngleBetweenVectors(polygon[i], polygon[i+1]);

    float diff = 0.000001;
    if (sumAngles - diff <= M_PI*2 && M_PI*2 <= sumAngles + diff)
        return true;

    freeTransformedCoordsFromMegagonToPolygon(polygon, meg.vertexesNum);
    return false;
}