#include <dos.h>
#include <conio.h>

#include <stdio.h>
#include <iostream.h>

void interrupt(*old)(...);

int a = 1;
int handler_place = 1;

void interrupt handler(...)
{
	int address = 0;
	char c = 0;
	asm {
		mov address, sp
	}
	cout << "interrupt: sp = " << address << ", a = "<< a << endl;
	c = getch();
	cout << "you pressed " << c << endl;
	if (c == 'q')
	{
		disable();
		setvect(handler_place, old);
		enable();
		cout << "stop debug" << endl;

		asm {
			pop ax
			xor ax, 100h
			push ax
		}
		//return from interrupt handler with TF = 0
	}
}	

void thread()
{
	for(int i = 0; i < 3; i++)
	{
    	a *= 2;
	}
	cout << "end of thread: a = " << a << endl;
}


void main(void)
{
	clrscr();
	cout << "start" << endl;

	old = getvect(handler_place);
	disable();
	setvect(handler_place, handler);
	enable();
	asm { 	// TF = 1
		pushf
		pop ax
		or ax, 100h
		push ax
		popf
	}
	thread();

	cout << "end" << endl;
	getch();
}
