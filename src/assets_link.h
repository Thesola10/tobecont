/**
 * To Be Continued 1.0.0 (C) Karim 'TheSola10' Vergnes
 * License: GNU GPL 3.0
 * Symbols from assets linker
 */

#ifndef __ASSETS_LINK_H
#define __ASSETS_LINK_H

extern const char _binary_assets_arr_bmp_start;
extern const char _binary_assets_tbc_wav_start;
extern const char _binary_assets_arr_bmp_end;
extern const char _binary_assets_tbc_wav_end;

static const char *arr_bmp = &_binary_assets_arr_bmp_start;
static const char *tbc_wav = &_binary_assets_tbc_wav_start;

#define tbc_wav_size  \
    (&_binary_assets_tbc_wav_end - &_binary_assets_tbc_wav_start)
#define arr_bmp_size  \
    (&_binary_assets_arr_bmp_end - &_binary_assets_arr_bmp_start)

#endif //__ASSETS_LINK_H
