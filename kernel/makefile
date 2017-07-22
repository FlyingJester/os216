
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

$(LIBPLATFORM): buildplatform

buildplatform:
	$(MAKE) -C $(PLATFORM)

$(LIBARCH): buildarch

buildarch:
	$(MAKE) -C $(ARCH)

OBJECTS=cpp.o driver.o malloc.o message.o schedule.o kernel.o syscall.o

COMMON_HEADERS=platform/fatal.h platform/print.h

# Kernel objects
cpp.o: cpp.cpp cpp.hpp cpp.hpp.gch
	$(CXX) $(CXXFLAGS) -c cpp.cpp -o cpp.o

malloc.o: malloc.c platform/fatal.h $(C_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CC) $(CFLAGS) $(MALLOC_OBJ_FLAGS) -c malloc.c -o malloc.o

driver.o: driver.cpp driver.hpp arch/memory.h arch/interrupts.h $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c driver.cpp -o driver.o

message.o: message.cpp message.hpp arch/memory.h $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c message.cpp -o message.o

schedule.o: schedule.cpp schedule.hpp $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c schedule.cpp -o schedule.o

syscall.o: syscall.cpp $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS) syscall.hpp
	$(CXX) $(CXXFLAGS) -c syscall.cpp -o syscall.o

kernel.o: kernel.cpp $(CXX_PRECOMPILED_HEADER) $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c kernel.cpp -o kernel.o

# Kernel binary
kernel.elf: $(LIBPLATFORM) $(LIBARCH) $(OBJECTS) $(ROOT)/libc/lib216c.a kernel216.ld
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBPLATFORM) $(LIBARCH) -L$(ROOT)/libc -l216c libgcc.a -T kernel216.ld -o kernel.elf 

kernel.sym: kernel.elf
	$(OBJCOPY) --only-keep-debug kernel.elf kernel.sym

clean:
	$(MAKE) -C $(PLATFORM) clean
	$(MAKE) -C $(ARCH) clean
	rm *.o kernel.elf $(PRECOMPILED_HEADERS) $(C_PRECOMPILED_HEADER) $(CXX_PRECOMPILED_HEADER)

.PHONY: clean mkplatform mkarch buildarch buildplatform
.IGNORE: clean
