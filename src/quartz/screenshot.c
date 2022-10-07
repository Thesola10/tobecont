#include "screenshot.h"

SDL_Surface *getScreenshot(SDL_DisplayMode DM)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, DM.w, DM.h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    return (dest);
}
