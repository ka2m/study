section .data
    fmtin: db "%lf%lf%lf", 0
    fmtout: db "%lf", 10, 0
    two: dq 2.0
    four: dq 4.0
    fzero: dq 0.0

section .bss
    a: resq 1
    b: resq 1
    e: resq 1 ; e is c

section .text
    extern _scanf
    extern _printf
    global _main
    _main:
        push e
        push b
        push a
        push fmtin
        call _scanf
        add esp, 16
        fld qword [b]
        fmul qword [b] ; b^2
        fld qword [a] ; st0 = a st1 = b^2
        fmul qword [e]
        fmul qword [four]
        fsubr st1 ; st0 = b^2 - 4ae st1 = b^2
        fld qword [fzero] ; st0 = 0 st1 = D
        fcomp
        fstsw ax
        sahf
        fstp qword [fzero]
        jl _main

        fsqrt ; sqrt(b^2-4ae)
        fsub qword [b] ; sqrt(b^2-4ae)-b
        fdiv qword [two] ; (sqrt(D)-b) / 2
        fdiv qword [a] ; (sqrt(D) - b) / 2a
        fstp qword [a]
        push dword [a+4]
        push dword [a]
        push fmtout
        call _printf
        add esp, 12
        xor eax, eax
        xor ecx, ecx
        ret
