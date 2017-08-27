; Copyright (c) 2017 Martin McDonough.  All rights reserved.
;
; This Source Code Form is subject to the terms of the Mozilla Public
; License, v. 2.0. If a copy of the MPL was not distributed with this
; file, You can obtain one at http://mozilla.org/MPL/2.0/.

section .init
align 4

global _init:function
_init:
    push ebp
    mov ebp, esp

section .fini
align 4

global _fini:function
_fini:
    push ebp
    mov ebp, esp
