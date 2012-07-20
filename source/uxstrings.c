#include "utils.h"

char *str_lower(char *abc) {
	unsigned int i;
	for(i = 0; abc[i]; i++)
		abc[i] = tolower((unsigned char)abc[ i ]);
	return abc;
}