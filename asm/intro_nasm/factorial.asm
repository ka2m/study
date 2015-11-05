section .data
    fmt: db "%d", 0
    one: dd 1

section .bss
    n: resd 1

section .text
    extern _printf
    extern _scanf
    global _lab
    global _fin
    global _main
    _main:
        push n
        push fmt
        call _scanf
        add esp, 8
        mov eax, [one]
        mov ecx, [one]
    _lab:
        cmp ecx, [n]
        jg _fin
        mul ecx
        add ecx, [one]
        jmp _lab
    _fin:
        push eax
        push fmt
        call _printf
        add esp, 8
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        ret


