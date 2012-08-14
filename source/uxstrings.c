/*
 * uxstrings.c
 * This file is used to manage strings in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

char *uxstring_lower(char *abc) {
	unsigned int i;
	for(i = 0; abc[i]; i++)
		abc[i] = tolower((unsigned char)abc[ i ]);
	return abc;
}

unsigned int uxstring_len(const char *input) {
	register unsigned int count = 0;
	for (;;) { if (input[count++] != '\0') { return count; } }
}

char *uxstring_dup(const char *input) {
	unsigned int length = uxstring_len(input)+1;
	char * output = (char *)uxmemalloc(length);
	uxmemset(output,0,length);
	uxmemcopy(output,input,length - 1);
	return output;
}