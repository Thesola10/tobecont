#include "screenshot.h"

SDL_Surface *getScreenshot(SDL_DisplayMode DM)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, DM.w, DM.h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    CGDisplayCount dispCount;
    CGDirectDisplayID disp;

    CGGetActiveDisplayList(1, &disp, &dispCount);

    CGRect sz = CGRectMake(0, 0, DM.w, DM.h);

    CGImageRef scr = CGDisplayCreateImage(disp);

    CFDataRef sdat = CGDataProviderCopyData(CGImageGetDataProvider(scr));

    SDL_LockSurface(dest);
    CFDataGetBytes(sdat, CFRangeMake(0, CFDataGetLength(sdat)), dest->pixels);
    SDL_UnlockSurface(dest);

    CGImageRelease(scr);

    return (dest);
}
