#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <math.h>
#include <algorithm>

int dynamicMinPenalty(std::vector<int>& distances, int k, int max, std::unordered_map<int, int>& cache) {

  if (k == (int)distances.size()-1) {
    return 0;
  }

  if (cache.count(k) > 0) {
    return cache.at(k);
  }

  int minC = max;
  for (unsigned int j = k + 1; j < distances.size(); j++) {
    int cost = pow(400 - (distances[j] - distances[k]), 2);
    minC = std::min(minC, cost + dynamicMinPenalty(distances, j, max, cache));
  }

  cache.insert(std::pair<int, int>(k, minC));
  return minC;
  
}

int dynamicMinPenalty(std::vector<int>& distances) {
  std::unordered_map<int, int> cache;
  int max = pow(400 - (distances[distances.size()-1] - distances[0]), 2);
  return dynamicMinPenalty(distances, 0, max, cache);
}

int main() {
  std::string data;
  std::vector<int> distances;
  int n, miles;

  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> n;

  for (int i = 0; i <= n; i++) {
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> miles;
    distances.push_back(miles);
  }

  std::cout << dynamicMinPenalty(distances) << std::endl;

  return 0;
}
