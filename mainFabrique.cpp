#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Абстрактные базовые классы всех возможных видов воинов
class Infantryman {
public:
	unsigned int health;
	virtual void info() = 0;
	virtual ~Infantryman() {}
};

class Archer {
public:
	unsigned int health;
	virtual void info() = 0;
	virtual ~Archer() {}
};
  
class Horseman {
public:
	unsigned int health;
	virtual void info() = 0;
	virtual ~Horseman() {}
};

class Catapult {
public:
	unsigned int health;
	virtual void info() = 0;
	virtual ~Catapult() {}
};

// Классы всех видов воинов Римской армии
class RomanInfantryman: public Infantryman {
public:
	RomanInfantryman() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "RomanInfantryman, health = " << health << std::endl;
	}
};

class RomanArcher: public Archer {
public:
	RomanArcher() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "RomanArcher, health = " << health << std::endl;
	}
};
  
class RomanHorseman: public Horseman {
public:
	RomanHorseman() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "RomanHorseman, health = " << health << std::endl; 
	}
};

class RomanCatapult: public Catapult {
public:
	RomanCatapult() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "RomanCatapult, health = " << health << std::endl; 
	}
};


// Классы всех видов воинов армии Карфагена
class CarthaginianInfantryman: public Infantryman {
public:
	CarthaginianInfantryman() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "CarthaginianInfantryman, health = " << health << std::endl;
	}
};

class CarthaginianArcher: public Archer {
public:
	CarthaginianArcher() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "CarthaginianArcher, health = " << health << std::endl;
	}
};

class CarthaginianHorseman: public Horseman {
public:
	CarthaginianHorseman() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "CarthaginianHorseman, health = " << health << std::endl;
	}
};

class CarthaginianCatapult: public Catapult {
public:
	CarthaginianCatapult() {
		health = rand() % 99 + 1;
	}
	void info() {
		std::cout << "CarthaginianCatapult, health = " << health << std::endl; 
	}
};

// Абстрактная фабрика для производства воинов
class ArmyFactory {
public:
	virtual Infantryman* createInfantryman() = 0;
	virtual Archer* createArcher() = 0;
	virtual Horseman* createHorseman() = 0;
	virtual Catapult* createCatapult() = 0;

	virtual ~ArmyFactory() {}
};


// Фабрика для создания воинов Римской армии
class RomanArmyFactory: public ArmyFactory {
public:
	Infantryman* createInfantryman() {
		return new RomanInfantryman;
	}
	Archer* createArcher() {
		return new RomanArcher;
	}
	Horseman* createHorseman() {
		return new RomanHorseman;
	}
	Catapult* createCatapult() {
		return new RomanCatapult;
	}
};


// Фабрика для создания воинов армии Карфагена
class CarthaginianArmyFactory: public ArmyFactory {
public:
	Infantryman* createInfantryman() {
		return new CarthaginianInfantryman;
	}
	Archer* createArcher() {
		return new CarthaginianArcher;
	}
	Horseman* createHorseman() {
		return new CarthaginianHorseman;
	}
	Catapult* createCatapult() {
		return new CarthaginianCatapult;
	}
};


// Класс, содержащий всех воинов той или иной армии
class Army {
public:
	Army(std::string name) {
		this->name = name;
	}
	~Army() {
		unsigned int i;

		for(i = 0; i < vi.size(); ++i)
			delete vi[i];
		
		for(i = 0; i < va.size(); ++i)
			delete va[i];
		
		for(i = 0; i < vh.size(); ++i)
			delete vh[i];

		for(i = 0; i < vc.size(); ++i)
			delete vc[i];
	}

	void info() {
		unsigned int i;

		std::cout << "vi = " << vi.size() << '\n';
		for(i = 0; i < vi.size(); ++i)
			vi[i]->info();

		std::cout << "va = " << va.size() << '\n';
		for(i = 0; i < va.size(); ++i)
			va[i]->info();

		std::cout << "vh = " << vh.size() << '\n';
		for(i = 0; i < vh.size(); ++i)
			vh[i]->info();

		std::cout << "vc = " << vc.size() << '\n';
		for(i = 0; i < vc.size(); ++i)
			vc[i]->info();
	}

	void small_info() const {
		std::cout << name << '\n';
		std::cout << "vi = " << vi.size() << '\n';
		std::cout << "va = " << va.size() << '\n';
		std::cout << "vh = " << vh.size() << '\n';
		std::cout << "vc = " << vc.size() << '\n';
	}

	std::string name;

	std::vector <Infantryman*> vi;
	std::vector <Archer*> va;
	std::vector <Horseman*> vh;
	std::vector <Catapult*> vc;
};
  
  
// Здесь создается армия той или иной стороны
class Game {
public:
	Army* createArmy(ArmyFactory& factory, std::string name) {
		auto p = new Army(name);
		for (unsigned int i = 0; i < rand() % 100; i++)
			p->vi.push_back(factory.createInfantryman());
		
		for (unsigned int i = 0; i < rand() % 70; i++)
			p->va.push_back(factory.createArcher());
		
		for (unsigned int i = 0; i < rand() % 50; i++)
			p->vh.push_back(factory.createHorseman());
		
		for (unsigned int i = 0; i < rand() % 10; i++)
			p->vc.push_back(factory.createCatapult());
		
		return p;
    }
	void fight(Army& rArmy, Army& cArmy){
		rArmy.small_info();
		cArmy.small_info();
	}
};


int main() {
	srand (time(nullptr));
    Game game;

    RomanArmyFactory ra_factory;
    CarthaginianArmyFactory ca_factory;
	
	std::string rName = "Roman Army";
    Army* ra = game.createArmy(ra_factory, rName);

	std::string cName = "Carthaginian Army";
    Army* ca = game.createArmy(ca_factory, cName);

    std::cout << "Roman army:" << std::endl;
    ra->info();

    std::cout << "\nCarthaginian army:" << std::endl;
    ca->info();

	std::cout << "FIGHT!" << '\n';

	game.fight(*ra, *ca);

	system("pause");
	return 0;
}
