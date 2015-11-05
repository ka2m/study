.model small
.stack 100h
.386
.data
row db 4 ; вывод с 5 строки
col db 9 ; с 10 строчки (0-нумерация)
mode db ? ; сохранение режима
char db 04Dh ; первый символ - M
attr db 9h ; первый аттрибут - ярко-зеленый
.code

setvm proc ; получение и установка видеорежима
    mov ah, 0Fh  ; получить
    int 10h
    mov mode, al ; сохранить в mode

    mov ah, 00h ; установить режим 03: текстовый
    mov al, 03h ; но с поддержкой графики
    int 10h
    ret
setvm endp

clear proc ; очистка экрана
    pusha
    mov ah, 06h ; очистить
    mov cx, 0000 ; с левого верхнего угла
    mov dx, 184fh ; до нижнего правого
    int 10h
    popa
    ret
clear endp

cursor proc
    pusha
    mov ah, 02h ; перенести курсор
    mov bh, 0   ; на страницу 0
    mov dh, row ; на строку из row
    mov dl, col ; на столбец из col
    int 10h
    popa
    ret
cursor endp

show proc
    pusha
    mov ah, 09h ; вывести на экран с аттрибутом
    mov al, char ; ascii-код
    mov bh, 0 ; номер страницы
    mov bl, attr ; аттрибут
    mov cx, 7 ; число повторений
    int 10h
    popa
    ret
show endp


start:
mov ax, @data
mov ds, ax
call setvm
call clear

mov cx, 6 ; 6 строк

draw_line:
    push cx ; запомнить итератор
    call cursor ; установить курсор
    call show ; отобразить строку символов
    inc char ; перейти к следующему символу
    inc attr ; к следующему аттрибуту
    inc row ; и к строке
    pop cx ; извлечь итератор перед уменьшением
    loop draw_line

mov ah, 10h ; ожидание ввода от пользователя
int 16h
call clear ; очистка экрана

mov ah, 05h ; переход на другую страницу
mov al, 01h ; для восстановления курсора
int	10h


mov ax, 4C00h ; выход
int 21h
end start
