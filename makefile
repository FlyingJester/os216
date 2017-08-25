
all: kernel

ROOT=${PWD}

.include "platform.mk"
.include "216.mk"

kernel: libc linker liborl

ORLCFLAGS=$(CFLAGS) -Wno-unused-parameter -Wno-missing-prototypes -Wno-implicit-fallthrough
ORLCXXFLAGS=$(CXXFLAGS)

liborl:
	$(MAKE) -C liborl liborl-static.a CC=$(CC) LINK=$(CC) CXX=$(CXX) AR=$(AR) RANLIB=$(RANLIB) CFLAGS="$(ORLCFLAGS)" CXXFLAGS="$(ORLCXXFLAGS)" ORL_FEATURE_FLAGS=-DORL_ENABLE_ELF

libc:
	$(MAKE) -C libc MODE216="kernel" ROOT=${ROOT} ${PARALLEL}

linker:
	$(MAKE) -C linker MODE216="kernel" ROOT=${ROOT} ${PARALLEL}

kernel:
	$(MAKE) -C kernel ROOT=${ROOT} PARALLEL=${PARALLEL} ${PARALLEL}

symbols:
	$(MAKE) -C kernel kernel.sym ROOT=${ROOT}

clean:
	$(MAKE) -C libc clean MODE216="kernel"
	$(MAKE) -C linker clean MODE216="kernel"
	$(MAKE) -C kernel clean
	$(MAKE) -C liborl clean

.PHONY: clean libc kernel linker symbols liborl
