
all: kernel

ROOT=${PWD}

.include "platform.mk"

kernel: libc linker

libc:
	$(MAKE) -C libc MODE216="kernel" ROOT=${ROOT}

linker:
	$(MAKE) -C linker MODE216="kernel" ROOT=${ROOT}

kernel:
	$(MAKE) -C kernel ROOT=${ROOT}

symbols:
	$(MAKE) -C kernel kernel.sym ROOT=${ROOT}

clean:
	$(MAKE) -C libc clean MODE216="kernel"
	$(MAKE) -C linker clean MODE216="kernel"
	$(MAKE) -C kernel clean

.PHONY: clean libc kernel linker symbols
