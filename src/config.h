#ifndef __CONFIG_H
#define __CONFIG_H

/**
 * \file    config.h
 * \brief   Configuration options for To-Be-Continued
 */

#include <SDL.h>

/**
 * Expression that returns a value, in pixels, describing the X-coordinate
 * of the top-left corner of the arrow. Use <code>DM.w</code> for the display
 * area width, and <code>arrow->w</code> for the arrow's own width.
 *
 * \brief   Offset in pixels from left of screen
 */
#define ARROW_X     20

/**
 * Expression that returns a value, in pixels, describing the Y-coordinate
 * of the top-left corner of the arrow. Use <code>DM.h</code> for the display
 * area height, and <code>arrow->h</code> for the arrow's own height.
 *
 * \brief   Offset in pixels from top of screen
 */
#define ARROW_Y     DM.h - (arrow->h + 20)

/// \brief Sampling rate, in Hz, for background music.
#define SOUND_SMPRATE   44100
/// \brief PCM format, as SDL macro, for background music.
#define SOUND_FORMAT    AUDIO_S16
/// \brief Number of sound channels for background music.
#define SOUND_CHANNELS  2
/// \brief In samples, size of buffer to allocate during playback.
#define SOUND_BUFFER    4096
/// \brief In milliseconds, total duration of background music.
#define SOUND_DURATION  17800
/// \brief In milliseconds, when to show the splash screen.
#define SOUND_BUILDUP   3200

/// \brief Floating-point value for screenshot's red channel gamma
#define GAMMA_R     4
/// \brief Floating-point value for screenshot's green channel gamma
#define GAMMA_G     3
/// \brief Floating-point value for screenshot's blue channel gamma
#define GAMMA_B     1

#endif //__CONFIG_H

// vim: ft=c.doxygen
