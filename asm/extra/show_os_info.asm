.model tiny ; режим с одним общим сегментом для создания COM
.386 ; использовать расширения 386 процессора
.code
org 100h ; прыжок через стек и PSP
start: ; точка входа в программу
jmp actual ; переход на выполнение самой программы

; вывод строки
; адрес строки в DX загружается в главной программе
out_str:
    mov ah, 09h
    int 21h
    ret

; перевод строки
out_new_str:
    lea dx, newstr
    call out_str
    ret

; получение n-ого бита
; в стеке - n
; получаем n, логически сдвигаем вправо
; после этого у нас остаются n+1, n+2, n+3 биты
; избавимся от них при помощи
; логического сложения с 1 для получения значения
; именно n-ого бита
; 1 или 0 в младшем бите регистра BX
; вернем это значение через стек
get_nth_bit_stack:
    pop bx
    pop cx
    mov dx, status
    shr dx, cl
    and dx, 1
    push dx
    push bx
    ret

; вывод строк yes или no
; передаем значение бита через стек
; сравниваем и загружаем адрес нужной строки
print_yn_stack:
    pop bx
    pop dx
    cmp dx, 1
    je yes
    jmp no
    yes:
        lea dx, yes_str
        jmp print
    no:
        lea dx, no_str
    print:
        call out_str
    push bx
    ret

; получение числа принтеров
; здесь просто необходимо получить старшие два бита
; так что get_nth_bit_stack не нужен
; получаем (в регистре 16ричное значение) ASCII код
; цифры и выводим
get_printer_status:
    mov dx, status
    mov cl, 0Eh
    shr dx, cl

    add dl, 30h
    mov ah, 06h
    int 21h
    ret

; подключен ли последовательный принтер
; нужен только 13 бит
get_serial_printer_status:
    mov cl, 0Dh
    push cx
    call get_nth_bit_stack
    call print_yn_stack
    ret

; подклчюен ли игровой адаптер
; аналогично прошлой процедуре
get_gamepad_status:
    mov cl, 0Ch
    push cx
    call get_nth_bit_stack
    call print_yn_stack
    ret

; поулчение количества адаптеров RS232
; сбросим значения bx и dx
; так как в dx будет количество
; а bx будет использоваться для
; сдвига битов результата влево
; так как получаем биты со СТАРШЕГО (11го)
get_rs232_status:
   xor bx, bx
   xor dx, dx

   mov cl, 0Bh
   push dx
   push cx
   call get_nth_bit_stack
   pop bx
   pop dx

   shl bx, 2
   add dx, bx

   mov cl, 0Ah
   push dx
   push cx
   call get_nth_bit_stack
   pop bx
   pop dx

   shl bx, 1
   add dx, bx

   mov cl, 09h
   push dx
   push cx
   call get_nth_bit_stack
   pop bx
   pop dx

   add dx, bx
   add dl, 30h

   mov ah, 06h
   int 21h
   ret

; получение видеорежима
; длина каждой строки вывода - 14 символов
; то есть 14 байт
; после получения значения
; загрузим в dx адрес начала массива
; строк-описаний видеорежимов
; и прибавим 14*(значение битов видеорежима)
; для получения начала каждой из строк-описаний

get_videmode_status:
    mov al, 5h
    push ax
    call get_nth_bit_stack
    pop dx
    shl dx, 1
    dec al
    push dx
    push ax
    call get_nth_bit_stack
    pop ax
    pop dx
    add dl, al

    push dx ; запишем в стек видеорежим
    mov dx, offset videomode_vars ; нулевой элемент массива
    xor bx, bx
    pop bx
    xchg ax, bx
    mov bx, 0Eh
    push dx
    mul bx ; умножение 14 на значение битов видеорежима
           ; в DX (результат в dx)
    pop dx
    add dx, ax  ; прибавляем смещение в массиве к начальному
                ; адресу массива строк-описаний

    call out_str ; выводим
    ret

; есть сопроцессор?
get_coporocessor_status:
    mov cl, 1h
    push cx
    call get_nth_bit_stack
    call print_yn_stack
    ret

; есть ли дисковые устройства и сколько их
get_disk_devices_status:
    mov cl, 0h
    push cx
    call get_nth_bit_stack
    pop ax
    push ax
    push ax
    call print_yn_stack ; есть или нет
    pop ax
    cmp ax, 0
    je cmn
    jmp gcnt
    gcnt: ; если есть, то выведем число
        call out_new_str
        lea dx, disktte_str
        call out_str
        xor dx, dx
        mov al, 7h ; 7 бит
        push ax
        call get_nth_bit_stack
        pop dx
        shl dx, 1
        dec al
        push dx
        push ax
        call get_nth_bit_stack
        pop ax
        pop dx
        add dl, al
        add dl, 30h
        mov ah, 06h
        int 21h
    cmn:
        ret

; вывод кол-ва памяти
get_phy_mem_status:
    int 12h ; прерывание для получения кол-ва памяти
    xor cx, cx
    itm: ; количество получено в 16сс, переведем в 10сс
        xor dx, dx
        mov bx, 10
        div bx
        add dl, 30h
        inc cx
        push dx
        cmp ax,0
        jne itm
    mov ah, 06h
    oupm: ; выведем
        pop dx
        int 21h
        loop oupm
    ret

actual:
    ; получение списка оборудования и сохранение
    ; в переменную
    int 11h
    mov status, ax

    ; последовательно получим каждый статус
    lea dx, printer_str
    call out_str
    call get_printer_status
    call out_new_str

    lea dx, sprinter_str
    call out_str
    call get_serial_printer_status
    call out_new_str

    lea dx, gamepad_str
    call out_str
    call get_gamepad_status
    call out_new_str

    lea dx, rs232_str
    call out_str
    call get_rs232_status
    call out_new_str

    lea dx, videomode_str
    call out_str
    call get_videmode_status
    call out_new_str

    lea dx, coprocessor_str
    call out_str
    call get_coporocessor_status
    call out_new_str

    lea dx, disk_devices
    call out_str
    call get_disk_devices_status
    call out_new_str

    ; получение кол-ва памяти
    lea dx, phy_mem_str
    call out_str
    call get_phy_mem_status
    call out_new_str

    ; выход
    mov ax, 4C00h
    int 21h
    ; ---- VARIABLES ---------
    ; строки-описания
    printer_str db 'Printers: $'
    sprinter_str db 'Serial printer: $'
    gamepad_str db 'Game adapters: $'
    disktte_str db 'Disk drives: $'
    rs232_str db 'RS-232 Adpaters: $'
    videomode_str db 'Initial video mode: $'
    coprocessor_str db 'Coprocessor: $'
    disk_devices db 'Disks: $'
    phy_mem_str db 'Physical memory size (KB): $'

    status dw 0000
    yes_str db 'yes$'
    no_str  db 'no$'
    newstr db 0Ah, 0Dh, 24h ; перевод строки
    ; строки-описания видеорежимов
    videomode_vars db 'none         $'
                   db '40x25 + color$'
                   db '80x25 + color$'
                   db 'black-white  $'
end start
