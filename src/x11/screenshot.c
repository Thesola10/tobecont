#include "screenshot.h"

SDL_Surface *getScreenshot(int aw, int ah)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, aw, ah, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    Display *disp = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(disp);

    XWindowAttributes attr = {0};
    XGetWindowAttributes(disp, root, &attr);

    XImage *img = XGetImage(disp, root, 0, 0,
            aw, ah, AllPlanes, ZPixmap);

    int x, y;
    SDL_LockSurface(dest);
    for (y = 0; y < ah; y++)
        for (x = 0; x < aw; x++)
            ((unsigned *) dest->pixels)[x + y * aw] = XGetPixel(img, x, y);
    SDL_UnlockSurface(dest);

    return (dest);
}
