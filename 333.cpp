#include <iostream>

int main() {
    int x, y;
    std::cout << (std::cin >> x >> y, y >= -2 ? "Inside" : "Outside");
    
  return 0;
}
