#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Tree {

  class Node {
    
  public:
    int value;
    Node* left;
    Node* right;
    
    Node(int _value) {
      value = _value;
      right = NULL;
      left = NULL;
    }
  };

  Node *root;

  void insert(Node *current, int data) {
    if (data < current->value) {
      if (current->left != NULL) {
	insert(current->left, data);
      }
      else {
	current->left = new Node(data);
      }
    }
    else {
      if (current->right != NULL) {
	insert(current->right, data);
      }
      else {
	current->right = new Node(data);
      }
    }
  }

public:
  Tree(int data) {
    root = new Node(data);
  }

  void insertNewNode(int data) {
    insert(root, data);
  }
};


int countDifferentPrototypes(std::vector<std::vector<int>> &prototypes, int numProto, int numLayers) {
  std::vector<Tree> trees; 
  for (int p = 0; p < numProto; p++) {
    for (int l = 0; l < numLayers; l++) {
      if (l == 0) {
	trees.push_back(Tree(prototypes[p].at(l)));
      }
      else {
	trees.at(p).insertNewNode(prototypes[p].at(l));
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
