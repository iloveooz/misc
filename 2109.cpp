#include <iostream>
using namespace std;
int main(){
  int a, b, c, d, e;
  cin >> a >> b >> c >> d >> e;

  std::cout << e + 2 << ' ' << e + 4 << ' ' << e + 6 << std::endl;
  std::cout << e + d << ' ' << e + (e + d) << ' ' << e + (e + d) + (e + d) << std::endl;
  std::cout << e + (e - d) + 1 << ' ' << e + (e - d) + (e - d) + 3 << ' ' << e + (e - d) + (e - d) + (e - d) + 6 << std::endl;
  std::cout << e + d + c << ' ' << 2 * e + 2 * d + c << ' ' << 4 * e + 3 * d + 2 * c << ' ' << std::endl;
    
  return 0;   
 }
