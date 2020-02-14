#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

std::vector<std::string> generateReportBFS(std::vector<std::string> names, std::map<std::string, std::vector<std::string>> friends, std::string rumorStarter) {
  std::map<std::string, int> dist;
  std::map<std::string, std::string> prev;
  for (std::string n : names) {
    dist.insert(std::pair<std::string, int>(n, -1)); // -1 represents infinity
    prev.insert(std::pair<std::string, std::string>(n, "")); // currently, no previous rumor teller
  }
  dist.at(rumorStarter) = 0; // the rumor starter
  std::vector<std::string> report;

  if (friends.count(rumorStarter) < 1) {
    report.push_back(rumorStarter);
  }
  else {
    std::queue<std::string> q;
    q.push(rumorStarter);

    while (!q.empty()) {
      std::string curr = q.front();
      q.pop();
      for (std::string f : friends.at(curr)) {
	if (dist.at(f) == -1) {
	  q.push(f);
	  dist.at(f) = dist.at(curr) + 1;
	  prev.at(f) = curr;
	}
      }
      report.push_back(curr);
    }
  }
  
  std::vector<std::string> nCopy(names);
  std::sort(std::begin(nCopy), std::end(nCopy));
  for (std::string n : nCopy) {
    if (dist.at(n) == -1) {
      report.push_back(n);
    }
  }
  
  return report;
}

int main() {
  int n, f, r;
  std::string data;

  std::getline(std::cin, data);
  std::stringstream ss1(data);
  ss1 >> n;
  std::string name;
  std::vector<std::string> names;
  for (int i = 0; i < n; i++) {
    std::getline(std::cin, data);
    std::stringstream ss1(data);
    ss1 >> name;
    names.push_back(name);
  }
  
  std::getline(std::cin, data);
  std::stringstream ss2(data);
  ss2 >> f;
  std::string friend1, friend2;
  std::map<std::string, std::vector<std::string>> friends;
  for (int i = 0; i < f; i++) {
    std::getline(std::cin, data);
    std::stringstream ss2(data);
    ss2 >> friend1;
    ss2 >> friend2;
    if (friends.count(friend1) < 1) {
      friends.insert(std::pair<std::string, std::vector<std::string>>(friend1, {friend2}));
    }
    else {
      friends.at(friend1).push_back(friend2);
    }
    if (friends.count(friend2) < 1) {
      friends.insert(std::pair<std::string, std::vector<std::string>>(friend2, {friend1}));
    }
    else {
      friends.at(friend2).push_back(friend1);
    }
  }
  // get friend groups in alphabetical order
  for (std::string s : names) {
    if (friends.count(s) > 0) {
      std::sort(std::begin(friends.at(s)), std::end(friends.at(s)));
    }
  }

  std::getline(std::cin, data);
  std::stringstream ss3(data);
  ss3 >> r;
  std::string student;
  std::vector<std::string> rumors;
  for (int i = 0; i < r; i++) {
    std::getline(std::cin, data);
    std::stringstream ss3(data);
    ss3 >> student;
    rumors.push_back(student);
  }

  for (unsigned int i = 0; i < rumors.size(); i++) {
    std::vector<std::string> report = generateReportBFS(names, friends, rumors[i]);
    for (unsigned int j = 0; j < report.size() - 1; j++) {
      std::cout << report[j] << " ";
    }
    std::cout << report[report.size() - 1] << std::endl;
  }
  if (rumors.size() == 0) {
    std::cout << std::endl;
  }
  
  return 0;
}
