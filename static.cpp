#include <iostream>

class Critter {
public:
	static int s_Total;
	Critter(int hunger = 0);
	int GetHunger() const;
	void SetHunger(int hunger);
	static int GetTotal();
private:
	int m_Hunger;
};

Critter::Critter(int hunger): m_Hunger(hunger) {
	++s_Total;
	std::cout << "A new critter has been born!" << std::endl;
}

int Critter::GetHunger() const {
	return m_Hunger;
}

void Critter::SetHunger(int hunger) {
	if (hunger < 0) {
		std::cout << "You can't set а critter's hunger to а negative number.\n\n";
	}
	else {
		m_Hunger = hunger;
	}
}

int Critter::s_Total = 0;

int Critter::GetTotal() {
	return s_Total;
}

int main() {
	Critter crit(5);
	//std::cout<<crit.m_Hunger: // недопустимо. член m_Hunger является закрытым!
	std::cout << "Calling GetHunger(): "<< crit.GetHunger() << "\n\n";
	std::cout << "Calling SetHunger() with -1.\n";
	crit.SetHunger(-1);
	std::cout << "Calling SetHunger() with 9.\n";
	crit.SetHunger(9);
	std::cout << "Calling GetHunger(): "<< crit.GetHunger() << "\n\n";

	std::cout << "The total number of critters is: ";
	std::cout << Critter::s_Total << "\n\n";
	Critter critl, crit2, critЗ, crit4, crit5, crit6;
	std::cout << "\nThe total number of critters is: ";
	std::cout << Critter::GetTotal() << "\n";

	system("pause");
	return 0;
}
