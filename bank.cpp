#include <unordered_map>
#include <iostream>
#include <sstream>
#include <map>

/// Returns the maximum amount of money that can be obtained from people in the bank queue, given how long
/// they are willing to wait in line.
int maxMoney(int T, std::unordered_map<int, std::map<int, int>>& deposits) {
  int max = 0;
  for (int slot = T; slot >= 0; slot--) {
    if (deposits.count(slot) > 0 && !deposits.at(slot).empty()) {
      int d = deposits.at(slot).rbegin()->first; // get the largest desposit from the time slot (maps are sorted internally)
      max += d; // add the deposit to the sum total
      
      // remove this person's deposit from the remaining time slots
      for (int i = slot; i >=0; i--) {
	if (deposits.at(i).count(d) > 0) {
	  if (deposits.at(i).at(d) == 1) { // only one person wanting to deposit this amount
	    deposits.at(i).erase(d);
	  }
	  else { // mulitple people wanting to deposit this amount
	    deposits.at(i).at(d)--;
	  }
	}
      }
    }
  }
  
  return max;
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

    // add the person's deposit amount to all time slots at or before their max waiting period
    for (int time = t; time >= 0; time--) {
      if (deposits.count(time) < 1) { // time slot is not yet present
        deposits.insert(std::pair<int, std::map<int, int>>(time, { {c, 1} }));
      }
      else { // time slot is present
        if (deposits.at(time).count(c) < 1) { // a (currently) unique deposit amount at that time
   	  deposits.at(time).insert(std::pair<int, int>(c, 1));
        }
        else { // another deposit of the same amount is present
	  deposits.at(time).at(c)++; // represents another person willing to deposit the same amount at that time
        }
      }
    }
  }

  std::cout << maxMoney(T, deposits) << std::endl;
  
  return 0;
}
