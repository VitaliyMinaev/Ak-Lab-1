#include <iostream>
#include <conio.h>

// Y = 2 * x^2 + (3*x) / (2^x);
void FirstTask(int x = 3) {
	long X = x;  // осередок пам'яті для аргументу
	long oldValue = 2, counterOfIteration = 0;
    long REZ[5]; // 7 осередків пам'яті для результатів

    _asm
    {
        lea EBX, REZ         				  ; завантаження адреси результатів в регістр EBX

        mov ECX, 5                            ; лічильник кількості повторень циклу

	startmainloop:
		cmp counterOfIteration, ECX
		jae exitmainloop

		mov EAX, 2                            ; EAX = 2
		mov ECX, 1

	startpowerloop:							  ; EAX = 2 ^ x => loop
		cmp ecx, X
		jae exitpowerloop
		mul oldValue
		inc ECX
		jmp startpowerloop

	exitpowerloop:

		mov ECX, 5							  ; лічильник кількості повторень циклу

		mov EDI, eax						  ; Sending result to EDI => EDI = 2 ^ x

		mov EAX, 3							  ; EAX = 3
		mul X								  ; EAX = 3 * x

		div EDI								  ; EAX = (3*x)/(2^x)
		mov EDI, EAX						  ; EDI = (3 * x) / (2 ^ x)

		mov EAX, 2							  ; EAX = 2
		mul X								  ; EAX = 2 * X
		mul X							      ; EAX = 2 * X^2

		add EAX, EDI						  ; EAX = 2 * X ^ 2 + (3 * x) / (2 ^ x) => Final result

        mov dword ptr[EBX], EAX               ; пересилання результату в пам'ять
        add EBX, 4                            ; збільшення адреси результатів
        add X, 2                              ; збільшення аргументу на 2
		
		inc counterOfIteration
		jmp startmainloop

	exitmainloop:

    }

    for (int i = 0; i < 5; ++i) {
        std::cout << "Result " << i + 1 << ": " << REZ[i] << std::endl;
    }
}

// a(n) = 5 ^ n + 8 * n
void SecondTask() {
	long n = 0, result = 0, oldValue = 5;

	_asm
	{
	startmainloop :
		mov ECX, 20000
		cmp result, ECX
		jae exitmainloop

		add n, 1; збільшення аргументу на 1

		mov EAX, 8							  ; EAX = 8
		mul n								  ; EAX = 8 * n

		mov EDI, EAX						  ; Sending result to EDI => EDI = 8 * n

		mov EAX, 5							  ; EAX = 5
		mov ECX, 1							  ; ECX = 1

	startpowerloop:							  ; EAX = 5 ^ n = > loop
		cmp ecx, n
		jae exitpowerloop
		mul oldValue
		inc ECX
		jmp startpowerloop

	exitpowerloop :

		add EAX, EDI						   ; Final result => 5 ^ n + 8 * n
		mov result, EAX						   ; n => Final result
		
		jmp startmainloop

	exitmainloop :
	}

	std::cout << "Result: " << n << std::endl;
}

/*
У пам'яті заданий масив з 10 елементів. Помістити в регістр EAX
мінімальний елемент масиву, а в регістр EDX його адресу в пам'яті.
*/
void ThirdTask() {
	long arraySize = 10;
	long arr[10] = { 3, 5, 21, 51, 21, 5, 14, 1, 3, 17 };

	for (auto item : arr) {
		std::cout << item << " ";
	}

	std::cout << std::endl;

	long minValue = arr[0], minValueAddress = 0;

	_asm
	{
		lea EBX, arr					       ; Ініціалізація елементів
		mov ECX, 0

	startarrayloop:
		cmp ECX, arraySize					   ; ECX => iteration counter
		jae exitarrayloop					   ; if(ECX > arraySize) => exit loop

		mov eax, arr[ECX*4]					   ; EAX => current element of array; EAX = arr[ECX]
		mov ebx, arr[ECX]					   ; EBX => address of current element

		cmp minValue, EAX					   ; if (minValue > EAX) = > minValue = EAX
		jg less
	continueloop:
		
		add ECX, 1							   ; ECX += 1

		jmp startarrayloop

	less :									   ; minValue = EAX and minValueAddress = ebx
		mov minValue, eax
		mov minValueAddress, ebx
		jmp continueloop

	exitarrayloop:

		mov EAX, minValue					   ; EAX = minValue
		mov EDX, ebx						   ; EDX = ebx = minValueAddress
	}

	std::cout << "Min value of array: " << minValue << "\n" 
		<< "Address of min value: " << minValueAddress << std::endl;
}

int main()
{
    std::cout << "First task result: " << std::endl;
	FirstTask();

	std::cout << std::endl;

	std::cout << "Second task result: " << std::endl;
	SecondTask();

	std::cout << std::endl;

	std::cout << "Third task result: " << std::endl;
	ThirdTask();

    return 0;
}