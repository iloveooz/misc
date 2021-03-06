// Напишите программу, которая запрашивает натуральное число N (не более 100), 
// а далее последовательность из N чисел, и находит количество минимальных элементов последовательности.

#include <iostream>
#include <vector>
#include <algorithm>
int main() {
  std::size_t n;
  std::cin >> n;
  std::vector<int> v(n);
  for (auto& num:v) std::cin >> num;
  std::cout << count(v.begin(), v.end(), *min_element(v.begin(), v.end()));  
  return 0;
}
