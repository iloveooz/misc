#include <memory>
#include <iostream>

class SomeClass {
public:
    void sayHello() {
        std::cout << "Hello!" << std::endl;
    }

    ~SomeClass() {
        std::cout << "~SomeClass" << std::endl;
    }
};

int main() {
    std::weak_ptr<SomeClass> wptr;

    {
        auto ptr = std::make_shared<SomeClass>();
        wptr = ptr;

        if (auto tptr = wptr.lock()) {
            tptr->sayHello();
        } else {
            std::cout << "lock() failed" << std::endl;
        }
    }

    if (auto tptr = wptr.lock()) {
        tptr->sayHello();
    } else {
        std::cout << "lock() failed" << std::endl;
    }
}
