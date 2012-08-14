/*
 * uxusb.h
 * This file is used to manage usb subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXUSB_H
#define UXUSB_H

/* Functions exported by uxusb module */
extern void uxusb_init();								//!< Init usb system (if required)
extern void uxusb_shutdown();							//!< Deinit usb system (if required)

extern int uxusb_modules_loaded;
extern int uxusb_usb_active;

#endif