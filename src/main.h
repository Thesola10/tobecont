#ifndef __MAIN_H
#define __MAIN_H

/**
 * \file    main.h
 * \brief   Primary header for To-Be-Continued
 */

#include <SDL.h>
#include "assets_link.h"

/**
 * This function should be defined in a subdirectory of <code>src</code>
 * named after the "backend name". It should return an SDL surface, the size of
 * the provided DisplayMode.
 *
 * \brief   Obtain screenshot as SDL surface
 * \param aw    The width, in pixels, of the expected screenshot surface.
 *              This value represents physical pixels on HiDPI systems.
 * \param ah    The height, in pixels, of the expected screenshot surface.
 *              This value represents physical pixels on HiDPI systems.
 * \return  An SDL surface containing a screenshot for the whole screen.
 */
SDL_Surface *getScreenshot(int aw, int ah);

#endif //__MAIN_H

// vim: ft=c.doxygen
