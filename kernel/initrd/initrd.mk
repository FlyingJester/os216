# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: libinitrd.a

.include "../../216.mk"

rd_contents.o: initrd.h rd_contents.c rd_contents.inc rd_macro.inc rd_list.inc
	$(CC) $(CFLAGS) -c rd_contents.c -o rd_contents.o

libinitrd.a: rd_contents.o
	$(AR) -rc libinitrd.a rd_contents.o
	$(RANLIB) $(RANLIBFLAGS) libinitrd.a

clean:
	rm $(INC) libinitrd.a rd_contents.o

.IGNORE: clean generate_includes
.PHONY: clean
