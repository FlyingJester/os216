
.include "../../216.mk"

LIBARCH=lib216arch.a

all: $(LIBARCH)

OBJECTS=interrupt.o memory.o init.o syscall.o

$(LIBARCH): $(OBJECTS)
	$(AR) rc $(LIBARCH) $(OBJECTS)

interrupt.o: interrupt.s
	$(AS) $(ASFLAGS) interrupt.s -o interrupt.o

memory.o: memory.s
	$(AS) $(ASFLAGS) memory.s -o memory.o

init.o: init.s
	$(AS) $(ASFLAGS) init.s -o init.o

syscall.o: syscall.s
	$(AS) $(ASFLAGS) syscall.s -o syscall.o

clean:
	rm $(OBJECTS) $(LIBPLATFORM)

.PHONY: clean
.IGNORE: clean
