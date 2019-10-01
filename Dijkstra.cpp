#include <iostream>
#include <ctime>

#define SIZE 9

int main() {
	srand(static_cast<int>(time(nullptr)));

	int matrix[SIZE][SIZE]; // матрица связей
	int d[SIZE]; // минимальное расстояние
	int v[SIZE]; // посещенные вершины

	int temp, minindex, min;
	int begin_index = 0;

	setlocale(LC_ALL, "Russian");

	// Инициализация матрицы связей
	for (int i = 0; i < SIZE; i++) {
		matrix[i][i] = 0;
		for (int j = i + 1; j < SIZE; j++) {
			std::cout << "Введите расстояние (" << (i + 1) << " - " << (j + 1) << "): ";
			temp = rand() % 98 + 1;
			std::cout << temp << std::endl;
			matrix[i][j] = temp;
			matrix[j][i] = temp;
		}
	}

	// Вывод матрицы связей
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
				std::cout << matrix[i][j] << '\t';
		std::cout << std::endl;
	}

	//Инициализация вершин и расстояний
	for (int i = 0; i < SIZE; i++) {
		d[i] = 10000;
		v[i] = 1;
	}

	d[begin_index] = 0;

	// Шаг алгоритма
	do {
		minindex = 10000;
		min = 10000;

		for (int i = 0; i < SIZE; i++) {
			// Если вершину ещё не обошли и вес меньше min
			if ((v[i] == 1) && (d[i]<min)) { 
				// Переприсваиваем значения
				min = d[i];
				minindex = i;
			}
		}

		// Добавляем найденный минимальный вес к текущему весу вершины и сравниваем с текущим минимальным весом вершины
		if (minindex != 10000) {
			for (int i = 0; i < SIZE; i++) {
				if (matrix[minindex][i] > 0) {
					temp = min + matrix[minindex][i];
					if (temp < d[i]) {
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} 
	while (minindex < 10000);

	// Вывод кратчайших расстояний до вершин
	std::cout << '\n' << "Кратчайшие расстояния до вершин" << '\n';
	for (int i = 0; i < SIZE; i++)
		std::cout << d[i] << '\t';
	std::cout << std::endl;

	// Восстановление пути
	int ver[SIZE]; // массив посещенных вершин
	int end = 4; // индекс конечной вершины = 5 - 1
	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = d[end]; // вес конечной вершины

	while (end != begin_index) { // пока не дошли до начальной вершины
		for (int i = 0; i < SIZE; i++) // просматриваем все вершины
		if (matrix[end][i] != 0) { // если связь есть
			int temp = weight - matrix[end][i]; // определяем вес пути из предыдущей вершины
			if (temp == d[i]) { // если вес совпал с рассчитанным, значит из этой вершины и был переход
				weight = temp; // сохраняем новый вес
				end = i;       // сохраняем предыдущую вершину
				ver[k] = i + 1; // и записываем ее в массив
				k++;
			}
		}
	}

	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	std::cout << '\n' << "Вывод кратчайшего пути" << '\n';

	for (int i = k - 1; i >= 0; i--)
		std::cout << ver[i] << ' ';
	std::cout << std::endl;
	
	system("pause");
	return 0;
}
