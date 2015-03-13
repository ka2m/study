section .data
    fmtin: db "%d%d", 0
    fmtout: db "%d", 0, 10
    two: dd 2
    five: dd 5

section .bss
    a: resd 1
    b: resd 1

section .text
    extern _scanf
    extern _printf
    global _main:
    _main:
        push b
        push a
        push fmtin
        call _scanf
        add esp, 12
        mov eax, [a]
        mul dword [two]
        mov ebx, eax
        mov eax, [b]
        div dword [five]
        sub ebx, eax
        mov [a], ebx
        push ebx
        push fmtout
        call _printf
        add esp, 8
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        ret
