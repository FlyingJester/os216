
LIBC=lib216c.a
OBJECTS=string.o 
#stdlib.o ctype.o

all: $(LIBC)

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

string.o: string.c include/string.h
	$(CC) $(CFLAGS) -c string.c -o string.o

ctype.o: ctype.c include/ctype.h
	$(CC) $(CFLAGS) -c ctype.c -o ctype.o

clean:
	rm $(OBJECTS)
	rm $(LIBC)

.PHONY: clean
.IGNORE: clean
