.if ${MODE216} == "kernel"

.include "../../216.mk"
CFLAGS+=-DOS216_KERNEL=1 -I../libc/include
CXXFLAGS+=-DOS216_KERNEL=1 -I../libc/include

.else

AR?=ar
RANLIB?=ranlib
CC?=cc
CFLAGS?=-Wall -Werror -pedantic -fno-builtin -g -Os

.endif

LIBELF=libzelda_elf.a

OBJECTS=elf_load.o

all: $(LIBELF)

$(LIBELF): $(OBJECTS)
	$(AR) -rc $(LIBELF) $(OBJECTS)
	$(RANLIB) $(LIBELF)

elf_load.o: elf_load.c elf_load.h elf.h
	$(CC) $(CFLAGS) -c elf_load.c -o elf_load.o


clean:
	rm $(OBJECTS) $(LIBELF)

.PHONY: clean
.SILENT: clean
.IGNORE: clean
