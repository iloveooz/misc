#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<std::string> inventory;

	inventory.emplace_back("sword");
	inventory.emplace_back("armor");
	inventory.emplace_back("shield");

	std::cout << "You have " << inventory.size() << " items. \n";
	std::cout << "\nYour items: \n";
	for (unsigned int i = 0; i < inventory.size(); ++i) {
		std::cout << inventory[i] << std::endl;
	}

	std::cout << "\nYou trade your sword for a battle axe. ";
	inventory[0] = "battle axe";

	std::cout << "\nYour items;\n";
	for (unsigned int i =0; i < inventory.size(); ++i) {
		std::cout << inventory[i] << std::endl;
	}

	std::cout << "\nThe item name '" << inventory[0] << "' has ";
	std::cout << inventory[0].capacity() <<" letters in it.\n";
	std::cout << "\nYour shield is destroyed in a fierce battle ";

	inventory.pop_back();
	
	std::cout << "\nYour items;\n";

	for (unsigned int i = 0; i < inventory.size(); ++i) {
		std::cout << inventory[i] << std::endl;
	}
	std::cout << "\nYou were robbed of all of your possessions by a thief.";

	inventory.clear();

	if (inventory.empty()) {
		std::cout << "\nYou have nothing. \n";
	}
	else {
		std::cout << "\nYou have at least one item.\n";
	}

		system("pause");
	return 0;
}
