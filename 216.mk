# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

.include "platform.mk"

CCTYPE?=g
CC="$(PREFIX)$(CCTYPE)cc"
CXX="$(PREFIX)$(CCTYPE)++"
LD=$(PREFIX)ld
STRIP=$(PREFIX)strip
OBJCOPY=$(PREFIX)objcopy
CCFLAGS=-Wall -Wextra -Werror -fno-builtin -nostdlib -ffreestanding -pipe -I${ROOT}/libc/include -I${ROOT}/libcpp/include
CFLAGS=$(CCFLAGS) -ansi -Wenum-compare -Wjump-misses-init -Wmissing-prototypes -g 
CXXFLAGS=$(CCFLAGS) -fno-exceptions -fno-rtti -std=c++03 -g 
AR=$(PREFIX)ar
RANLIB=$(PREFIX)ranlib
