#pragma once
#include <stdint.h>
#include <stdio.h>

FILE* write_image_header(struct fat12_bs *p_bs_fat12, uint8_t *bootcode, char output_filename);