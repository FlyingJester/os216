# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# build scripts to package the userland into a C file with a map in it.
# This is used to build the programs included in the kernel image.

# To use this script, add a PACKAGE_TARGET macro that points to the executable
# to package, and PACKAGE_NAME that is the name as a valid C identifier.
# If PACKAGE_NAME is undefined, it will default to PACKAGE_TARGET

PACKAGE_NAME?=${PACKAGE_TARGET}

package: $(PACKAGE_TARGET)
	$(ROOT)/tools/bin_to_c $(PACKAGE_TARGET) ./tmp.c $(PACKAGE_NAME)
	cat ./tmp.c >> $(ROOT)/kernel/initrd/rd_contents_new.inc
	rm ./tmp.c
	echo "X(${PACKAGE_NAME})" >> $(ROOT)/kernel/initrd/rd_macro_new.inc

