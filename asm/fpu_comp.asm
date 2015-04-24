section .data
    fmt: db "%lf", 0
    mone: dq -1.0
    one: dq 1.0
    zero: dq 0.0
    ten: dq 10.0
    two: dq 2.0
    four: dq 4.0

section .bss
    x: resq 1

section .text
    extern _scanf
    extern _printf
    global _lab2
    global _lab1
    global _finish
    global _main
    _main:
        push x
        push fmt
        call _scanf
        add esp, 8
        fld qword [x]
        fld qword [one]

        fcomp
        fstsw ax
        sahf
        je _lab1

        fld qword [x]
        fld qword [mone]

        fcomp
        fstsw ax
        sahf
        je _lab2

        fld qword [x]
        fmul qword [two]
        jmp _finish
        _lab1:
            fld qword [x]
            fsub qword [four]
            jmp _finish

        _lab2:
            fld qword [x]
            fadd qword [ten]
            jmp _finish

        _finish:
            fstp qword [x]
            push dword [x+4]
            push dword [x]
            push fmt
            call _printf
            add esp, 12
            xor eax, eax
            xor ecx, ecx
            ret
