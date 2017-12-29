# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: ps2

PACKAGE_TARGET=ps2

.include "../../../package.mk"

.include "../../../../216.mk"

ps2: ps2.o ps2drv.o
	$(LD) ps2.o ps2drv.o -T ../../../link.ld -o ps2

ps2drv.o: ps2drv.s
	$(AS) $(ASFLAGS) ps2drv.s -o ps2drv.o

ps2.o: ps2.c
	$(CC) $(CFLAGS) -c ps2.c -o ps2.o

clean:
	rm ps2 ps2.o ps2drv.o

.PHONY: package clean
