#include <stdint.h>
#include "tool.h"
#include "file.h"

#pragma pack(1)
struct fat12_bs {
	uint8_t bootjmp[3];
	uint8_t oem_name[8];
	uint16_t byt_per_sector;
	uint8_t sect_per_clust;
	uint16_t reserved_sectors;
	uint8_t fat_amnt;
	uint16_t dir_entry_count;
	uint16_t total_sectors;
	uint8_t media_type;
	uint16_t sector_per_fat;

	uint16_t sector_per_track;
	uint16_t head_side_amnt;
	uint32_t hidden_sectors;
	uint32_t large_total_sectors;

	/* FAT 12 EBPB */
	uint8_t drive_num;
	uint8_t reserved;
	uint8_t signature;
	uint8_t volume_serial[4];
	uint8_t volume_label[11];
	uint8_t system_id_string[8];
	/* BOOT CODE FOLLOWED BY BOOT SIG */
};

int initialize_fat(char type)
{
	struct fat12_bs block;		/* I suck with names */

	/* BPB */

	block.bootjmp[0] = 0xeb;
	block.bootjmp[1] = 0x3c;
	block.bootjmp[2] = 0x90;

	fill(block.oem_name, "MSWIN4.1", 8);

	block.byt_per_sector = 512;
	block.sect_per_clust = 1;
	block.reserved_sectors = 1;
	/* TODO: MAKE 2 FAT vs 1 FAT OPTIONAL! */
	block.fat_amnt = 2;
	/* TODO: DROP HDD SUPPORT, VHD IS BETTER FOR THAT? Not if someone wants fat12 disk 
	*  IN ADDITION TO THIS THERE IS ALSO THE MATTER OF 5.25 DISKS AND OTHER ASSORTMENTS */
	block.dir_entry_count = 224;	//Unsure if this is correct!

	switch (type) {
	case 0:
	break;
	case 1:		/* 1.44 mb diskette. 1 474 560 byte -> 2880 sectors */
		block.total_sectors = 2880;	//2 byte
		block.media_type = 0xf0;
		block.sector_per_fat = 9;
			/* DOS 3.31 BPB */	//this being selectable might be a plus
		block.sector_per_track = 18;
		block.head_side_amnt = 2;	//double density
		block.hidden_sectors = 0;
		block.large_total_sectors = 0;	//only use if total sector count is 0
			/* EBPB */
		block.drive_num = 0;		//first removable media.
		block.reserved = 0;
		block.signature = 0x29;		// THIS SHOULD BE OPTIONAL.
						// 0x28 is pre ms-dos 4.0 lacking the two following sources, isntead having a DPT (int 1Eh).
		fill(block.volume_serial, "AABB", 4);	//TODO: Make this generate a better number.
		fill(block.volume_label, "VIVI       ", 11);
		fill(block.system_id_string, "FAT12   ", 8);
	break;
	case 2:
	break;
	}
	/* ========== SIXTY-ONE BYTES (61 b) ========= */
	/* Boot code, this is NOT a system disk! */
	write_image_header(&block);
	return 0;
}