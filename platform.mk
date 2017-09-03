# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

TOOLARCH=i686

PREFIX=$(TOOLARCH)-os216-

# If you do not have an os216 cross compiler built, use this instead.
#PREFIX=$(TOOLARCH)-elf-

ARCH=x86
PLATFORM=pc

AS=yasm
ASFLAGS=-m x86 -f elf32
ASFLATFLAGS=-m x86 -f bin
