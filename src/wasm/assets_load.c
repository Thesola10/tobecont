#include <emscripten/emscripten.h>
#include "assets_load.h"

EM_JS(int, getFileToArray, (char *uri, char *tgt, long &size), {
    var XHR = new XMLHttpRequest();
    XHR.onload = function(e) {
        if (XHR.status >= 400) {
            return 1;
        } else {
            // copy buffer and length
            return 0;
        }
    };
    XHR.onerror = reject;
    XHR.open("GET", uri);
    XHR.send();
});

int wasmFetchAssets(void)
{
    if (getFileToArray(WASM_URL_PREFIX "arr.bmp", arr_bmp, &arr_bmp_size))
        return 1;
    if (getFileToArray(WASM_URL_PREFIX "tbc.wav", tbc_wav, &tbc_wav_size))
        return 2;

    return 0;
}
