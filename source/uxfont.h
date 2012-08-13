#ifndef UXFONT_H
#define UXFONT_H


typedef struct UX_FONT {
	/* ... */
} UX_FONT;


/* Functions exported by uxfont module */
extern void uxfont_init();								//!< Init font system (if required)
extern void uxfont_shutdown();							//!< Deinit font system (if required)

#endif