#include <iostream>
#include <string>

class Critter {
	// Указываем. что следующие глобальные функции являются дружественными по отношению к классу Critter
	friend void Peek(const Critter& aCritter);
	friend std::ostream& operator <<(std::ostream& os, const Critter& aCritter);
public:
	Critter(const std::string& name = "");
private:
	std::string m_Name;
};

Critter::Critter(const std::string& name) : m_Name(name) {}

void Peek(const Critter& aCritter);

std::ostream& operator << (std::ostream& os, const Critter& aCritter);

int main() {
	Critter crit("Poochie");
	std::cout << "Calling Peek() to access crit's private data member.m Name;\n";
	Peek(crit);

	std::cout << "\nSending crit object to std::cout with the << operator;\n";
	std::cout << crit;
	system("pause");
	return 0;
}

// глобальная дружественная функция. которая может получать доступ ко всем членам объекта класса Critter
void Peek(const Critter& aCritter) {
	std::cout << aCritter.m_Name << std::endl;
}

// глобальная дружественная функция. которая может получать доступ ко всем членам объекта класса Critter
// перегруженный оператор <<, позволяющий отправить объект типа Critter в поток std::cout
std::ostream& operator << (std::ostream& os, const Critter& aCritter) {
	os << "Critter Object - ";
	os << "m_Name: " << aCritter.m_Name << std::endl;
	return os;
}
