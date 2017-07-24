
.include "../../216.mk"

LIBPLATFORM=lib216platform.a

all: $(LIBPLATFORM)

OBJECTS=fatal.o print.o vga.o pci.o

$(LIBPLATFORM): $(OBJECTS)
	$(AR) rc $(LIBPLATFORM) $(OBJECTS)

fatal.o: fatal.c ../platform/fatal.h pc_print.h vga.h
	$(CC) $(CFLAGS) -c fatal.c -o fatal.o

print.o: print.c ../platform/print.h pc_print.h vga.h
	$(CC) $(CFLAGS) -c print.c -o print.o

vga.o: vga.c vga.h pc_print.h
	$(CC) $(CFLAGS) -c vga.c -o vga.o

pci.o: pci.cpp ../platform/bus.hpp ../driver.hpp ../device.h ../cpp.hpp
	$(CXX) $(CXXFLAGS) -c pci.cpp -o pci.o

clean:
	rm $(OBJECTS) $(LIBPLATFORM)

.PHONY: clean
.IGNORE: clean
