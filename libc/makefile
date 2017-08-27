# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

LIBC=lib216c.a
OBJECTS=string.o stdio.o ctype.o

all: $(LIBC) crti.o crtn.o

.if ${MODE216} == "kernel"

.include "../216.mk"

CFLAGS+=-DOS216_KERNEL=1
CXXFLAGS+=-DOS216_KERNEL=1

.else

AR?=ar
RANLIB?=ranlib
CC?=cc
CFLAGS?=-Wall -Werror -pedantic -fno-builtin -g -Os

.endif

$(LIBC): $(OBJECTS)
	$(AR) -rc $(LIBC) $(OBJECTS)
	$(RANLIB) $(RANLIBFLAGS) $(LIBC)

stdlib.o: stdlib.c include/stdlib.h
	$(CC) $(CFLAGS) -c stdlib.c -o stdlib.o

stdio.o: stdio.c include/stdio.h
	$(CC) $(CFLAGS) -c stdio.c -o stdio.o

string.o: string.c include/string.h
	$(CC) $(CFLAGS) -c string.c -o string.o

ctype.o: ctype.c include/ctype.h
	$(CC) $(CFLAGS) -c ctype.c -o ctype.o

crti.o: crti.s
	$(AS) $(ASFLAGS) -o crti.o crti.s

crtn.o: crtn.s
	$(AS) $(ASFLAGS) -o crtn.o crtn.s

clean:
	rm $(OBJECTS) crti.o crtn.o
	rm $(LIBC)

.PHONY: clean
.IGNORE: clean
