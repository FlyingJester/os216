#!/bin/sh

# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# If the source is different than the destination, or the destination doesn't
# exist, copy the source to the destination.
# update SRC DST
update() {
    src=$1
    dst=$2
    if test -s dst
    then
        # File exists, check if source is different, and if so, overwrite the
        # destination
        if ! cmp $src $dst
        then
            cp $src $dst
        fi
    else
        cp $src $dst
    fi
}

# Update the contents and the include/macro files
update rd_contents_new.c rd_contents.c
update rd_macro_new.inc rd_macro.inc
update rd_list_new.inc rd_list.inc
