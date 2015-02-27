section .data
    a: db "Hello, world!", 0, 10

section .text
    extern _printf
    global _main

    _main:
    push a
    call _printf
    add esp, 4
    xor eax, eax
    ret
