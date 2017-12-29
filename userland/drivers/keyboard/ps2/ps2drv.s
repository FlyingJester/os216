; Copyright (c) 2018 Martin McDonough.  All rights reserved.
;
; This Source Code Form is subject to the terms of the Mozilla Public
; License, v. 2.0. If a copy of the MPL was not distributed with this
; file, You can obtain one at http://mozilla.org/MPL/2.0/.

extern OS216_DriverMain

global start
start:
    call OS216_DriverMain
    mov eax, 0
    ud2
