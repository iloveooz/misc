// make_pair example
#include <utility>      // std::pair
#include <iostream>     // std::cout

class MyString : public std::string {
	
};

int main() {
	std::pair <std::string, int> andy;
	std::pair <std::string, int> bill;

	andy = std::make_pair("Andy", 28);
	bill = std::make_pair("Bill", 25);

	std::cout << "FP: " << andy.first.data() << ", " << andy.second << '\n';
	std::cout << "SP: " << bill.first.data() << ", " << bill.second << '\n';

	system("pause");
	return 0;
}
