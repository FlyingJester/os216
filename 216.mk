
.include "platform.mk"

CC=$(PREFIX)gcc
CXX=$(PREFIX)g++
GOLD=$(PREFIX)ld.gold
OBJCOPY=$(PREFIX)objcopy
CCFLAGS=-Wall -Wextra -Werror -g -fno-builtin -nostdlib -ffreestanding -pipe -I$(ROOT)/libc/include
CFLAGS=$(CCFLAGS) -Os -ansi -Wenum-compare -Wjump-misses-init -Wmissing-prototypes
CXXFLAGS=$(CCFLAGS) -fno-exceptions -fno-rtti -std=c++03
AR=$(PREFIX)ar
RANLIB=$(PREFIX)ranlib
