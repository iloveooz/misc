#include <iostream>

class Dog {
public:
	Dog() {}
};

int fun() {
	return 111;
}

int main() {
	int a; // lv
	Dog rex; // lv
	
	fun(); // rv
	Dog{}; // rv
	
	// lvalue ref -> lvalue
	int& b = a;
	
	// const lvalue ref -> rvalue
	const int& c = fun();
	
	// rvalue ref -> rvalue only!
	int&& d = std::move(a);
	return 0;
}
