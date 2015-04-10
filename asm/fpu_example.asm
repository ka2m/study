section .data
    fmtin: db "%lf%lf", 0
    fmtout: db "%lf", 10, 0

section .bss
    a: resq 1
    b: resq 1

section .text
    extern _scanf
    extern _printf
    global _main
    main:
        push b
        push a
        push fmtin
        call _scanf
        add esp, 12
        fld qword [a] ; st0 = a
        fadd qword [b] ; st0 = a + b
        fst qword [a] ; a = st0
        push dword [a+4]
        push dword [a]
        push fmtout
        call _printf
        add esp, 12
        xor eax, eax
        xor ecx, ecx
        ret
