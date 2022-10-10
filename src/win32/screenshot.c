#include "screenshot.h"

SDL_Surface *getScreenshot(SDL_DisplayMode DM)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, DM.w, DM.h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    HDC hdc = CreateDCA("DISPLAY", NULL, NULL, NULL);

    HDC hdest = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, DM.w, DM.h);
    HGDIOBJ sel = SelectObject(hdest, bmp);

    BitBlt(hdest, 0, 0, DM.w, DM.h, hdc, 0, 0, SRCCOPY);

    SDL_LockSurface(dest);
    GetBitmapBits(bmp, DM.w * DM.h * 32, dest->pixels);
    SDL_UnlockSurface(dest);

    SelectObject(hdest, sel);
    DeleteDC(hdest);
    return (dest);
}
