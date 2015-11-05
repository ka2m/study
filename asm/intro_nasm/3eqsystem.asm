section .data
    fmtout: db "%d", 0, 10
    fmtin: db "%d", 0
    two: dd 2
    three: dd 3
    zero: dd 0

section .bss
    x: resd 1

section .text
    extern _scanf
    extern _printf
    global _main
    global _pos
    global _zero
    _main:
        push x
        push fmtin
        call _scanf
        add esp, 8
        mov eax, [x]
        cmp eax, [zero]
        jl _neg
        je _zero
        mul dword [x]
        jmp _fin
    _neg:
        mul dword [two]
        add eax, [three]
        jmp _fin
    _zero:
        mov eax, [zero]
        jmp _fin
    _fin:
        push eax
        push fmtout
        call _printf
        add esp, 8
        xor eax, eax
        xor ebx, ebx
        ret


