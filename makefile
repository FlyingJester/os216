
all: kernel

ROOT=${PWD}

.include "platform.mk"
.include "216.mk"

kernel: libc linker

liborl:
	$(MAKE) -C liborl

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

.PHONY: clean libc kernel linker symbols
