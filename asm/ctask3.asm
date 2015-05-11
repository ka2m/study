section .data
    fmt: db "%lf", 0
    four: dq 4.0

section .bss
    x: resq 1

section .text
    extern _scanf
    extern _printf
    global _main
    _main:
     push x
     push fmt
     call _scanf
     add esp, 8
     fld qword [x]
     fsqrt
     fmul qword [four]
     fstp qword [x]

     push dword [x+4]
     push dword [x]
     push fmt
     call _printf
     add esp, 12
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    ret
