/* Copyright (c) 2017-2018 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	FILE *src, *dst;
	int c;
	unsigned long i = 4;
	char buffer[5];
	if(argc < 4){
		fputs("Usage: bin_to_c <source> <dest> <name>\n", stderr);
		return EXIT_FAILURE;
	}
	src = fopen(argv[1], "rb");
	dst = fopen(argv[2], "wb");
	
	if(!src){
		fputs("Could not open input file", stderr);
		fputs(argv[1], stderr); fputc('\n', stderr);
	}
	
	if(!dst){
		fputs("Could not open output file", stderr);
		fputs(argv[2], stderr); fputc('\n', stderr);
	}
	
	if(!(src && dst))
		return EXIT_FAILURE;
	
	fputs("const unsigned char ", dst);
    fputs(argv[3], dst);
    fputs("[] = {\n    ", dst);
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[4] = ',';
	while((c = fgetc(src)) != EOF){
		
		if((c >> 4) > 9)
			buffer[2] = 'A' + (c >> 4) - 10;
		else
			buffer[2] = '0' + (c >> 4);
		
		if((c & 0x0F) > 9)
			buffer[3] = 'A' + (c & 0x0F) - 10;
		else
			buffer[3] = '0' + (c & 0x0F);
		
		if(i + sizeof(buffer) >= 80){
			fputs("\n    ", dst);
			i = 4;
		}
		i += sizeof(buffer);
		fwrite(buffer, 1, sizeof(buffer), dst);
	}
	fputs("\n};\n", dst);
}
