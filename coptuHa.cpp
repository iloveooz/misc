// Найти значение суммы и адрес ячейки, где она
// хранится для определенных элементов под
// побочной диагональю марицы x[4][4]
// группа ИС-21

#include <iostream>
#include <cmath>

int ** createM(int size, int ch) {
	int ** mas = new int * [size];
	
	for (int i = 0; i < size; i++) {
		mas[i] = new int[size];
		for (int j = 0; j < size; j++) {
			if (ch == 1) {
				mas[i][j] = (rand() % 10) * (pow((-1), rand() % 2));
			} else {
				std::cout << "Bвeguтe (" << (i + 1) << ") (" << (j + 1) << ") элeмeнm мaccuвa - ";
				std::cin >> mas[i][j];
				std::cout << "Ok!" << std::endl;
			}
		}
	}
	return mas;
}

void printM(int ** mas, int size) {
	std::cout << "3agaнa мaтpuцa!" << std::endl;
	
	for (int i = 0; i < size; i++) {
		std::cout << '\t';
		for (int j = 0; j < size; j++) {
			if (mas[i][j] >= 0) 
				std::cout << " ";
			std::cout << mas[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int summa(int ** mas, int size) {
	int k = 0;
	int sum = 0;
	
	// суммирование
	for (int i = size - 1; i >= 1; i--) {
		for (int j = 1 + k; j < size; j++) {
			sum += mas[i][j];
		}
		k++;
	}
	return sum;
}

int main() {
	srand(time(nullptr));
	
	int size = 0;
	int ch = 0;
	int ** mas = nullptr;
	int sum = 0;
	
	std::cout << "\tOZZY elements presents" << std::endl;
	
	while (size <= 0 || size > 10) {
		std::cout << "Bвeguтe nopяgoк мaтpuцы (порядок <= 10) - ";
		std::cin >> size;
	}
	
	std::cout << "Ok!" << std::endl;
	
	while (ch != 1 && ch != 2) {
		std::cout << "Kaк зanoлнuть слyчаuно (1), c клавиатуры (2) - ";
		std::cin >> ch;
		
		switch (ch) { 
			case 1: 
				std::cout << "Ok, " << ch << " - aвтоматuческu." << std::endl; 
				break;
			case 2: 
				std::cout << "Ok, " << ch << " - c клавиатуры." << std::endl; 
				break;
			default: 
				std::cout << "Oшu6кa! " << std::endl; 
		}
	}
	
	mas = createM(size, ch);
	printM(mas, size);
	sum = summa(mas, size); // суммирование
	
	std::cout << "\t Cyмма nog no6oчнou guaroнaлью - " << sum << std::endl;
	std::cout << "\t Agpec мecтoнaxoжgeнuя cyммы   - " << &sum << std::endl;

	for (int i = 0; i < size; i++)
		delete mas[i];
	delete [] mas;
	
	return 0;
}
