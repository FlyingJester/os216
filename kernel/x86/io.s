
global OS216_IOOut
OS216_IOOut:
    cmp [esp+12], DWORD 2
    jl OS216_IOOut8
    jg OS216_IOOut32
    ; fallthrough

global OS216_IOOut16
OS216_IOOut16:
    mov eax, [esp+4]
    mov edx, [esp+8]
    out dx, ax
    ret

global OS216_IOOut8
OS216_IOOut8:
    mov eax, [esp+4]
    mov edx, [esp+8]
    out dx, al
    ret

global OS216_IOOut32
OS216_IOOut32:
    mov eax, [esp+4]
    mov edx, [esp+8]
os216_io_out_32:
    out dx, eax
    ret

global OS216_IOIn
OS216_IOIn:
    cmp [esp+8], DWORD 2
    jl OS216_IOIn8
    jg OS216_IOIn32
    ; fallthrough

global OS216_IOIn16
OS216_IOIn16:
    mov edx, [esp+4]
    xor eax, eax
    in ax, dx
    ret

global OS216_IOIn8
OS216_IOIn8:
    mov edx, [esp+4]
    xor eax, eax
    in al, dx
    ret

global OS216_IOIn32
OS216_IOIn32:
    mov edx, [esp+4]
    in eax, dx
    ret
