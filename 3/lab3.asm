; nasm 32bit (runlab3.sh)

%macro putchar 1 
    ; print dword register %1 (linux api)
    push eax
    push ebx
    push ecx
    push edx
    push %1         
    mov   eax, 4      ; __NR_write from asm/unistd_32.h (32-bit int 0x80 ABI)
    mov   ebx, 1      ; stdout fileno
    mov   ecx, esp    ; ecx now points to your char
    mov   edx, 1      ; edx should contain how many characters to print
    int   80h         ; sys_write(1, "A", 1)
    ; return value in EAX = 1 (byte written), or error (-errno)
    add esp, 2        ; restore esp if necessary
    pop edx
    pop ecx
    pop ebx
    pop eax
%endmacro

global _start

section .data
B dw 1, 2, 0, -5, 12, -45, 123, -1234, 30001
A dw 0 dup(9)

section .text
_start:

mov esi, B
mov edi, A
mov ecx, 9
copy_loop:
	mov ax, [esi]
	mov [edi], ax
	add esi, 2
	add edi, 2
	dec ecx
jnz copy_loop

mov esi, A
mov ecx, 9            ; size of array A
array_loop:
    mov eax, [esi]       ; get first element

    test ax, ax
    jns if_unsigned       ; if ax is not signed
        mov bx, '-'
        putchar bx
        neg ax

    if_unsigned:
    mov bx, 10            ; bx - divider
    xor di, di            ; di - for number of digits of ax

    div_loop:            
        xor dx, dx    ; no most significant word of pair dx:ax
        div bx        ; divide dx:ax by bx, remainder to dx
        push dx       ; dx - digit - to stack
        inc di	      ; one more digit
        cmp ax, 0     ; divide while ax != 0
    jnz div_loop

    print_digits_loop:
        pop ax
        add ax, '0'
        putchar ax
        dec di
    jnz print_digits_loop   ; if di != 0    
    
    mov bx, ' '
    putchar bx

    add esi, 2
dec ecx
jnz array_loop

mov bx, 10
putchar bx

; system exit
mov eax,1            
mov ebx,0            
int 80h
