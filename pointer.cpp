#include <iostream>

void changer(int* n) {
	(*n)++;
}

void changer2(int& x) {
	x++;
}

int main() {
	int x = 0;

	changer(&x);
	changer2(x);

	std::cout << x << std::endl;

	system("pause");
	return 0;
}
