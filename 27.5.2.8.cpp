#include <iostream>
#include <algorithm>

int main(){
  std::string s;
  std::cin >> s;
	std::sort(s.begin(), s.end());
  std::cout << s;
	return 0;
}
