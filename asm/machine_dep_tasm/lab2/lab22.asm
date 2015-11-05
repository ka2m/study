.model small ;Модель памяти SMALL использует сегменты размером не более 64Кб
.stack 100h
.data
.code ;Начало сегмента кода

outSym proc ; для A...F
  add dl, 07h
  ret
outSym endp

prepNum proc
  add dl, 30h ; для 0...9
  cmp dl, 3ah
  jge outSym ; если цифра A...F - добавить 0x7
  ret
prepNum endp

print proc
  mov ah,02h ; 02 - вывод символа в stdout
  int 21h ; вызов прерывания
  ret
print endp

printStr proc ; вывод одной строки
    mov dl, cl ; передадим в DL первую цифру
    call PrepNum ; подготовим ее ASCII код
    call print ; выведем
    mov dl, 20h ; пробел
    call print
    mov dl, bl ; аналогично для второй цифры
    call PrepNum
    call print
    mov dl, 0ah ; \n - перенос строки
    call print
    mov dl, 0dh; \r - возвращение каретки
    call print
    ret
endp printStr

start: ;Выполнение программы
    mov ax,@data ; подготовка сегмента даных
    mov ds,ax
    mov ax, 0001h ; зададим первую цифру
    mov bx, 000Ah ; зададим вторую цифру
    xchg ax,cx ; в AL возвращается выведенный символ
               ; после int 21, так что сохраним
               ; ax в cx для выполнения задания
    call printStr
    xchg cx,bx
    call printStr
    xor ax,ax
    int 20h ; выход
    ;mov AX,4C00h
    ;int 21h
end start
