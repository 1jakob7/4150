#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

int dynamicMinPenalty(std::vector<int>& distances, int k, std::unordered_map<int, int> cache) {
  
}

int dynamicMinPenalty(std::vector<int>& distances) {
  
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
