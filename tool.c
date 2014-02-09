#include <stdlib.h>
#include <stdint.h>

	/* test it */
char fill(uint8_t* entry, char* string, unsigned int len)
{
	int i;
	i = len;
	while (i != 0) {
		i--;
		entry[i] = (uint8_t) string[i];
	}
	return 0x00;
}