# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# All userland directories
ALL_USERLAND=sys

# Userland directories to include in the kernel image for booting.
# Currently the kernel image's packages includes just a test program.
# In the future it should include a ramdisk file server, an ELF program loader,
# and the drivers to bring the system online (disk, display, and keyboard).
# After that, the system should be able to boot itself from disk, and be
# debuggable in case of a failure.
PACKAGED_USERLAND=sys

all:
.for target in $(ALL_USERLAND)
	$(MAKE) -C $(target) PARALLEL=${PARALLEL}
.endfor

package:
	cp $(ROOT)/kernel/initrd/rd_contents_base.c $(ROOT)/kernel/initrd/rd_contents_new.c
	truncate -s 0 $(ROOT)/kernel/initrd/rd_list_new.inc
	truncate -s 0 $(ROOT)/kernel/initrd/rd_macro_new.inc
.for target in $(PACKAGED_USERLAND)
	$(MAKE) -C $(target) package ROOT=${ROOT} PARALLEL=${PARALLEL}
.endfor

clean:
.for target in $(ALL_USERLAND)
	$(MAKE) -C $(target) clean
.endfor

.PHONY: $(ALL_USERLAND) clean package
.IGNORE: clean
.SILENT: package
