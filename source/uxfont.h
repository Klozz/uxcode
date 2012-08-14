
/*
 * uxfont.h
 * This file is used to manage fonts subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * Uses parts of intraFont by BenHur - http://www.psp-programming.com/benhur
 * Uses parts of pgeFont by InsertWittyName - http://insomniac.0x89.org
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXFONT_H
#define UXFONT_H


typedef struct UX_FONT {
	/* ... */
} UX_FONT;


/* Functions exported by uxfont module */
extern void uxfont_init();								//!< Init font system (if required)
extern void uxfont_shutdown();							//!< Deinit font system (if required)

#endif