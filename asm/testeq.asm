section .data
    fmtin: db "%d%d", 0
    fmtout1: db "a>b", 0, 10
    fmtout2: db "a<=b", 0, 10

section .bss
    a: resd 1
    b: resd 1

section .text
    extern _scanf
    extern _printf
    global _main
    global _lab1
    global _fin
    _main:
        push b
        push a
        push fmtin
        call _scanf
        add esp, 12
        mov eax, [a]
        cmp eax, [b]
        jg _lab1
        push fmtout2
        jmp _fin
        ret
    _lab1:
        push fmtout1
    _fin:
        call _printf
        add esp, 4
        xor eax, eax
        xor ecx, ecx
        ret
