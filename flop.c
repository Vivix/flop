/* There's no place like home */
/* files -> fat12 image. */
#include <stdio.h>
#include <stdlib.h>
#include "fat.h"

int main(int argc, char* *argv)
{
	char* help = "\tHELP MESSAGE WILL BE HERE LOL";
	unsigned char input_filename_index;
	unsigned char output_filename_index;
	int i = 1;				/* Process our arguments. */
	char flag = 0;

	/*************************
	i	input folder / file
	o	output img
		input name+.img default
	f1	floppy 1.44mb	default
	f2	floppy 2.88mb
	hd	the full maximum of the fs (16mb~)
	h	print help and exit
	************************/

	if (argc <= 1) {
		puts(help);
		goto err_ex;
	}

	while(i < argc) {
		switch(argv[i][1]) {
		case 'h':
			if (argv[i][2] != 'd') {
				puts(help);
				goto zer_ex;
			}
			/* hdd chosen, set flag 0 for maximum size */
			flag = 0;
		break;
		case 'i':
			/* save the index into argv, nothing else */
			//RUN CHECK, SAME AS BELOW
			input_filename_index = ++i;
		break;
		case 'f':
			if (argv[i][2] < 0x31 | 0x32 < argv[i][2])
				goto err_ex;
			//set appropriate flag
			flag = (argv[i][2] & 0x0f);
			puts("You've chosen a valid floppy option.");
		break;
		case 'o':
			//check and set valid filename
			//CHECK
			output_filename_index = ++i;
		break;
		default:
			printf("Invalid argument: %s\r\n", argv[i]);
			puts(help);
			goto err_ex;
		break;
		}
		i++;
	}
	/* Initialize */
	initialize_fat(flag);

zer_ex:
	return 0;
err_ex:
	return -1;
}