#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>
#define Port8042 0x60
#define _tail si
#define _head di


void interrupt (*old)(...);

void put_in_buf(int scn)
{
	__asm {
		push ax

		mov ax, 0x40
		mov ds, ax
		mov _head, 0x1A
		mov _tail, 0x1C
		mov ax, [_tail]
		add ax, 2
		cmp al, 3Ch
		jle skip
		mov al, 1Eh
	}

	skip:
	__asm {
		mov cx, ax
		mov ax, [_head]
		cmp [_head], cx
		je end
	}
	char asc = 'n';
	_AL = scn;
	_AH = asc;
	__asm {
		mov _tail, [_tail]
		mov [_tail], ax
		mov _tail, 0x1C
		mov [_tail], cx
	}

end:
	__asm {
		pop ax
	}
	return;
}

void interrupt click(...)
{
	int scn;
	cout << "Click\n";
	__asm {
		in al,61H
		mov ah,al
		or al,80h
		out 61H,al
		push ax
		mov ax, 0000h
		in al, 60H
	}
	scn = _AL;
	put_in_buf(scn);
	__asm {
		pop ax
		xchg ah,al
		out 61H,al
		mov al,20H
		out 20H,al
	}
}

int main()
{
	clrscr();
	old = getvect(0x09);
	disable();
	setvect(0x09, click);
	enable();
	int toPrint = 1;
	int iAdres;
	char cScan,cAsci;
	do
	{
	 // Load registers  ds:si with value  0x40:0x1A
	__asm {
		push ds 	//
		push si         //  save registers
		push di         //
		mov ax,0x40     //
		mov ds,ax       // load segment
		mov si,0x1A     // load head pointer
		mov di,0x1C     // load tail pointer
	}
	wait_kbd:
	__asm {
		 mov ax,[si]     // Comparing pointers and waiting for press
		 cmp ax,[di]
		 je wait_kbd
	// load di with value 0x1C
	// compare pointers
	// read pointer
		 mov si,[si]
	}
	iAdres=_SI;
	// Read value from buffer
	// registers AL_ and  _AH comatain Scan -code ASCII-code
	__asm mov ax, [si]
	__asm pop di
	__asm pop si
	__asm pop ds
	cScan=_AL;
	cAsci=_AH;
	if (toPrint == 1) {
	printf("Adress = %x   Scan ­ = %d      ASCII = %d \n",iAdres,cScan,cAsci);
	toPrint = 0;
	}
	else {
		toPrint = 1;
	}
	} while(getch() != 1);
	setvect(0x09, old);
	return 0;
}
