
global OS216_IOOut
OS216_IOOut:
    mov eax, [esp+4]
    mov edx, [esp+8]
    out dx, al
    ret

global OS216_IOIn
OS216_IOIn:
    mov edx, [esp+4]
    xor eax, eax
    in al, dx
    ret
