/*
 * uxstrings.h
 * This file is used to manage strings in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXSTRINGS_H
#define UXSTRINGS_H
#include "utils.h"

extern char *uxstring_lower(char *abc);
extern unsigned int uxstring_len(const char *input);
extern char *uxstring_dup(const char *input);
extern char * uxstring_copy(char *out, const char *in);
extern char * uxstring_cat(char *out, const char *in);

#endif
