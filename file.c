#include <stdio.h>
#include <stdint.h>
#include "fat.h"

/* This function will be altered heavily */
FILE* write_image_header(struct fat12_bs *p_bs_fat12, uint8_t *bootcode, char* output_filename)
{
	FILE* output;
	output = fopen(output_filename, "wb");	/* return an error */
	
	printf("--%x\r\n",output);
	fwrite(p_bs_fat12, 1, 62, output);	/* SIZES BASED ON FAT 12 */
	
	puts("--write bootcode\r\n");
	fwrite(bootcode, 1, 450, output);

	return output;
}
 
unsigned char append_image(char* data, unsigned int len, FILE* output)
{
	//how do we even do this?
	return 0;
}

unsigned char close_image_file(FILE* output)
{
	fclose(output);
	//errorchewk
	return 0;
}

/* This section will read and process files, and co operate with fat.c to create an image. It will be called by main after initialization of fat */