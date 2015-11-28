.model tiny ; единый сегмент для создания COM-программы
.386 ; расширения 386 процессора
.code
org 100h ; перепрыгиваем PSP
start: ; точка входа в программу
jmp actual ; переход к выполнению

; вывод строки, адрес начала в DX
out_str:
    mov ah, 09h
    int 21h
    ret

; перенос строки
out_new_str:
    lea dx, newstr
    call out_str
    ret

; вывод двоеточия - разделителя компонент времени
out_colon:
    mov ah, 02h
    mov dl, ':'
    int 21h
    ret

; считыванмя компонента времени
; вызов 21,1 - результат (символ) в AL
; получим цифру из ASCII-кода
; запишем в переменную компоненты
; так как это была старшая часть числа (десятки)
; сдвинем влево на 4, чтобы было место для единиц
; считаем и занесем единицы в переменную
read_elem_timep:
   mov ah, 01h
   int 21h
   sub al, 30h
   mov byte ptr timep, al
   shl timep, 4
   int 21h
   sub al, 30h
   add timep, al
   ret

; отображение компоненты времени
; значение в десятичном виде в компоненте-переменной
; через логическое умножение на F (а потом на F0)
; получим каждый элемент компонента
; прибавим к каждому элементу 30h для получения ASCII-кода
; выведем на экран один элемент (старший) при помощи 21,6
; затем выведем второй элемент (младший)
show_elem_timep:
    mov al, byte ptr timep
    xor ah, ah
    mov cx, ax

    and al, 0Fh
    add al, 30h
    mov dl, al

    push dx

    mov ax, cx
    and ax, 0F0h
    shr ax, 04h
    add al, 30h

    mov dl, al

    mov ah, 06h
    int 21h

    pop dx
    int 21h

    ret

; отображение текущего времени
; занесем в переменную компонента значения
; регистров CH, CL, DH (часы, минуты, секунды)
; и выведем
show_cur_time:
    push dx
    lea dx, cur_t_str
    call out_str

    push cx
    mov byte ptr timep, ch
    call show_elem_timep
    call out_colon
    pop cx

    mov byte ptr timep, cl
    call show_elem_timep
    call out_colon
    pop dx
    mov byte ptr timep, dh
    call show_elem_timep
    call out_new_str
    ret

actual:
    ; --- GETTING TIME
    xor ax, ax
    mov ah, 02h
    int 1ah ; получение текущего времени

    call show_cur_time ; вывод на экран
    ; --- ENTERING NEW TIME

    lea dx, enter_h_str ; считывание часов
    call out_str
    call read_elem_timep
    call out_new_str
    mov ch, byte ptr timep

    push cx
    lea dx, enter_m_str ; считывание минут
    call out_str
    call read_elem_timep
    call out_new_str
    pop cx

    mov cl, byte ptr timep

    push cx
    lea dx, enter_s_str
    call out_str
    call read_elem_timep ; считывание секунд
    call out_new_str
    pop cx

    mov dh, byte ptr timep
    xor dl, dl

    mov ah, 03h ; запись времени в систему
    int 1ah

    xor cx, cx
    xor dx, dx

    mov ah, 02h
    int 1ah


    ; -- show new time
    ; вывод нового времени -проверка
    call show_cur_time

    ; выход
    mov ax, 4c00h
    int 21h


; --- VARIABLES --
; переменная компоненты из двух байт - старшая и младшая часть)
timep db 2 DUP(?)
cur_t_str db 'Current time: $'
ent_t_str db 'Entered time: $'
enter_h_str db 'Enter hours: $'
enter_m_str db 'Enter mins: $'
enter_s_str db 'Enter secs: $'

; перевод строки
newstr   db 0Ah, 0Dh, 24h

end start
