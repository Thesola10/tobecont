#ifndef __ASSETS_H
#define __ASSETS_H

/**
 * \file    assets_load.h
 * \brief   Browser-based asset downloader for WASM
 *
 * The symbols below are designed as drop-ins for those usually provided under
 * @ref assets_link.h .
 *
 * Asset files are expected to be relative to @ref WASM_URL_PREFIX .
 */

/// \brief Receptacle for arr.bmp as fetched over the Web
static const char *arr_bmp;
/// \brief Receptacle for tbc.wav as fetched over the Web
static const char *tbc_wav;

/// \brief Retrieved file size for arr.bmp
long arr_bmp_size;
/// \brief Retrieved file size for tbc.wav
long tbc_wav_size;

/**
 * This function allocates and populates the @ref arr_bmp and @ref tbc_wav
 * bytestrings with the contents of their corresponding asset files, as fetched
 * by the browser over HTTP or HTTPS. The request uses the browser's XHR API
 * and is the concatenation of @ref WASM_URL_PREFIX followed by the asset's
 * file name.
 *
 * \brief   Download assets from the Web
 * \return  0 on success, any other value otherwise.
 */
int wasmFetchAssets(void);

#endif //__ASSETS_H

// vim: ft=c.doxygen
