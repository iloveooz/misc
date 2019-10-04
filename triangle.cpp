#include <iostream>
#include <cmath>
#include <ctime>

class triangle {
private:
	double _a, _b, _c;

	double angleA;
	double angleB;
	double angleC;

	double PI;
public:
	triangle() : _a(0), _b(0), _c(0) {}

	triangle(double aa, double bb) {
		PI = 3.14159265359;
		_a = aa;
		_b = bb;
		_c = sqrt(_a * _a + _b * _b);
	
		angleA = asin(_a / _c) / PI * 180;
		angleB = asin(_b / _c) / PI * 180;
		angleC = 180 - angleA - angleB;
	}

	void viewCatets() {
		std::cout << " a = " << _a << ';';
		std::cout << " b = " << _b << ';';
		std::cout << " c = " << _c << std::endl;
	}

	void viewAngles()	{
		std::cout << " A = " << angleA << ';';
		std::cout << " B = " << angleB << ';';	
		std::cout << " C = " << angleC << std::endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	srand(static_cast<unsigned int>(time(nullptr)));

	triangle ABC(3,4);
	
	ABC.viewCatets();
	ABC.viewAngles();

	system("pause");
	return 0;
}
