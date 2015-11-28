; Функции WinAPI
extrn ExitProcess: PROC         ; завершение процесса
extrn MessageBoxA: PROC         ; вывод диалогового окна
extrn GetUserNameA:PROC         ; запрос имени пользователя
extrn GetComputerNameA: PROC    ; запрос имени компьютера
extrn GetTempPathA: PROC        ; запрос директории временных файлов
extrn GetVersionExA: PROC       ; запрос информации о версии и сборке ОС
extrn wsprintfA: PROC           ; форматированный вывод

; введем струтктуру для GetVersionExA
; в структуру запсываются размер всех данных,
; старшая и младшая версия системы и тип
; платформы
OSVERSIONINFO STRUCT
	dwOSVersionInfoSize DWORD ?
	dwMajorVersion DWORD ?
	dwMinorVersion DWORD ?
	dwBuildNumber DWORD ?
	dwPlatformId DWORD ?
	szCSDVersion BYTE 128 dup(?)
OSVERSIONINFO ends


; константы, задающие размеры для
; буферов различных запросов
; размеры взяты с MSDN
szMAX_COMP_NAME EQU 16
szUNLEN EQU 257
szMAX_PATH EQU 261

.data
    ; строка форматирования
	fmt db 'Username: %s',0ah,
	       'Computer name: %s', 0ah,
           'TMP Path: %s', 0ah,
           'OS version: %d.%d.%d', 0
    ; заголовок окна
	caption db 'Computer info!', 0
.code
Start PROC
    ; локальные переменные
	local msg[1024]:BYTE                   ; результирующая строка
    ; переменные возврата
	local _username[szUNLEN]:BYTE
	local _compname[szMAX_COMP_NAME]: BYTE
	local _temppath[szMAX_PATH]: BYTE
	local _version: OSVERSIONINFO
    ; переменная для передачи размера буфера по ссылке в ф-ции
    local _size: QWORD

    ; выравнивание стека
    sub rsp, 28h

    ; получение имени пользователя
	mov _size, szUNLEN
	lea rcx, _username
	lea rdx, _size
	call GetUserNameA

    ; получение имени машины
	mov _size, szMAX_COMP_NAME
	lea rcx, _compname
	lea rdx, _size
	call GetComputerNameA

    ; получение пути до $TEMP
	mov _size, szMAX_PATH
	lea rcx, _size
	lea rdx, _temppath
	call GetTempPathA

    ; очищение полей структуры
	xor al, al
	lea rdi, _version
	rep stos byte ptr [rdi]

    ; установка размера стурктуры
	mov rax, size _version
	mov _version.dwOSVersionInfoSize, eax

    ; получение информации о версии системы
	lea rcx, _version
	call GetVersionExA


    ; загрузка параметров wsprintf
	lea rcx, msg ; результат
	lea rdx, fmt ; строка форматирования
	lea r8, _username ; параметры для подставления
	lea r9, _compname

	lea rax, _temppath

    ; после 4 аргумента необходимо помещать значения параметров
    ; в стек
	mov qword ptr [rsp+20h], rax

	xor rax, rax
	mov eax, _version.dwMajorVersion
	mov qword ptr [rsp+28h], rax
	mov eax, _version.dwMinorVersion
	mov qword ptr [rsp+30h], rax
	mov eax, _version.dwBuildNumber
	mov qword ptr [rsp+38h]	, rax

	call wsprintfA

    ; вывод диалогового окна
	mov rcx, 0
	lea rdx, msg
	lea r8, caption
	mov r9, 0
	call MessageBoxA

    ; код выхода - 0
	xor rcx, rcx
    ; выход
	call ExitProcess
Start ENDP
end
