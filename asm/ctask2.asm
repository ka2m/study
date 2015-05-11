section .data
    fmtin: db "%lf%lf%lf", 0
    fmtout: db "%lf", 10, 0
    seven: dq 7.0
    two: dq 2.0

section .bss
    a: resq 1
    b: resq 1
    d: resq 1
    x: resq 1
    sb: resq 1

section .text
    extern _scanf
    extern _printf
    global _main
    _main:
     push d
     push b
     push a
     push fmtin
     call _scanf
     add esp, 16

     fld qword [b]
     fmul qword [seven]
     fstp qword [sb]
     fld qword [a]

     fadd qword [sb]
     fstp qword [x]
     fld qword [d]

     fdiv qword [two]
     fsubr qword [x]
     fstp qword [x]

     push dword [x+4]
     push dword [x]
     push fmtout
     call _printf
     add esp, 12
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    ret
