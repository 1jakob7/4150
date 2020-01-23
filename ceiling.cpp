#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Tree {
  
public:
  int value;
  Node* left;
  Node* right;
  
  Node(int _value) {
    value = _value;
    Node* right = NULL;
    Node* left = NULL;
  }
};


int countDifferentPrototypes(std::vector<std::vector<int>> &prototypes, int numProto, int numLayers) {
  for (int i = 0; i < numLayers; i++) {
    for (int j = 0; j < numProto; j++) {
      if (j == 0) {
	Node  
      }
    }
  }
  
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

  std::cout << countDifferentPrototypes(prototypes, numProto, numLayers) << std::endl;
}
