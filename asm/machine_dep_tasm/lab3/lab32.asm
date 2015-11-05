.model small ;Модель памяти SMALL использует сегменты размером не более 64Кб
.stack 100h ;объявление сегмента стека
.code ;Начало сегмента кода
start: ;Выполнение программы
    mov eax, 65536 ; запись 65536 в регистр
    mov cx, 5 ; число цифр
    step:
        xor dx,dx ; очистка dx
        mov ebx, 10 ; делитель для перевода в 10ричную СС
        div ebx ; деление
        add dx, 30h ; аналогино задаче 1
        pop bx
        push dx
        push bx
        loop step
    pop bx
    mov cx,5
    xor eax,eax
    mov ah,02
    print:
        pop dx
        int 21h
        loop print

    int 20h ; выход
end start
