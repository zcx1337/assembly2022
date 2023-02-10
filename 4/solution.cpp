// main file(module) of cpp project in visual studio
#include <iostream>
#include <chrono>

const int arraySide = 4;

void printArray(int* array)
{
	for (size_t i = 0; i < arraySide; ++i) {
		for (size_t j = 0; j < arraySide; ++j) {
			std::cout << array[i * arraySide + j] << ' ';
		}
		std::cout << '\n';
	}
}

void initArrray(int* array)
{
	for (size_t i = 0; i < arraySide; ++i)
	{
		for (size_t j = 0; j < arraySide; ++j)
		{
			array[i * arraySide + j] = i * arraySide + j + 1;
		}
	}
}

int main()
{
	int array[arraySide][arraySide]; // array in stack (arraySide * arraySide * 4 byte in a line)

	const long long loopCount = 1E+7;

	std::chrono::steady_clock timer1;
	auto start = timer1.now();
	for (long long i = 0; i < loopCount; ++i);
	auto end = timer1.now();
	std::cout << "empty loop time in ms: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	start = timer1.now();
	for (long long i = 0; i < loopCount; ++i)
	{
		__asm {   // gcc, please
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
			sub eax, ebx
		}
	}
	end = timer1.now();
	std::cout << "1 loop time in ms: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	__asm {
		lea ebx, array
	}

	start = timer1.now();
	for (long long i = 0; i < loopCount; ++i)
	{
		__asm {
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
			sub eax, [ebx]
		}
	}
	end = timer1.now();
	std::cout << "2 loop time in ms: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	__asm {
		mov esi, 4
	}

	start = timer1.now();
	for (long long i = 0; i < loopCount; ++i)
	{
		__asm {
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
			sub eax, [ebx + 4 * esi + 2]
		}
	}
	end = timer1.now();
	std::cout << "3 loop time in ms: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	start = timer1.now();
	for (long long i = 0; i < loopCount; ++i)
	{
		__asm {
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
			sub[ebx], eax
		}
	}
	end = timer1.now();
	std::cout << "4 loop time in ms: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	initArrray(*array);          // send int*, not int(*)[4]
	std::cout << "array before fill1" << "\n";
	printArray(*array);
	__asm {
		lea esi, array
		add esi, 16
		mov ecx, 2				 // 2 of 4 rows are even 
		mov eax, 0			     // filler

		evenLoop:
			mov edi, 0           // index in row
			fillLine :
				mov [esi], eax
				add esi, 4
				inc edi
				cmp edi, 4
			jl fillLine          // jump if index < arraySide

			add esi, 16          // next even row
		loop evenLoop
	}
	std::cout << "\array after fill1" << "\n";
	printArray(*array);

	initArrray(*array);
	std::cout << "array before fill2" << "\n";
	printArray(*array);
	__asm {
		cld
		mov ebx, 2                 // 2 of 4 rows are even 
		lea edi, [array + 16]      // first even row
		evenLoop2:
		mov eax, 0                 // filler
			mov ecx, 4             // arraySide
			rep stosd              // fill row edi
			add edi, 16            // already shifted 16
			dec ebx
			cmp ebx, 0
		jne evenLoop2
	}
	std::cout << "\array after fill2" << "\n";
	printArray(*array);
	return 0;
}
