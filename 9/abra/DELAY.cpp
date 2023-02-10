#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>
#include <time.h>
#define Port8042 0x60


int main()
{
	clrscr();
	int isBlocked = 1;
	int iAdres;
	char cScan,cAsci;
	time_t tim0 = time(NULL);
	outp(0x60, 0xF5);
	do
	{
		printf("next cycle\n");
		time_t tim = time(NULL);
		printf("diff: %i\n", tim - tim0);
		if (((tim - tim0) >= 10) && (isBlocked == 1))
		{
			printf("UNLOCKED!!!\n");
			isBlocked = 0;
			outp(0x60, 0xF6);
			break;
		}
	} while(1);
	return 0;
}
