#include <iostream>
#include <sstream>
#include <vector>
#include <map>



int main() {
  int n, f, r;
  std::string data;

  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> n;

  std::string name;
  std::vector<std::string> names;
  for (int i = 0; i < n; i++) {
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> name;
    names.push_back(name);
  }

  std::cout << names.at(1) << std::endl;
  
  return 0;
}
