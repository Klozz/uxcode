#ifndef UXUSB_H
#define UXUSB_H

/* Functions exported by uxusb module */
extern void uxusb_init();								//!< Init usb system (if required)
extern void uxusb_shutdown();							//!< Deinit usb system (if required)

extern int uxusb_modules_loaded;
extern int uxusb_usb_active;

#endif