# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: test

PACKAGE_TARGET=test

.include "../../package.mk"

.include "../../../216.mk"

test: test.o test.ld
	$(LD) test.o -T test.ld -o test

test.o: test.s
	$(AS) $(ASFLAGS) test.s -o test.o

clean:
	rm test test.o

.PHONY: package
