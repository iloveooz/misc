#include <iostream>
#include <string>
#include <vector>

class Critter {
public:
	Critter(const std::string& name = "");
	std::string GetName() const;
private:
	std::string m_Name;
};
	
inline std::string Critter::GetName() const {
	return m_Name;
}

Critter::Critter(const std::string& name) : m_Name(name) {}

class Farm {
public:
	Farm(int spaces = 1);
	void Add(const Critter& aCritter);
	void RollCall() const;
private:
	std::vector<Critter> m_Critters;
};

Farm::Farm(int spaces) {
	m_Critters.reserve(spaces);
}

void Farm::Add(const Critter& aCritter) {
	m_Critters.push_back(aCritter);
}

void Farm::RollCall() const {
	for(std::vector<Critter>::const_iterator iter = m_Critters.begin();	iter != m_Critters.end(); ++iter) { 
		std::cout << iter->GetName() << " here. \n";
	}
}

int main() {
	Critter crit("Poochie");
	std::cout << "Me critter's name is " << crit.GetName() << std::endl;
	std::cout << "\nCreating critter farm.\n";
	Farm myFarm(3);
	std::cout << "\nAdding three critters to the farm.\n";
	myFarm.Add(Critter("Moe"));
	myFarm.Add(Critter( "Larry"));
	myFarm.Add(Critter( "Curly"));
	std::cout << "\nCalling Roll...\n";
	myFarm.RollCall();
	system("pause");
	return 0;
}
