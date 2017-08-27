/*
 * Copyright (c) 2017 Martin McDonough.  All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "include/ctype.h"

/*****************************************************************************/

int tolower(int c){
    if(c >= 'A' && c <= 'Z')
        return (c - 'A') + 'a';
    else
        return c;
}

/*****************************************************************************/

int toupper(int c){
    if(c >= 'a' && c <= 'z')
        return (c - 'a') + 'A';
    else
        return c;
}
