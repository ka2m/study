sys_exit        equ     1
sys_read        equ     3
sys_write       equ     4
stdin           equ     0
stdout          equ     1
stderr          equ     3

section .data
  welcome          db      "Hello, this is the clock program ", 0, 10
  welcome_len        equ     $-welcome
  clr    db 0x1b, "[2J", 0x1b, "[H"
  clr_len equ $ - clr

section .text

global  _start
_start:
  mov ecx, welcome
  mov edx, welcome_len
  call func_print
  mov ecx, clr
  mov edx, clr_len
  call func_print
  jmp func_exit

func_print:
    mov     eax, sys_write
    mov     ebx, stdout
    int     0x80
    ret
func_exit: 
    mov     eax, sys_exit
    xor     ebx, ebx
    int     0x80


