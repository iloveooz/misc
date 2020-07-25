#include <iostream>
#include <memory> 

class Hello {
public:
	void say() {
		std::cout << "HI!" << std::endl;
	}
};

int main() {
	std::unique_ptr<Hello> hello(new Hello());
	
	hello->say();
	
	return 0;
}
	
