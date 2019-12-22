#include <iostream>

class Init {
	public:
		virtual void print() = 0;
};

class Base : public Init {
	public:
		void print() {
			std::cout << "Base!" << std::endl;
		}
};

class Deriv : public Base {
	public:
		void print() {
			std::cout << "Deriv!" << std::endl;
		}	
};

class Student : public Deriv {
	public:
		void print() {
			std::cout << "Student!" << std::endl;
		}
};

class Teacher : public Deriv {
	public:
		void print() {
			std::cout << "Teacher!" << std::endl;
		}
};

class Admin : public Student, public Teacher {
};

int main() {
	
	Student S;
	S.print();
	Deriv D;
	D.print();
	Base B;
	B.print();
	
	Admin A;
	
	A.print();
	
	return 0;
}
