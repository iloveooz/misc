#include <iostream>

int main() {
    int v, t, s;
    std::cin >> v;
    std::cin >> t;
    
    s = v * t % 109;
    std::cout << s;
return 0;
}
