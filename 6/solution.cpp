#include <stdio.h>
#include <dos.h>
#include <iostream.h>
#include <conio.h>


long long A = 125;
long long B = 0;


void interrupt(*old)(...);       // interrupt function pointer  

void interrupt handler1(...)     // custom interrupt function
{
	cout << "int 1" << endl;
	asm {
		lea si, A
		lea di, B

		mov ax, [si]             // exchange (for example)
		mov bx, [di]
		mov [di], ax
		mov [si], bx
	}
}


void interrupt handler2(...)
{
	cout << "int 2" << endl;
	asm {
		lea di, B                // inc B
		mov ax, [di]
		inc ax
		mov [di], ax
	}
	asm {
		mov ax, [bp+18]          // get IP from stack frame 
		add ax, 2                // skip division (/ 0)
		mov [bp+18], ax          // ready to return from handler2
	}
}


void main(void)
{
	clrscr();

	int usual = 0xf0;
	old = getvect(usual);
	disable();
	setvect(usual, handler1);
	enable();
	geninterrupt(usual);
	cout << "A = " << A << ", B = " << B << endl;
	setvect(usual, old);
	getch();

	int special = 0;
	old = getvect(special);
	setvect(special, handler2);
	int a = 1;
	a / 0;                                     // will loop if no lines 38-40
	setvect(special, old);
	cout << A << ' ' << B << '\n';
	getch();
}
