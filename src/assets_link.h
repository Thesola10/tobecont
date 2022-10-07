#ifndef __ASSETS_LINK_H
#define __ASSETS_LINK_H

/**
 * \file    assets_link.h
 * \brief   Symbols from assets linker
 */

///\brief Start of assets/arr.bmp as exported by objcopy
extern const char _binary_assets_arr_bmp_start;
///\brief End of assets/arr.bmp as exported by objcopy
extern const char _binary_assets_tbc_wav_start;
///\brief Start of assets/tbc.wav as exported by objcopy
extern const char _binary_assets_arr_bmp_end;
///\brief End of assets/tbc.wav as exported by objcopy
extern const char _binary_assets_tbc_wav_end;

///\brief Exported pointer to start of assets/arr.bmp
static const char *arr_bmp = &_binary_assets_arr_bmp_start;
///\brief Exported pointer to start of assets/tbc.wav
static const char *tbc_wav = &_binary_assets_tbc_wav_start;

/**
 * We cannot use objcopy's <code>_binary_assets_arr_bmp_size</code> since it is
 * declared as an absolute symbol, which conflicts with PIC linking. As such,
 * we instead computer the size from the start and end pointers.
 *
 * \brief Computed expression for length of assets/arr.bmp
 */
#define arr_bmp_size  \
    (&_binary_assets_arr_bmp_end - &_binary_assets_arr_bmp_start)
/**
 * We cannot use objcopy's <code>_binary_assets_tbc_wav_size</code> since it is
 * declared as an absolute symbol, which conflicts with PIC linking. As such,
 * we instead compute the size from the start and end pointers.
 *
 * \brief Computed expression for length of assets/tbc.wav
 */
#define tbc_wav_size  \
    (&_binary_assets_tbc_wav_end - &_binary_assets_tbc_wav_start)


#endif //__ASSETS_LINK_H

// vim: ft=c.doxygen
