#include <iostream>

#define PRINT(x) std::cout << x << std::endl;
constexpr float PI = 3.141592653589793f;

float powerWithInt(float base, int exp) {
	float ans = 1.0f;
	for (int i = 0; i < exp; i++)
	{
		ans = base * ans;
	}
	return ans;
}

float Factorial(int input) {
	if (input < 1) {
		return 1;
	}
	return input * Factorial(input - 1);
}

void Factorial() {
	PRINT("Get factorial of a function: ");
	int a = 0;
	std::cin >> a;
	std::cout << Factorial(a);
}

float Exp(float input) {
	float result = 0;
	for (int i = 0; i < 30; i++)
	{
		result += powerWithInt(input, i) / Factorial(i);
	}
	return result;
}

float Sqrt(float input) {
	//Newton Raphson
	float result = 10;

	for (int i = 0; i < 30; i++)
	{
		result = result - (result * result - input) / (2 * result);
	}
	return result;
}

float Mod(float num, float mod) {
	if (num >= 0) {
		while (!(num < mod)) {
			num -= mod;
		}
	}

	else {
		while ((num < 0)) {
			num += mod;
		}
	}

	return num;
}

void Mod() {
	PRINT("Get Modulus of a number");
	float a, b;
	std::cout << "Dividend: ";
	std::cin >> a;
	std::cout << "Divisor: ";
	std::cin >> b;
	PRINT("Ans is: " << Mod(a,b));
}

void Adder() {
	PRINT("Add two numbers: ");
	float a, b;
	std::cout << "First Num: ";
	std::cin >> a;
	std::cout << "Second Num: ";
	std::cin >> b;
	PRINT("Ans is: " << a+b);

}

void Subtract() {
	PRINT("Subtract first number from second: ");
	float a, b;
	std::cout << "First Num: ";
	std::cin >> a;
	std::cout << "Second Num: ";
	std::cin >> b;
	PRINT("Ans is: " << b - a);
}

void Multiplication() {
	PRINT("Multiply two numbers: ");
	float a, b;
	std::cout << "First Num: ";
	std::cin >> a;
	std::cout << "Second Num: ";
	std::cin >> b;
	PRINT("Ans is: " << a * b);
}

void Division() {
	PRINT("Divide first by second: ");
	float a, b;
	std::cout << "First Num: ";
	std::cin >> a;
	std::cout << "Second Num: ";
	std::cin >> b;
	PRINT("Ans is : " << a / b);
}

void Sine() {
	float input,result = 0;
	std::cout << "Sin Of (in Degree): ";
	std::cin >> input;

	input = Mod(input, 360);
	input *= PI / 180.0f;

	for (int i = 0; i < 15; i++)
	{
		result += powerWithInt(input, 2 * i + 1) * powerWithInt(-1.0f, i) / Factorial(2 * i + 1);
	}
	PRINT(result);
}

void Cos() {
	float input, result = 0;
	std::cout << "Cos Of (in Degree): ";
	std::cin >> input;

	input = Mod(input, 360);
	input *= PI / 180.0f;

	for (int i = 0; i < 15; i++)
	{
		result += powerWithInt(input, 2 * i) * powerWithInt(-1.0f, i) / Factorial(2 * i );
	}
	std::cout << result;
}

void Tan() {
	float input , cos = 0;
	float sin = 0;
	std::cout << "Tan Of (in Degree): ";
	std::cin >> input;

	input = Mod(input, 360);
	input *= PI / 180.0f;

	for (int i = 0; i < 15; i++)
	{
		cos += powerWithInt(input, 2 * i) * powerWithInt(-1.0f, i) / Factorial(2 * i);
	}

	for (int i = 0; i < 15; i++)
	{
		sin += powerWithInt(input, 2 * i + 1) * powerWithInt(-1.0f, i) / Factorial(2 * i + 1);
	}

	PRINT(sin / cos);
	
}

void Log() {
	PRINT("Get Natural Log of a num: ");
	float a = 0;
	std::cin >> a;
	
	float result = 10;

	for (int i = 0; i < 30; i++)
	{
		result = result - (Exp(result) - a) / Exp(result);
	}

	PRINT(result);
}

void Quadratic() {
	PRINT("Type the coefficeints of quadratic equation");
	float a, b, c;
	a = 0;
	b = 0;
	c = 0;

	std::cout << "Coefficient of x^2: ";
	std::cin >> a;
	std::cout << "Coefficient of x: ";
	std::cin >> b;
	std::cout << "Constant term: ";
	std::cin >> c;

	if (a == 0) {
		if (b == 0) {
			PRINT("No solution for u :]");
		}
		else {
			std::cout << "x is: " << -c / b << std::endl;
		}

	}

	else {
		float determinant = b * b - 4 * a * c;
		
		if (determinant < 0) {
			std::cout << "One Solution of x is: " << -b / (2 * a) << "+" << Sqrt(-determinant) / (2 * a) << "i" << std::endl;
			std::cout << "One Solution of x is: " << -b / (2 * a) << "-" << Sqrt(-determinant) / (2 * a) << "i" << std::endl;
			
		}
		else {
			std::cout << "One Solution of x is:   " << (-b + Sqrt(determinant)) / (2 * a) << std::endl;
			std::cout << "Other Solution of x is: " << (-b - Sqrt(determinant)) / (2 * a) << std::endl;
		}
	}
}