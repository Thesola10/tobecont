#include "main.h"

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


void renderDelay(SDL_Window *win, SDL_Renderer *rend)
{
    SDL_RenderPresent(rend);
    SDL_UpdateWindowSurface(win);
    SDL_Delay(16);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    SDL_Surface *arrow = SDL_LoadBMP_RW(SDL_RWFromConstMem(arr_bmp, arr_bmp_size), 1);

    SDL_Rect arrowRect;
    arrowRect.x = 20;
    arrowRect.y = DM.h - arrow->h - 20;
    arrowRect.w = arrow->w;
    arrowRect.h = arrow->h;

    SDL_AudioSpec obtainedSpec;
    SDL_AudioSpec wavSpec;
    wavSpec.freq     = 44100;
    wavSpec.format   = AUDIO_S16;
    wavSpec.channels = 2;
    wavSpec.samples  = 4096;
    wavSpec.callback = NULL;

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0,
            &wavSpec, &obtainedSpec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    SDL_QueueAudio(deviceId, tbc_wav, tbc_wav_size);

    SDL_PauseAudioDevice(deviceId, 0);

    SDL_Delay(3300);
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
            | SDL_WINDOW_OPENGL);

    SDL_Surface *shot = getScreenshot(DM);

    applyGamma(shot, 4, 3, 1);

    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *te  = SDL_CreateTextureFromSurface(rend, shot);
    SDL_Texture *art = SDL_CreateTextureFromSurface(rend, arrow);

    for (int frames = 860; frames; frames--) {
        SDL_RenderCopy(rend, te,  NULL, NULL);
        SDL_RenderCopy(rend, art, NULL, &arrowRect);
        renderDelay(win, rend);
    }

    SDL_DestroyWindow(win);
    SDL_FreeSurface(shot);
    SDL_DestroyTexture(te);
    SDL_DestroyRenderer(rend);
    SDL_CloseAudioDevice(deviceId);
    SDL_Quit();
    return 0;
}
