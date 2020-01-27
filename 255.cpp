#include <iostream>

int main() {
    int a;
    std::cin >> a;
    
    std::cout << "8*" << a / 1000 % 10 << " + 4*" << a / 100 % 10 << " + 2*" << a / 10 % 10 << " + 1*" << a / 1 % 10 << " = " << 8 * a / 1000 % 10 + 4 * a / 100 % 10 + 2 * a / 10 % 10 + 1 * a / 1 % 10 << std::endl;
  
    return 0;
}
