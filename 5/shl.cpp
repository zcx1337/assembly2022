#include <iostream>

void shlStack(long long int, long long int&)
{
	__asm
	{
		mov edi, [ebp + 12]
		mov edx, [ebp + 8]
		mov ebx, [ebp + 16]
		
		shl edx, 1
		rcl edi, 1

		mov[ebx], edx
		mov[ebx + 4], edi
	}
}

void shlReg()
{
	__asm
	{
		mov edi, [esi + 4]
		mov edx, [esi]

		shl edx, 1
		rcl edi, 1

		mov[ebx], edx
		mov[ebx + 4], edi
	}
}

long long int OP;
long long int RES;

void shlGlobal()
{
	__asm
	{
		lea esi, OP
		mov edi, [esi + 4]
		mov edx, [esi]

		shl edx, 1
		rcl edi, 1

		lea ebx, RES
		mov[ebx], edx
		mov[ebx + 4], edi
	}
}

int main()
{
	const long long int op = 0x0000000000000003;

	long long int res = 1;
	shlStack(op, res);
	std::cout << res << '\n';

	res = 2;
	__asm
	{
		lea esi, op
		lea ebx, res
	}
	shlReg();
	std::cout << res << '\n';

	OP = op;
	RES = 3;
	shlGlobal();
	std::cout << RES << '\n';

	return 0;
}
