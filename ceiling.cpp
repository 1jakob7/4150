#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int countDifferentPrototypes(std::vector<std::vector<int>> &prototypes) {

  return 0;
}

int main (int argc, char *argv[]) {
  std::string data;
  int numProto;
  int numLayers;

  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> numProto;
  ss >> numLayers;

  int val;
  int pCount = 0;
  std::vector<std::vector<int>> prototypes;
  while (pCount < numProto) {
    int lCount = 0;
    std::getline(std::cin, data);
    std::stringstream ss(data);
    std::vector<int> p;
    while (lCount < numLayers) {
      ss >> val;
      p.push_back(val);
      lCount++;
    }
    prototypes.push_back(p);
    pCount++;
  }

  std::cout << countDifferentPrototypes(prototypes) << std::endl;
}
