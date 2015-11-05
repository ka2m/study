section .data
    fmtout: db "%d", 0, 10
    a: dd 10
    b: dd 1
    d: dd 14
    two: dd 2
    five: dd 5
    seven: dd 7

section .text
    extern _printf
    global _main
    _main:
    mov eax, [a]
    mul dword [two] ;mul works with eax by default, either enter reg as 1st arg
    mov [a], eax
    mov eax, [b]
    mul dword [five]
    sub [a], eax
    mov eax, [d]
    div dword [seven] ;div also works with eax
    add [a], eax
    push dword [a]
    push fmtout
    call _printf
    add esp, 8
    xor eax, eax
    xor ecx, ecx
    ret
