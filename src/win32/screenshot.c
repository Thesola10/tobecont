#include "screenshot.h"

SDL_Surface *getScreenshot(int aw, int ah)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, aw, ah, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    HDC hdc = CreateDCA("DISPLAY", NULL, NULL, NULL);

    HDC hdest = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, aw, ah);
    HGDIOBJ sel = SelectObject(hdest, bmp);

    BitBlt(hdest, 0, 0, aw, ah, hdc, 0, 0, SRCCOPY);

    SDL_LockSurface(dest);
    GetBitmapBits(bmp, aw * ah * 32, dest->pixels);
    SDL_UnlockSurface(dest);

    SelectObject(hdest, sel);
    DeleteDC(hdest);
    return (dest);
}
