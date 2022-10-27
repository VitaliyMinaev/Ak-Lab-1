#include <iostream>
#include <conio.h>


int FirstTask(int x = 3) {
    // Y = 2 * x^2 + (3*x) / (2^x);

    long X = 3;  // осередок пам'яті для аргументу
	long oldValue = 2, counterOfIteration = 0;
    long REZ[5]; // 7 осередків пам'яті для результатів

    int y = 0;

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

    return y;
}

int main()
{
    std::cout << "First task result: " << std::endl;
	FirstTask();

    return 0;
}