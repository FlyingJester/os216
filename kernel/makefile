# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

.include "../216.mk"

all: kernel.elf

# Precompiled headers
CXX_PRECOMPILED_HEADER=cpp.hpp.gch
C_PRECOMPILED_HEADER=malloc.h.gch

cpp.hpp.gch: cpp.hpp
	$(CXX) $(CXXFLAGS) -H cpp.hpp

malloc.h.gch: malloc.h
	$(CC) $(CCFLAGS) -H malloc.h

# Platform and architecture libraries
LIBPLATFORM=$(PLATFORM)/lib216platform.a
LIBARCH=$(ARCH)/lib216arch.a
LIBINITRD=initrd/libinitrd.a

$(LIBPLATFORM): buildplatform

buildplatform:
	$(MAKE) -C $(PLATFORM) ${PARALLEL} ROOT=${ROOT}

$(LIBARCH): buildarch

buildarch:
	$(MAKE) -C $(ARCH) ${PARALLEL} ROOT=${ROOT}

$(LIBINITRD): buildinitrd

buildinitrd:
	$(MAKE) -C initrd

OBJECTS=cpp.o driver.o driver_interrupt.o device.o malloc.o message.o schedule.o kernel.o syscall.o physical_memory.o execute.o

COMMON_HEADERS=platform/fatal.h platform/print.h attributes.h

# includes to use liborl
ORLINCLUDE=-I$(ROOT)/liborl/include

# Kernel objects
cpp.o: cpp.cpp cpp.hpp cpp.hpp.gch
	$(CXX) $(CXXFLAGS) -c cpp.cpp -o cpp.o

malloc.o: malloc.c platform/fatal.h $(C_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CC) $(CFLAGS) $(MALLOC_OBJ_FLAGS) -c malloc.c -o malloc.o

physical_memory.o: physical_memory.c physical_memory.h assert.h platform/fatal.h arch/memory.h $(C_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CC) $(CFLAGS) $(MALLOC_OBJ_FLAGS) -c physical_memory.c -o physical_memory.o

driver_interrupt.o: driver_interrupt.cpp driver_interrupt.h driver.hpp $(CXX_PRECOMPILED_HEADER)
	$(CXX) $(CXXFLAGS) -c driver_interrupt.cpp -o driver_interrupt.o

driver.o: driver.cpp driver.hpp arch/memory.h arch/interrupts.h device.h $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c driver.cpp -o driver.o

device.o: device.c device.h
	$(CC) $(CFLAGS) -c device.c -o device.o

execute.o: execute.c execute.h $(C_PRECOMPILED_HEADER)
	$(CC) $(CFLAGS) $(ORLINCLUDE) -c execute.c -o execute.o

message.o: message.cpp message.hpp arch/memory.h $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c message.cpp -o message.o

schedule.o: schedule.cpp schedule.hpp $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c schedule.cpp -o schedule.o

syscall.o: syscall.cpp $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS) syscall.hpp
	$(CXX) $(CXXFLAGS) -c syscall.cpp -o syscall.o

kernel.o: kernel.cpp driver.hpp platform/bus.hpp arch/memory.h arch/timer.h $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c kernel.cpp -o kernel.o	

CRTBEGIN=`$(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o`
CRTEND=`$(CXX) $(CXXFLAGS) -print-file-name=crtend.o`
LIBGCC=`$(CXX) $(CXXFLAGS) -print-file-name=libgcc.a`

crtbegin.o:
	cp ${CRTBEGIN} ${PWD}

crtend.o:
	cp ${CRTEND} ${PWD}

libgcc.a:
	cp ${LIBGCC} ${PWD}

CRTSTARTOBJS=../libc/crti.o crtbegin.o
CRTENDOBJS=crtend.o ../libc/crtn.o

# Kernel binary
KLIBDEPS=$(LIBPLATFORM) $(LIBARCH) $(LIBINITRD)
KLIBS=$(KLIBDEPS) -lorl-static -l216c libgcc.a
KLIBDIRS=-L$(LIBCDIR) -L$(ORLDIR)

kernel.elf: $(KLIBDEPS) $(OBJECTS) $(CRTSTARTOBJS) $(CRTENDOBJS) libgcc.a $(ROOT)/libc/lib216c.a kernel216.ld
	$(CXX) $(CXXFLAGS) $(KLIBDIRS) $(CRTSTARTOBJS) $(OBJECTS) $(KLIBS) $(CRTENDOBJS) -T kernel216.ld -o kernel.elf
	$(OBJCOPY) --only-keep-debug kernel.elf kernel.sym
	$(STRIP) -s kernel.elf

clean:
	$(MAKE) -C $(PLATFORM) clean
	$(MAKE) -C $(ARCH) clean
	$(MAKE) -C initrd clean
	rm *.o kernel.elf $(PRECOMPILED_HEADERS) $(C_PRECOMPILED_HEADER) $(CXX_PRECOMPILED_HEADER) crtbegin.o crtend.o

.PHONY: clean mkplatform mkarch buildarch buildplatform
.IGNORE: clean
