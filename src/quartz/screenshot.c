#include "screenshot.h"

SDL_Surface *getScreenshot(int aw, int ah)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, aw, ah, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    CGDisplayCount dispCount;
    CGDirectDisplayID disp;

    CGGetActiveDisplayList(1, &disp, &dispCount);

    CGRect sz = CGRectMake(0, 0, aw, ah);

    CGImageRef scr = CGDisplayCreateImage(disp);

    CFDataRef sdat = CGDataProviderCopyData(CGImageGetDataProvider(scr));

    SDL_LockSurface(dest);
    CFDataGetBytes(sdat, CFRangeMake(0, aw * ah * 4), dest->pixels);
    SDL_UnlockSurface(dest);

    CGImageRelease(scr);

    return (dest);
}
