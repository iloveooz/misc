#include <iostream>

int main() {
    enum class Fruits {
        LEMON,
        KIWI
    };

    enum class Colors {
        PINK,
        GRAY
    };

    Fruits fruit = Fruits::LEMON;
    Colors color = Colors::PINK;

    if (fruit == color)
        std::cout << "fruit and color are equal\n";
    else
        std::cout << "fruit and color are not equal\n";

    std::cout << std::endl;
    system("pause");
    return 0;
}
