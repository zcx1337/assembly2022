#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>
#define Port8042 0x60

int main()
{
	clrscr();
	char symb;
	symb = getchar();
	while (symb != 'q')
	{
		if (symb == 'g' || symb == 'G')
		{
			outp(0x60, 0xED);
			for (int i = 0; i < 4000; i++);
			outp(0x60, 0x04);
		}
		if (symb == 'h' || symb == 'H')
		{
			outp(0x60, 0xED);
			for (int i = 0; i < 4000; i++);
			outp(0x60, 0x02);
		}
		symb = getchar();
	}
	return 0;
}
