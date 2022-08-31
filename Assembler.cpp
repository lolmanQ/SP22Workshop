// The task Assembler

#include <iostream>

extern "C" void PrintRes(int);
extern "C" int AddOne(int);

int main()
{
	int result;
	int a = 1, b = 5, c = 10, d = 20, e = 25;
	result = a + (b + c + d) - (a - b - c) * d + (e - (a - b));

	int r1;
	int r2;
	int r3;

	std::cout << result << std::endl;

	_asm 
	{
		MOV EAX, e
		ADD EAX, b
		SUB EAX, a
		MOV r1, EAX
		MOV EAX, a
		ADD EAX, b
		ADD EAX, c
		ADD EAX, d
		MOV r2, EAX
		MOV EAX, a
		SUB EAX, b
		SUB EAX, c
		MOV EDX, d
		MUL EDX
		MOV EBX, r2
		SUB EBX, EAX
		MOV EAX, r1
		ADD EAX, EBX
		MOV EBX, EAX

		PUSH EBX
		CALL AddOne
		pop EBX

		PUSH EAX
		CALL PrintRes
		pop eax
	};
}

void PrintRes(int res)
{
	std::cout << res << std::endl;
}

int AddOne(int originalValue)
{
	return originalValue + 1;
}
//EAX = r1
//EBX = r2
//ECX = r3
//EDX = r4

// a + (b + c + d) - (a - b - c) * d + (e - (a - b));

// (e-(a-b)) = v1
// r1 e + b - a
// 
// a+b+c+d = v2
// (a-b-c)*d = v3

//v2-v3+v1