#include <iostream>
#include <sstream>
#include <vector>

std::string findMajorGalaxy(std::vector<long> xCords, std::vector<long> yCords) {

  return "";
}

int main(int argc, char *argv[]) {
  std::string data;
  long d, k;
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> d;
  ss >> k;
  
  std::vector<long> xCords;
  std::vector<long> yCords;
  int kCount = 0;
  long val;
  while (kCount < k) {
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> val;
    xCords.push_back(val);
    ss >> val;
    yCords.push_back(val);
    kCount++;
  }

  std::cout << findMajorGalaxy(xCords, yCords) << std::endl;
}
