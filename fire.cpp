#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

/// Greedy Alg. Decision.
bool validSeparation(int minSeparation, int numShells, const std::vector<int>& distances) {
  int shellCount = 1;
  int combinedSeparation = 0;
  for (int i = 0; i < (int)distances.size(); i++) {
    combinedSeparation += distances[i];
    if (combinedSeparation >= minSeparation) {
      shellCount++;
      combinedSeparation = 0;
    }
  }
  return shellCount >= numShells;
}

/// Search.
void search(int& bsf, int& minSep, int& nextIndex, int numShells, const std::vector<int>& distances) {  
  while (minSep <= bsf && nextIndex >= 0) {
    minSep += distances[nextIndex];
    nextIndex--;
  }
  if (minSep > bsf) {
    if (validSeparation(minSep, numShells, distances)) {
      bsf = minSep;
      search(bsf, minSep, nextIndex, numShells, distances);
    }
  }
}

/// Optimization.
int maxSeparation(int numShells, std::vector<int> distances) {
  int bsf = 1;
  int minSep;
  int maxIndex;
  while (numShells != 1 && !distances.empty()) {
    maxIndex = distances.size()-1;
    minSep = distances[maxIndex];
    int nextIndex = maxIndex - 1;
    search(bsf, minSep, nextIndex, numShells, distances);
    if (validSeparation(bsf + 1, numShells, distances)) {
      bsf++;
    }
    else {
      break;
    }
    for (int i = maxIndex; i > nextIndex; i--) {
      distances.pop_back();
    }
    numShells--;
  }
  return bsf;
}   

int main() {
  std::string data;
  int n, k;
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> n >> k;

  int d;
  std::vector<int> distances;
  for (int i = 0; i < n-1; i++) {
    std::getline(std::cin, data);
    ss.str(""); ss.clear();
    ss << data;
    ss >> d;
    distances.push_back(d);
  }

  for (int i = 0; i < k; i++) {
    std::getline(std::cin, data);
    ss.str(""); ss.clear();
    ss << data;
    ss >> d;
    std::cout << maxSeparation(d, distances) << std::endl;
  }

  return 0;
}
