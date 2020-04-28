#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

/// Greedy Alg.
int maxSeparation(int minSeparation, int numShells, const std::vector<int>& distances) {
  int shellCount = 1;
  int combinedSeparation = 0;
  
  for (int i = 0; i < (int)distances.size(); i++) {
    combinedSeparation += distances[i];
    if (combinedSeparation >= minSeparation) {
      shellCount++;
      combinedSeparation = 0;
    }
  }

  if (shellCount >= numShells) {
    return maxSeparation(minSeparation + 1, numShells, distances);
  }
  return minSeparation - 1;
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
  
  while (std::getline(std::cin, data)) {
    if (data.empty()) break;
    ss.str(""); ss.clear();
    ss << data;
    ss >> d;
    std::cout << maxSeparation(1, d, distances) << std::endl;
  }
  
  return 0;
}
