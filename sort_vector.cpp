#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	setlocale(LC_ALL, "Russian");
	std::vector <int> k;

	k.push_back (22);
	k.push_back (11);
	k.push_back (4);
	k.push_back (100);
	k.push_back (23);
	k.push_back (12);
	k.push_back (24);
	k.push_back (15);
	k.push_back (400);
	k.push_back (10);

	std::vector <int > ::iterator p;

	std::cout << "Вывод неотсортированного вектора:\n";
	
	for (p = k.begin(); p < k.end(); p++) {
		std::cout << *p << ' ';
	}
	
	std::sort ( k.begin() , k.end());
	
	std::cout << "\nВывод отсортированного вектора:\n";
	
	for (p = k.begin(); p < k.end(); p++) {
		std::cout << *p << ' ';
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}
