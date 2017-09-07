# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

ALL_SYS=test
# Sys directories to include in the kernel image for booting.
PACKAGED_SYS=test

all:
.for target in $(ALL_SYS)
	$(MAKE) -C $(target) ${PARALLEL}
.endfor

package:
.for target in $(PACKAGED_SYS)
	$(MAKE) -C $(target) package ROOT=${ROOT} PARALLEL=${PARALLEL}
.endfor

clean:
.for target in $(ALL_USERLAND)
	$(MAKE) -C $(target) clean
.endfor

.PHONY: $(ALL_SYS) clean package
.IGNORE: clean
