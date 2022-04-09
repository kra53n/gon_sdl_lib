#include <SDL2/SDL.h>
#include <malloc.h>
#include <stdio.h>

#pragma once

struct Megagon;

void MegagonDraw(Megagon meg);
void MegagonInit(Megagon &meg, int vertexesNum, int size);
void MegagonFree(Megagon meg);
