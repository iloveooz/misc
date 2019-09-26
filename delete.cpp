#include <iostream>
#include <cmath>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	int n;
	std::cout << " n = ";
	std::cin >> n;

	const auto x = new float (n);
	
	std::cout << "Enter X"  <<  '\n';
	for (int i = 0; i < n; i++)
		std::cin >> x[i];

	for (int i = 0; i < n; )
		if (x[i] > 0) {
			for (int j = i; j < n - 1; j++)
				x[j] = x[j + 1];
			n--;
		}
		else
			i++;

	std::cout << "X(changed)" << '\n';
	for (int i = 0; i < n; i++)
		std::cout << x[i] << '\t';
	std::cout <<  std::endl;

	system("pause");
	return 0;
}
