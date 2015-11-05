section .data
    fmt: db "%d", 0
    zero: dd 0
section .bss
    a: resd 1

section .text
    extern _scanf
    extern _printf
    global _main
    global _neg
    global _zero
    _main:
        push a
        push fmt
        call _scanf
        add esp, 8
        mov eax, [a]
        cmp eax, [zero]
        jl _neg
        je _zero
        mov ebx, 1
        jmp _fin
    _neg:
        mov ebx, -1
        jmp _fin
    _zero:
        mov ebx, 0
        jmp _fin
    _fin:
        push ebx
        push fmt
        call _printf
        add esp, 8
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        ret
