# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: kernel userland

ROOT=${PWD}

.include "platform.mk"
.include "216.mk"

# Tools used to build the kernel image.
tools: nanojson
	$(MAKE) -C tools ROOT=${ROOT}

EXTCFLAGS=$(CFLAGS) -Wno-unused-parameter -Wno-missing-prototypes -Wno-implicit-fallthrough
EXTCXXFLAGS=$(CXXFLAGS)
ORLDIR=${ROOT}/liborl
NJDIR=${ROOT}/nanojson
LIBCDIR=${ROOT}/libc

liborl:
	$(MAKE) -C $(ORLDIR) liborl-static.a CC=$(CC) LINK=$(CC) CXX=$(CXX) AR=$(AR) RANLIB=$(RANLIB) CFLAGS="$(EXTCFLAGS)" CXXFLAGS="$(EXTCXXFLAGS)" ORL_FEATURE_FLAGS=-DORL_ENABLE_ELF

# nanojson is used by some of the tools.
nanojson:
	$(MAKE) -C $(NJDIR) static

# Build nanojson in native os216 mode
216nanojson:
	$(MAKE) -C $(NJDIR) OBJSUFFIX=216 static CC=$(CC) LINK=$(CC) AR=$(AR) RANLIB=$(RANLIB) CFLAGS="$(EXTCFLAGS)"

libc:
	$(MAKE) -C $(LIBCDIR) MODE216="kernel" ROOT=${ROOT} ${PARALLEL}

runkconf: tools drivers.json
	tools/kconf drivers.json driver
	touch runkconf

userland: libc liborl tools 216nanojson runkconf
	$(MAKE) -C userland PARALLEL=${PARALLEL} ROOT=${ROOT}

initrd: userland
	$(MAKE) -C userland package PARALLEL=${PARALLEL} ROOT=${ROOT}

kernel: tools libc liborl initrd
	$(MAKE) -C kernel ROOT=${ROOT} PARALLEL=${PARALLEL} ORLDIR=${ORLDIR} LIBCDIR=${LIBCDIR}

symbols: kernel
	$(MAKE) -C kernel kernel.sym ROOT=${ROOT}

clean_liborl:
	$(MAKE) -C liborl clean

clean_nanojson:
	$(MAKE) -C $(NJDIR) clean

clean_216nanojson:
	$(MAKE) -C $(NJDIR) clean OBJSUFFIX=216

clean: clean_liborl clean_nanojson clean_216nanojson
	$(MAKE) -C libc clean MODE216="kernel"
	$(MAKE) -C kernel clean
	$(MAKE) -C userland clean

.PHONY: clean libc kernel symbols liborl clean_liborl initrd userland tools nanojson clean_nanojson 216nanojson clean_216nanojson
.IGNORE: clean_liborl
