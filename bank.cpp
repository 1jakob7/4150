#include <unordered_map>
#include <iostream>
#include <sstream>
#include <map>

int maxMoney(int T, const std::unordered_map<int, std::map<int, int>>& deposits) {

  return -1;
}

int main() {
  std::string data;
  int N, T, c, t;
  
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> N;
  ss >> T;

  std::unordered_map<int, std::map<int, int>> deposits; // (time, ($$$, count))
  for (int i = 0; i < N; i++) {
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> c;
    ss >> t;

    if (deposits.count(t) < 1) { // time slot is not yet present
      deposits.insert(std::pair<int, std::map<int, int>>(t, { {c, 1} }));
    }
    else { // time slot is present
      if (deposits.at(t).count(c) < 1) { // a (currently) unique deposit amount at that time
	deposits.at(t).insert(std::pair<int, int>(c, 1));
      }
      else { // another deposit of the same amount is present
	deposits.at(t).at(c)++; // represents another person willing to deposit the same amount at that time
      }
    }
  }

  std::cout << maxMoney(T, deposits) << std::endl;
  
  return 0;
}

/// deposits.at(*time*).rbegin() will return the largest deposit at that time slot
