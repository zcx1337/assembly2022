#include <stdio.h>
#include <conio.h>

int main (void)
{
   int aa;
   clrscr();

   int A[10]={2,1,2,3,4,5,6,7,8,9};
   int B[10]={1,1,0,0,0,0,0,0,0,0};
   A[0] = 2;
   printf ("\n ���祭�� ������ ॣ���஢ is, di = %x  %x ", _SI, _DI);

   asm {
	cld
	mov cx, 10
	lea si, A[0]
	lea di, B[0]
	push ds
	mov ax, es
	mov ds, ax
	rep movsw
	pop ds
   }
   printf ("\n ���祭�� ������ ॣ���஢ is, di = %x  %x ", _SI, _DI);
   printf ("\n �뢮� ���ᨢ� � ��᫥ ��ப���� ��।��");
   for (int i=0; i<10; i++)
   {
      printf (" \n  %d ", B[i]);
   }

   getch();
   return 0;
};
