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

void SlavikFunc() {
	long X = 3;// осередок пам'яті для аргументу
	long i = 5;
	long six = 6;
	long REZ[5]; // 7 осередків пам'яті для ре-зультатів
	//(6^𝑥+12)/(5∙𝑥−8)

//
/*	3		32			, 57142857
	7		10368		, 44444
	11		7719086		, 553
	15		7017686337
	19		7			, 00413E+12*/

	_asm
	{

		lea ebx, REZ
		mov esi, i
		start :
		; (5∙𝑥−8)
			mov eax, 5
			mul X
			sub eax, 8
			; end of(5∙𝑥−8)
			; sending resukt to edi
			mov edi, eax

			; (6 ^ 𝑥 + 12)

			mov eax, 6
			; degree
			mov ecx, X
			dec ecx

			power_numerator :
		imul six
			loop power_numerator
			add eax, 12

			div edi
			mov dword ptr[EBX], EAX
			add EBX, 4
			add X, 4
			mov ecx, esi
			dec esi
			loop start



	} // закінчення ассемблерной вставки

	printf("Task #1\n");
	for (auto v : REZ)
		printf("%d ", v);

}

int main()
{
    std::cout << "First task result: " << std::endl;
	FirstTask();

    return 0;
}