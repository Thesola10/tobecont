#include "screenshot.h"

SDL_Surface *getScreenshot(SDL_DisplayMode DM)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, DM.w, DM.h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    Display *disp = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(disp);

    XWindowAttributes attr = {0};
    XGetWindowAttributes(disp, root, &attr);

    XImage *img = XGetImage(disp, root, 0, 0,
            DM.w, DM.h, AllPlanes, ZPixmap);

    int x, y;
    SDL_LockSurface(dest);
    for (y = 0; y < DM.h; y++)
        for (x = 0; x < DM.w; x++)
            ((unsigned *) dest->pixels)[x + y * DM.w] = XGetPixel(img, x, y);
    SDL_UnlockSurface(dest);

    return (dest);
}
