#include "screenshot.h"

EM_JS(void, getMediaOneFrame, (char *tgt), {
    const canvas = document.createElement("canvas");
    const capture = async () => {
        const context = canvas.getContext("2d");
        const video = document.createElement("video");

        try {
            const captureStream = await navigator.mediaDevices.getDisplayMedia();
            video.srcObject = captureStream;
            context.drawImage(video, 0, 0, window.width, window.height);
            captureStream.getTracks().forEach(track => track.stop());
        } catch (err) {
            console.error("Error: " + err);
        }
    };

    const mybuf = Module._malloc(window.width * window.height * 4);

    capture(); 
    canvas.getImageData(0, 0, window.width, window.height).data.buffer;

    return mybuf;
});

SDL_Surface *getScreenshot(SDL_DisplayMode DM)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(
            0, DM.w, DM.h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff, 0);

    //TODO: Perform screenshot acquisition

    SDL_LockSurface(dest);
    //TODO: Perform screenshot copy into dest->pixels
    getMediaOneFrame(dest->pixels);
    SDL_UnlockSurface(dest);

    return (dest);
}
