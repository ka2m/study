; используем две процедуры WinAPI: вывод окна и выход
extrn ExitProcess: PROC
extrn MessageBoxA: PROC
.data
; зададим переменные
; название окна
caption db '64-bit hello!', 0

; сообщение диалога
message db 'Hello World!', 0
.code
Start PROC
  sub    rsp,28h      ; выравниванием стек на 40 байт
  mov    rcx, 0       ; родительское окно, в нашем случае
                      ; рабочий стол (0)
  lea    rdx, message ; адрес сообщения
  lea    r8,  caption ; адрес заголовка
  mov    r9d, 0       ; тип диалога: информационный с
                      ; кнопкой ОК
  call   MessageBoxA  ; вызов функции WinAPI для вывода диалога
  call ExitProcess    ; выход
Start ENDP
End
