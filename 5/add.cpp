#include <iostream>

void addStack(long long int, long long int, long long int&)
{
	__asm
	{
		mov esi, [ebp + 24]   // third arg is adress

		mov eax, [ebp + 8]
		mov ebx, [ebp + 16]
		add eax, ebx
		mov[esi], eax
		mov eax, [ebp + 12]
		mov ebx, [ebp + 20]
		adc eax, ebx
		mov[esi + 4], eax
	}
}

void addReg()
{
	__asm
	{
		mov eax, [ebx]
		mov ecx, [edx]
		add eax, ecx
		mov[esi], eax
		mov eax, [ebx + 4]
		mov ecx, [edx + 4]
		adc eax, ecx
		mov[esi + 4], eax
	}
}

long long int OP1;
long long int OP2;
long long int RES;

void addGlobal()
{
	__asm
	{
		lea ebx, OP1
		lea edx, OP2
		lea esi, RES
		mov eax, [ebx]
		mov ecx, [edx]
		add eax, ecx
		mov[esi], eax
		mov eax, [ebx + 4]
		mov ecx, [edx + 4]
		adc eax, ecx
		mov[esi + 4], eax
	}
}

int main()
{
	const long long int op1 = 0x0000FFFFFFFFFFFF;
	const long long int op2 = 0x0000000000000001;

	long long int res = 1;
	addStack(op1, op2, res);
	std::cout << res << '\n';

	res = 2;
	__asm
	{
		lea ebx, op1
		lea edx, op2
		lea esi, res
	}
	addReg();
	std::cout << res << '\n';

	OP1 = op1; OP2 = op2;
	RES = 3;
	addGlobal();
	std::cout << RES << '\n';

	return 0;
}
