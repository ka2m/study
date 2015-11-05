section .data
    fmt: db "%d", 0
    a: dd 5
    b: dd 5
    d: dd 12
    seven: dd 7
    two: dd 2

section .bss
    x: resd 1

section .text
    extern _printf
    global _main
    _main:
     mov eax, [b]
     mul dword [seven] ; 7b
     add eax, [a] ; a+7b
     sub eax, [x]
     mov [x], eax
     mov eax, [d]
     div dword [two]
     mov ebx, [x]
     sub ebx, eax
     mov [x], ebx
    push ebx
    push fmt
    call _printf
    add esp, 8
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    ret
