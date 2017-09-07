# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: test

PACKAGE_TARGET=test

.include "../../package.mk"

.include "../../../216.mk"

CRTBEGIN=`$(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o`
CRTEND=`$(CXX) $(CXXFLAGS) -print-file-name=crtend.o`

CRTSTARTOBJS=../../../libc/crti.o ${CRTBEGIN}
CRTENDOBJS=${CRTEND} ../../../libc/crtn.o

test: test.o test.ld
	$(LD) $(CRTSTARTOBJS) test.o $(CRTENDOBJS) -T test.ld -o test

test.o: test.s
	$(AS) $(ASFLAGS) test.s -o test.o

.PHONY: package
