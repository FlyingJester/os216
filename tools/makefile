
TOOLS=bin_to_c kconf

all: $(TOOLS)

bin_to_c: bin_to_c.c
	gcc bin_to_c.c -o bin_to_c

kconf: kernel_config.cpp ../nanojson/nanojson.h ../nanojson/libnanojson.a
	g++ kernel_config.cpp -I${ROOT} -L${ROOT}/nanojson -lnanojson -o kconf
