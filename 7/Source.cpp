#include <iostream>
using namespace std;

int main()
{
	float a = 1;
	float b = 3;
	float c = 5;
	float sum = 0;
	__asm
	{
		finit
		fld a
		fld b
		fld c
		fadd
		fadd
		fstp sum
	}
	cout << "1. sum = " << sum << endl;

	__asm
	{
		finit
		fstp sum
	}
	cout << "2. sum = " << sum << endl;

	int ctrl = 0x027F;         // do also with 0x027B;
	a = 5;
	b = 0;
	__asm
	{
		finit
		fldcw ctrl
		fld a
		fld b
		fdiv
		fstp sum
	}
	cout << "3. sum = " << sum << endl;

	return 0;
}
