#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// Handles BST creation, as well as comparisons between two trees.
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

  bool isSame(Node* aCurrent, Node* bCurrent) {
    if (aCurrent != NULL && bCurrent != NULL) {
      return (isSame(aCurrent->right, bCurrent->right)
	      && isSame(aCurrent->left, bCurrent->left));
    }
    else if (aCurrent == NULL && bCurrent == NULL) {
      return true;
    }
    else {
      return false;
    }
  }

public:
  Tree(int data) {
    root = new Node(data);
  }

  void insertNewNode(int data) {
    insert(root, data);
  }

  bool isSameStructure(Tree other) {
    return isSame(root, other.root);
  }
};

/// Tests a list of trees for structual differences (how they would be constructed visually)
/// and returns the number of different "designs".
int countDifferentPrototypes(std::vector<std::vector<int>> &prototypes, int numProto, int numLayers) {
  if (prototypes.size() == 1) {
    return 1;
  }

  // take the input data and construct a list of trees
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
  
  int numDiff = 0;
  bool hasMatch[numProto];
  for (int i = 0; i < numProto; i++) {
    hasMatch[i] = false;
  }
  // tests trees against each other, and skips trees that are already matched with a previous
  for (int p = 0; p < numProto - 1; p++) {
    if (hasMatch[p] == false) {
      for (int i = p + 1; i < numProto; i++) {
        if (hasMatch[i] == false && trees[p].isSameStructure(trees[i])) {
	  hasMatch[p] = true;
	  hasMatch[i] = true;
        }
      }
      numDiff++;
    }
  }
  // check the final prototype since the loop skips it's final contribution
  if (hasMatch[numProto-1] == false) {
    numDiff++;
  }
  
  return numDiff;
}

int main (int argc, char* argv[]) {
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
  // take in the specified number of prototypes
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

  return 0;
}
