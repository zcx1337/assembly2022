#include <iostream>

void mulStack(long long int, long long int, long long int&)
{
	__asm
	{
		mov esi, [ebp + 24]

		mov eax, [ebp + 8]
		mov ebx, [ebp + 16]
		mul ebx
		mov[esi], eax
		mov[esi + 4], edx

		mov eax, [ebp + 8]
		mov ebx, [ebp + 20]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx

		mov eax, [ebp + 12]
		mov ebx, [ebp + 16]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx

		mov eax, [ebp + 12]
		mov ebx, [ebp + 20]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
	}
}

void mulReg()
{
	__asm
	{
		push edx
		push ebx
		mov eax, [ebx]
		mov ecx, [edx]
		mul ecx
		mov[esi], eax
		mov[esi + 4], edx
		pop edx
		pop ebx

		push edx
		push ebx
		mov eax, [ebx]
		mov ebx, [edx + 4]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
		pop edx
		pop ebx

		push edx
		push ebx
		mov eax, [ebx + 4]
		mov ebx, [edx]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
		pop edx
		pop ebx

		push edx
		push ebx
		mov eax, [ebx + 4]
		mov ebx, [edx + 4]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
		pop edx
		pop ebx
	}
}

long long int OP1;
long long int OP2;
long long int RES;

void mulGlobal()
{
	__asm
	{
		lea ebx, OP1
		lea edx, OP2
		lea esi, RES
		push edx
		push ebx
		mov eax, [ebx]
		mov ecx, [edx]
		mul ecx
		mov[esi], eax
		mov[esi + 4], edx
		pop edx
		pop ebx
		push edx
		push ebx
		mov eax, [ebx]
		mov ebx, [edx + 4]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
		pop edx
		pop ebx
		push edx
		push ebx
		mov eax, [ebx + 4]
		mov ebx, [edx]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
		pop edx
		pop ebx
		push edx
		push ebx
		mov eax, [ebx + 4]
		mov ebx, [edx + 4]
		mul ebx
		adc[esi], eax
		adc[esi + 4], edx
		pop edx
		pop ebx
	}
}

int main()
{
	const long long int op1 = 0x0000000010000000;
	const long long int op2 = 0x0000000001000000;

	long long int res = 1;
	mulStack(op1, op2, res);
	std::cout << res << '\n';

	res = 2;
	__asm
	{
		lea ebx, op1
		lea edx, op2
		lea esi, res
	}
	mulReg();
	std::cout << res << '\n';

	OP1 = op1; OP2 = op2;
	RES = 3;
	mulGlobal();
	std::cout << RES << '\n';

	return 0;
}
