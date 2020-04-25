#include <iostream>
#include <sstream>
#include <vector>

/// Greedy Alg.

/// Driver. Increase distance by 1 and try until it fails.
int maxSeparation() {

  return 0;
}

int main() {
  std::string data;
  int n, k;
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> n >> k;

  int d;
  std::vector<int> dist;
  for (int i = 0; i < n-1; i++) {
    std::getline(std::cin, data);
    ss.str(""); ss.clear();
    ss << data;
    ss >> d;
    dist.push_back(d);
  }

  while (std::getline(std::cin, data)) {
    if (data.empty()) break;
    ss.str(""); ss.clear();
    ss << data;
    ss >> d;
    //
  }

  return 0;
}
