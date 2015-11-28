;Макрос выделяет место под параметры в стеке и форсированно выравнивает его

;если максимальное число параметров 8, то argc- 8-4+8%2
;если 9, то 9-1+9%2
;то есть идет округление в большую сторону
;во всей программе r15 зарезервирован для хранения указателя на "старый" стек
;
STACKALLOC MACRO argc
	push r15
	mov r15, rsp
	and spl, 0f0h
	;стек должен быть выровнен на 16n
	sub rsp,8*4
	;т.о. при входе в вызываемую функцию стек будет выровнен на 16 байт
	;выделяем стек по соглашению, 32 байта под rcx, rdx, r8, r9
	;

	IF argc ;если arcg !=0
	;под параметры функций, максимальное число стековых параметров умноженное на 8
		sub rsp,8*argc
	ENDIF
ENDM

STACKFREE MACRO
	mov rsp,r15
	;восстанавливаем невыровненный указатель стека
	pop r15
ENDM

NULL_FIFTH_ARG MACRO
	mov qword ptr[rsp+20h], 0
ENDM

;объявление внешними используемых в данной программе функций
extern ExitProcess:PROC, lstrlenA:PROC, WriteConsoleA:PROC, ReadConsoleA:PROC, GetStdHandle:PROC

;макрозамены
STD_OUTPUT_HANDLE equ-11
STD_INPUT_HANDLE equ-10
;определяем данные
.data?
	hStdOutput dq ?
	hStdInput dq ?
.data
	invalidNumber db 'Invalid character in number!', 0
	exitMsg db  0ah, 'Press any key to exit', 0
	enterA db 'a=',0
	enterB db 'b=',0
	resultAB db 'a+b=',0

.code
	WaitInput PROC USES rcx rdx r8 r9
		LOCAL readStr:BYTE
		LOCAL bytesRead:DWORD
		STACKALLOC
		mov rcx, hStdInput        ;HANDLE hConsoleInput
		lea rdx, readStr       ;LPVOID IpBuffer
		mov r8, 1                ;DWORD nNumberOfCharsToRead
		lea r9, bytesRead       ;LPDWORD IpNumberOfCharsRead
		NULL_FIFTH_ARG

		call ReadConsoleA
		STACKFREE
		ret
	WaitInput ENDP

	;функция печатает строку в консоли
	;параметр 1 = указатель на строку
	;стек чистит вызываемая сторона

	PrintString PROC USES rax rcx rdx r8 r9 pStr:QWORD
		LOCAL bytesWritten:QWORD
		STACKALLOC 1

		mov rcx, pStr ;LPCTSTR IpString
		call lstrlenA

		mov rcx, hStdOutput       ;HANDLE hConsoleOutput
		mov rdx,pStr              ;const VOID*IpBuffer
		mov r8,rax                ;DWORD nNumberOfCharsToWrite
		lea r9, bytesWritten      ;LPDWORD IpNumberOfCharsWritten
		NULL_FIFTH_ARG

		call WriteConsoleA

		STACKFREE
		ret 8
	PrintString ENDP


	;rax=прочитанный signed long
	;r10=статус чтения (0-успех, 1 -неудача)
	;стек чистит вызываемая сторона
	;
	ReadSignedLong PROC USES rbx rcx rdx r8 r9
		LOCAL readStr[64]:BYTE
		LOCAL bytesRead:DWORD
		STACKALLOC 2

		mov rcx, hStdInput        ;HANDLE hConsoleInput
		lea rdx, readStr       ;LPVOID IpBuffer
		mov r8,64                ;DWORD nNumberOfCharsToRead
		lea r9,bytesRead       ;LPDWORD IpNumberOfCharsRead
		NULL_FIFTH_ARG

		call ReadConsoleA

		;читаем из консоли не больше 64 символов, включая символ знака, само число и спец-символы \r\n
		xor rcx,rcx          ;rcx=0
		mov ecx,bytesRead  ;rcx=bytesRead
		sub rcx, 2
		mov byte ptr readStr[rcx], 0    ;\r заменяем на NULL
		mov r8, 1             ;10 в степени 1 понадобится потом при умножении
		xor rbx, rbx          ;rbx=результат=0
		scan_next_char:      ;проход по прочитанной строчке
			;проверяем, чтобы символы были в диапазоне от '0'(30h) до'9'(39h)
			;если все верно, то вычитаем '0'(30h) и получаем один из десятков числа
			dec rcx
			cmp rcx, -1  ;rcx-счетчик, по которому мы идем в обратном порядке
						 ;в данном случае, мы проверяем не прошли ли мы самый первый символ строки
						 ;если да, то сканирование строки завершено

			je scanning_complete
			xor rax, rax           ;rax=0
			mov al, readStr[rcx] ;символ сканируемой строки в al
			cmp al,'-'            ;проверка знака
			jne eval         ;если нет,то перейти к positive

			neg rbx               ;отрицательное число
								  ;при этом, т.к. мы уже читаем первый символ, то оно уже записано в rbx
								  ;читали мы его как положительно, поэтому нужно его преобразовать neg=not(reg)+1

			jmp scanning_complete

			eval:
				cmp al, 39h             ;al<'0'
 				jg invalid_character   ;если да, то invalid_character

				cmp al, 30h             ;al>='0'&& al>'9'
				jl invalid_character   ;да, значит invalid_character
							   ;если al>='0'&&al<='9' - хорошее число
				sub al, '0'             ;преобразуем '0' в 0, '1' в 1и т.д.
				mul r8                 ;rax=al*r8(r8 - степень 10)
				add rbx, rax            ;складываем
				mov rax, 10             ;
				mul r8                 ;r8=r8*10
				mov r8, rax             ;в r8 следующая степень десятки
				jmp scan_next_char

		invalid_character:
			xor r10, r10
			mov r10, 1
			jmp exit

		scanning_complete:
			xor r10, r10
			mov rax,rbx
		exit:
			STACKFREE
			ret 8*2
	ReadSignedLong ENDP

	PrintSignedLong PROC USES rax rcx rdx r8 r9 number:QWORD
		LOCAL numberStr[22]:BYTE
		xor r8, r8             ;r8=0 счетчик позиции в numberStr
		mov rax, number        ;rax = число для вывода
		btc number, 63         ;знаковый бит нашего числа копируем в carry
		jnc pos_part    ;у нас отрицательное число?
		mov numberStr[r8], '-' ;если да, то выводим минус
		neg rax               ;теперь делаем из данного числа положительное
		inc r8
		pos_part:
			mov rbx,10            ;rbx - делитель
			;делим число на 10 и складываем остатки в стек,чтобы потом записать их в строку в обратном порядке
			xor rcx,rcx           ;rсx - счетчик прочитанных чисел=0
			next:
				xor rdx,rdx
				;rdx обнуляем т.к. следующий div делит rdx:rax на rbx
				div rbx              ;rdx:rax / rbx. частное rax, остаток rdx
				add dl,'0'           ;преобразуем 0 в '0', 1 в '1' и т.д.
				push rdx             ;кладем символ в стек
				inc rcx              ;rcx++, прочитали еще один символ
				test rax,rax         ;целая часть от деления =0?
				je reverse           ;если ла.юто мы закончили собирать остатки
				jmp next
			reverse:
				pop rdx
				mov numberStr[r8],dl
				inc r8
				loop reverse

			mov numberStr[r8],0       ;конец строки

			lea rax,numberStr
			push rax
			call PrintString          ;печатаем numberStr

			ret 8                   ;чистим стек от одного параметра
	PrintSignedLong ENDP


	Start PROC                       ;вход в программу
		STACKALLOC

		mov rcx, STD_OUTPUT_HANDLE   ;DWORD nStdHandle
		call GetStdHandle            ;получаем Handle вывода
		mov hStdOutput, rax

		mov rcx, STD_INPUT_HANDLE    ;DWORD nStdHandle
		call GetStdHandle            ;получаем Handle ввода
		mov hStdInput, rax

		lea rax, enterA              ;выводим строку "а="
		push rax
		call PrintString

		call ReadSignedLong          ;читаем введенное число
		cmp r10, 0                  ;проверка числа
		jne invalid_character        ;r10!=0 ?, переход к invalid_character

		mov r8, rax                  ;сохраняем а в r8

		lea rax, enterB              ;выводим строку "b="
		push rax
		call PrintString

		call ReadSignedLong          ;читаем введенное число
		cmp r10, 0                  ;проверка числа
		jne invalid_character        ;r10!=0 ?, переход к invalid_character

		add r8, rax						; r8 = a + b

		lea rax, resultAB				; выводим строчку "a + b = "
		push rax
		call PrintString

		push r8
		call PrintSignedLong			; выводим a + b

		mov rcx, 0					; UINT uExitCode
		jmp exit

		invalid_character:
			lea rax, invalidNumber		; печатаем сообщение о неверном введении числа
			push rax
			call PrintString
			mov rcx, 1
			jmp exit

		exit:
			lea rax, exitMsg
			push rax
			call PrintString
			call WaitInput

			call ExitProcess
Start ENDP
end
