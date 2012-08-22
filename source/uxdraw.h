/*
 * uxdraw.h
 * This file is used to manage drawings in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXDRAW_H
#define UXDRAW_H

#include "uxgraphics.h"
#include "uxvertex.h"


/* Functions exported by uxdraw module */
extern void uxdraw_init();								//!< Init drawing system (if required)
extern void uxdraw_shutdown();							//!< Deinit drawing system (if required)
extern int uxdraw_inited;

extern void uxdraw_line(int x1, int y1, int x2, int y2, UXCOLOR color);
extern void uxdraw_rect(int x, int y, int w, int h, UXCOLOR color);


#endif