#include <iostream>

class Animal {
public:
	virtual void eat() {
		std::cout << "I'm eating generic food!" << std::endl;
	}
};

class Cat : public Animal {
public:
	void eat() {
		std::cout << "I'm eating a rat!" << std::endl;
	}
};

class SiberianCat : public Cat {
public:
	void eat() {
		std::cout << "I'm eating a Wiskas only!" << std::endl;
	}
};

void foo(Animal *animal) {
	animal->eat();
}

int main() {
	Animal *animal = new Animal;
	Animal *cat = new Cat;
	Animal *sCat = new SiberianCat;

	foo(animal);
	foo(cat);
	foo(sCat);

	system("pause");
	return 0;
}

