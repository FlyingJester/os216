# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

all: kernel userland

ROOT=${PWD}

.include "platform.mk"
.include "216.mk"

# Tools used to build the kernel image.
tools:
	$(MAKE) -C tools

ORLCFLAGS=$(CFLAGS) -Wno-unused-parameter -Wno-missing-prototypes -Wno-implicit-fallthrough
ORLCXXFLAGS=$(CXXFLAGS)

liborl:
	$(MAKE) -C liborl liborl-static.a CC=$(CC) LINK=$(CC) CXX=$(CXX) AR=$(AR) RANLIB=$(RANLIB) CFLAGS="$(ORLCFLAGS)" CXXFLAGS="$(ORLCXXFLAGS)" ORL_FEATURE_FLAGS=-DORL_ENABLE_ELF

libc:
	$(MAKE) -C libc MODE216="kernel" ROOT=${ROOT} ${PARALLEL}

linker: tools
	$(MAKE) -C linker MODE216="kernel" ROOT=${ROOT} ${PARALLEL}

userland: libc liborl linker tools
	$(MAKE) -C userland PARALLEL=${PARALLEL} ROOT=${ROOT}

initrd: userland
	$(MAKE) -C userland package PARALLEL=${PARALLEL} ROOT=${ROOT}

kernel: tools libc linker liborl initrd
	$(MAKE) -C kernel ROOT=${ROOT} PARALLEL=${PARALLEL}

symbols: kernel
	$(MAKE) -C kernel kernel.sym ROOT=${ROOT}

clean_liborl:
	$(MAKE) -C liborl clean

clean: clean_liborl
	$(MAKE) -C libc clean MODE216="kernel"
	$(MAKE) -C linker clean MODE216="kernel"
	$(MAKE) -C kernel clean

.PHONY: clean libc kernel linker symbols liborl clean_liborl initrd userland tools
.IGNORE: clean_liborl
