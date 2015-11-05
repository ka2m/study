.model small
.stack 100h
.code
start:
mov ah,3
mov cl,1
shr ah, cl
jc l1
mov dx, 0
jmp ex
l1:
    mov dx, 1
    jmp ex

ex:
mov ax, 4C00h
int 21h
end start
