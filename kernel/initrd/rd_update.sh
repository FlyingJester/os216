#!/bin/sh

# Any copyright of this file is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# If the source is different than the destination, or the destination doesn't
# exist, copy the source to the destination.
# update SRC DST
update() {
    src=$1
    dst=$2
    if [ -s $dst ]
    then
        # File exists, check if source is different, and if so, overwrite the
        # destination
        if ! cmp $src $dst
        then
            echo "Replacing $dst"
            cp $src $dst
        # If a third argument was passed, we should touch that file to mark it
        # as fully up to date.
        elif [ "$#" -ne 2 ]
        then
            echo "Touching $3"
            touch $3
        fi
    else
        echo "Initializing $dst"
        cp $src $dst
    fi
}

if [ "$1" == "source" ]
then
    # Update the contents and the include/macro files
    echo "Updating source"
    update rd_contents_new.inc rd_contents.inc
    update rd_macro_new.inc rd_macro.inc
elif [ "$1" == "object" ]
then
    echo "Updating objects."
    update rd_contents_new.o rd_contents.o libinitrd.a
else
    echo "Invalid operation"
    exit 1
fi
