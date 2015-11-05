section .data
    fmt: "%s", 0, 10
    str1: db "abc", 0
    str2: db "def",0

section .text
    extern _printf
    global _main
    _main:
        mov ax, str1
        mov eax, str2
        push eax
        push fmt
        call _printf
        xor eax, eax
        xor ebx, ebx
        ret
