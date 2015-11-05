.model small ;Модель памяти SMALL использует сегменты размером не более 64Кб
.stack 100h
.data
.code ;Начало сегмента кода

outSym proc ; для A...F
  add dl, 07h
  ret
outSym endp

prepNum proc ; подготовка символа из цифры
  add dl, 30h ; для 0...9
  cmp dl, 3ah ;
  jge outSym ; если цифра A...F - добавить 0x7
  ret
prepNum endp

print proc ; вывод символа на экран
  mov ah,02h ; 02 - вывод символа в stdout
  int 21h ; вызов прерывания
  ret
print endp

start: ;Выполнение программы
    mov ax,@data ; подготовка сегмента даных
    mov ds,ax
    mov ax, 0001h ; зададим первую цифру
    mov bx, 000Ah ; зададим вторую цифру
    mov dl, al ; передадим в DL первую цифру
    call PrepNum ; подготовим ее ASCII код
    call print ; выведем
    mov dl, 20h ; пробел
    call print
    mov dl, bl ; аналогично для второй цифры
    call PrepNum
    call print
    int 20h ; выход
end start
