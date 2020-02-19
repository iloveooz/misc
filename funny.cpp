#include <iostream>

int main() {
    for (int i = 1; i < 10; i++) {
        for (int k = 0; k < 10; k++) {
            for (int s = 0; s < 10; s++) {
                if (i != k && i != s && k != s) {
                    if ((100 * i + 10 * k + s) + (100 * i + 10 * s + k) == (100 * k + 10 * s + i)) {
                        std::cout << i << k << s << '+' << i << s << k << '=' << k << s << i << std::endl;
                    }
                }
            }
        }
    }
    return 0;
}
