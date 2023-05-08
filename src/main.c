#include <stdbool.h>
#include "main.h"
#include "config.h"

static bool quit = false;

unsigned int do_quit(unsigned int tmr, void *unused) {
    quit = true;
    return 0;
}

unsigned char px_gamma(unsigned char channel, float gamma)
{
    float chnl_work = (float) channel;
    float gamma_work = (float) gamma;

    chnl_work = 255 * powf(chnl_work/255, 1/gamma_work);
    return (unsigned char) chnl_work;
}

unsigned long getFilteredPixel(unsigned long pixel, float r, float g, float b)
{
    unsigned char breakdown[3];

    // Split up pixel
    breakdown[0] = (int)((pixel & 0x00ff0000) >> 16);
    breakdown[1] = (int)((pixel & 0x0000ff00) >> 8);
    breakdown[2] = (int)((pixel & 0x000000ff));

    // Apply gamma formula
    breakdown[0] = px_gamma(breakdown[0], r);
    breakdown[1] = px_gamma(breakdown[1], g);
    breakdown[2] = px_gamma(breakdown[2], b);

    // Rebuild the pixel
    pixel  = breakdown[0]; pixel = pixel << 8;
    pixel += breakdown[1]; pixel = pixel << 8;
    pixel += breakdown[2];
    return pixel;
}

void applyGamma(SDL_Surface *surf, float r, float g, float b)
{
    int x, y;
    SDL_LockSurface(surf);
    for (y = 0; y < surf->h; y++)
        for (x = 0; x < surf->w; x++)
            ((unsigned *) surf->pixels)[x + y * surf->w]
                    = getFilteredPixel(((unsigned *)surf->pixels)[x + y * surf->w], r, g, b);
    SDL_UnlockSurface(surf);
}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    SDL_Surface *arrow = SDL_LoadBMP_RW(SDL_RWFromConstMem(arr_bmp, arr_bmp_size), 1);
    
    SDL_Rect arrowRect;
    arrowRect.x = ARROW_X;
    arrowRect.y = ARROW_Y;
    arrowRect.w = arrow->w;
    arrowRect.h = arrow->h;

    SDL_AudioSpec obtainedSpec;
    SDL_AudioSpec wavSpec;
    wavSpec.freq     = SOUND_SMPRATE;
    wavSpec.format   = SOUND_FORMAT;
    wavSpec.channels = SOUND_CHANNELS;
    wavSpec.samples  = SOUND_BUFFER;
    wavSpec.callback = NULL;
    wavSpec.userdata = NULL;

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0,
            &wavSpec, &obtainedSpec, 0);
    SDL_QueueAudio(deviceId, tbc_wav, tbc_wav_size);

    SDL_PauseAudioDevice(deviceId, 0);

    // Schedule exit by end of song
    SDL_AddTimer(SOUND_DURATION, &do_quit, NULL);

    // Start freeze-frame a wee bit before drop, opening a new SDL window
    // takes time!
    SDL_Delay(SOUND_BUILDUP);

    SDL_Window *win = SDL_CreateWindow(
            "ah-buh-bye! :D",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            DM.w, DM.h,
            SDL_WINDOW_FULLSCREEN
            | SDL_WINDOW_SHOWN
            | SDL_WINDOW_INPUT_GRABBED
            | SDL_WINDOW_MOUSE_CAPTURE
            | SDL_WINDOW_ALWAYS_ON_TOP
            | SDL_WINDOW_ALLOW_HIGHDPI
            | SDL_WINDOW_OPENGL);

    int aw = 0, ah = 0;
    SDL_GL_GetDrawableSize(win, &aw, &ah);

    SDL_Surface *shot = getScreenshot(aw, ah);
    applyGamma(shot, GAMMA_R, GAMMA_G, GAMMA_B);

    SDL_GLContext *gc = SDL_GL_CreateContext(win);
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *te  = SDL_CreateTextureFromSurface(rend, shot);
    SDL_Texture *art = SDL_CreateTextureFromSurface(rend, arrow);

    while (!quit) {
        SDL_PumpEvents();
        SDL_RenderCopy(rend, te,  NULL, NULL);
        SDL_RenderCopy(rend, art, NULL, &arrowRect);
        SDL_RenderPresent(rend);
        SDL_UpdateWindowSurface(win);
    }

    SDL_DestroyWindow(win);
    SDL_FreeSurface(shot);
    SDL_DestroyTexture(te);
    SDL_DestroyRenderer(rend);
    SDL_GL_DeleteContext(gc);
    SDL_CloseAudioDevice(deviceId);
    SDL_Quit();
    return 0;
}
