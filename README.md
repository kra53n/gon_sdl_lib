# gon_sdl_lib

I'm not sure if anyone needs this lib. ¯\\_(ツ)_/¯.


## Example

To work, you need to use `SDL_Renderer` as `ren`. In `window.h` I have `winWdt`,
`winHgt` and etc for window drawing.


```c
#include <SDL.h>
#include "window.h"
#include "gon.h"


int main(int argc, char* argv[])
{
    init();

    Megagon meg;
    MegagonInit(meg, { winWdt / 2, winHgt / 2 }, 5, 50);

    for (int i = 0; i < 200; i++)
    {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 128, 255, 128, 255);
        MegagonDraw(meg);
        meg.pos.y += 0.2;
        if (!(i % 9)) meg.vertexes[i % meg.vertexesNum].size += 10;

        SDL_RenderPresent(ren);
        SDL_Delay(10);
    }

    MegagonDestroy(meg);
    deInit(0);
    return 0;
}
```
