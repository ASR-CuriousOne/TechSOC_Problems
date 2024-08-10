#include <iostream>
#include "./mathfuncs.h"

#define PRINT(x) std::cout << x << std::endl;

void PrintOperations(char* operations, int numOfOperations) {
	for (int i = 0; i < numOfOperations; i++)
	{
		char* temp = operations + 4 * i;
		std::cout << *(temp) << *(temp+1) << *(temp+2) << *(temp+3) << " - " << i + 1 << std::endl;
	}
}

int main()
{
	int option = 0;

	PRINT("Welcome To Calculator");
	bool exit = true;

	int ops;

	while(exit){

	std::cout << "Choose the function u want to perform\n";
	char operations[][4] = {"Add","Sub","Mul","Div","Mod","Fac","Sin","Cos","Tan","Log"};
	int numOfoperations = sizeof(operations) / sizeof(char[4]);
	PrintOperations((char*)operations, numOfoperations);
	std::cout << "Solve Quadratic-" << numOfoperations + 1 << std::endl;
	std::cout << "Type Anything else to exit" << "\n\n";
	std::cout << "Type the corresponding number: ";
	std::cin >> option;

	switch (option)
	{
	case 1:
		Adder();
		break;
	case 2:
		Subtract();
		break;
	case 3:
		Multiplication();
		break;
	case 4:
		Division();
		break;
	case 5:
		Mod();
		break;
	case 6:
		Factorial();
		break;
	case 7:
		Sine();
		break;
	case 8:
		Cos();
		break;
	case 9:
		Tan();
		break;
	case 10:
		Log();
		break;
	case 11:
		Quadratic();
		break;
		
	default:
		exit = false;
		break;
	}
	std::system("pause");
	}
	
}