#include <iostream>
#include <sstream>
#include <vector>
#include <map>



int main() {
  int n, f, r;
  std::string data;

  std::getline(std::cin, data);
  std::stringstream ss1(data);
  ss1 >> n;
  std::string name;
  std::vector<std::string> names;
  for (int i = 0; i < n; i++) {
    std::getline(std::cin, data);
    std::stringstream ss1(data);
    ss1 >> name;
    names.push_back(name);
  }
  std::getline(std::cin, data);
  std::stringstream ss2(data);
  ss2 >> f;
  std::string friend1, friend2;
  std::map<std::string, std::vector<std::string>> friends;
  for (int i = 0; i < f; i++) {
    std::getline(std::cin, data);
    std::stringstream ss2(data);
    ss2 >> friend1;
    ss2 >> friend2;
    if (friends.count(friend1) < 1) {
      friends.insert(std::pair<std::string, std::vector<std::string>>(friend1, {friend2}));
    }
    else {
      friends.at(friend1).push_back(friend2);
    }
    //if()
  }
  

  //std::cout << names.at(1) << std::endl;
  
  return 0;
}
