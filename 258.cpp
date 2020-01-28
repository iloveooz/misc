#include <iostream>

int main() {
    int a;
    std::cin >> a;
    std::cout << 16 * (a / 16 % 2) << " + " << 8 * (a / 8 % 2) << " + " << 4 * (a / 4 % 2) << " + " << 2 * (a / 2 % 2) << " + " << 1 * (a / 1 % 2) << std::endl;
    return 0;
}
