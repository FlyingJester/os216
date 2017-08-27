# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

.include "../../216.mk"

LIBARCH=lib216arch.a

all: $(LIBARCH)

OBJECTS=interrupt.o memory.o init.o 8259pic.o io.o syscall.o cpu_state.o

$(LIBARCH): $(OBJECTS)
	$(AR) rc $(LIBARCH) $(OBJECTS)

cpu_state.o: cpu_state.s
	$(AS) $(ASFLAGS) cpu_state.s -o cpu_state.o

interrupt.o: interrupt.s
	$(AS) $(ASFLAGS) interrupt.s -o interrupt.o

memory.o: memory.s
	$(AS) $(ASFLAGS) memory.s -o memory.o

init.o: init.s
	$(AS) $(ASFLAGS) init.s -o init.o

8259pic.o: 8259pic.s
	$(AS) $(ASFLAGS) 8259pic.s -o 8259pic.o

io.o: io.s
	$(AS) $(ASFLAGS) io.s -o io.o

syscall.o: syscall.s
	$(AS) $(ASFLAGS) syscall.s -o syscall.o

clean:
	rm $(OBJECTS) $(LIBPLATFORM)

.PHONY: clean
.IGNORE: clean
