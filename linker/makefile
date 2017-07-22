.if defined(MODE216) && ${MODE216} == "kernel"

.include "../216.mk"
CFLAGS+=-DOS216_KERNEL=1 -I../libc/include
CXXFLAGS+=-DOS216_KERNEL=1 -I../libc/include

.else

AR?=ar
RANLIB?=ranlib
CC?=cc
LD?=cc
CFLAGS?=-Wall -Werror -pedantic -g -Os

RTLD=zelda
PRINTELF=printelf

.endif

LIBZELDA=libzelda.a

all: $(LIBZELDA) $(RTLD) $(PRINTELF)

LIBELF=elf/libzelda_elf.a
LIBDWARF=dwarf/libzelda_dwarf.a
LIBAOUT=a.out/libzelda_aout.a

$(LIBELF):
	$(MAKE) -C elf MODE216=$(MODE216)

$(LIBDWARF):
	$(MAKE) -C dwarf MODE216=$(MODE216)

$(LIBAOUT):
	$(MAKE) -C a.out MODE216=$(MODE216)

$(LIBZELDA): $(LIBELF)
	ar -M < zelda.mri

.if !defined(MODE216) || ${MODE216} != "kernel"
CLEAN_RTLD=clean_rtld
clean_rtld:
	rm *.o
	rm $(RTLD)
	rm $(PRINTELF)

ld.o: ld.c elf/elf.h elf/elf_load.h
	$(CC) $(CFLAGS) -c ld.c -o ld.o

printelf.o: printelf.c elf/elf.h elf/elf_load.h elf/elf_load.c
	$(CC) $(CFLAGS) -c printelf.c -o printelf.o

zelda: $(LIBZELDA) ld.o
	$(LD) $(LDFLAGS) ld.o $(LIBZELDA) -o zelda

printelf: $(LIBZELDA) printelf.o
	$(LD) $(LDFLAGS) printelf.o $(LIBZELDA) -o printelf

.endif

clean: $(CLEAN_RTLD)
	$(MAKE) -C elf clean MODE216=$(MODE216)
	$(MAKE) -C dwarf clean MODE216=$(MODE216)
	$(MAKE) -C a.out clean MODE216=$(MODE216)
	rm $(LIBZELDA)
	

.PHONY: clean $(CLEAN_RTLD)
.IGNORE: clean $(CLEAN_RTLD)
