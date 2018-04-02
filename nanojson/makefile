# Copyright (c) 2018 Martin McDonough.  All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CC?=gcc
LINK?=$(CC)
CFLAGS?=-Wall -Wextra -Werror -pedantic -ansi
AR?=ar
RANLIB?=ranlib
OBJPREFIX?=

shared: lib$(OBJPREFIX)nanojson.so

static: lib$(OBJPREFIX)nanojson.a

lib$(OBJPREFIX)nanojson.a: $(OBJPREFIX)nanojson.o
	$(AR) -rc lib$(OBJPREFIX)nanojson.a $(OBJPREFIX)nanojson.o
	$(RANLIB) lib$(OBJPREFIX)nanojson.a

lib$(OBJPREFIX)nanojson.so: $(OBJPREFIX)nanojson.o
	$(CC) $(OBJPREFIX)nanojson.o -shared -o lib$(OBJPREFIX)nanojson.so

$(OBJPREFIX)nanojson.o: nanojson.c nanojson.h
	$(CC) $(CFLAGS) -c nanojson.c -o $(OBJPREFIX)nanojson.o

clean:
	rm lib$(OBJPREFIX)nanojson.a || true
	rm lib$(OBJPREFIX)nanojson.so || true
	rm $(OBJPREFIX)nanojson.o || true

.PHONY: static shared clean

