#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

/// Generates a "report" of students in the order they recieved a rumor, starting from a given student.
std::vector<std::string> generateReportBFS(std::vector<std::string> names, std::map<std::string, std::vector<std::string>> friends, std::string rumorStarter) {
  std::map<std::string, int> dist;
  std::map<int, std::vector<std::string>> fDepths;
  for (std::string n : names) {
    dist.insert(std::pair<std::string, int>(n, -1)); // -1 represents infinity
  }
  dist.at(rumorStarter) = 0; // the rumor starter
  std::vector<std::string> report;
  report.push_back(rumorStarter);
  
  if (friends.count(rumorStarter) > 0) {
    std::queue<std::string> q;
    q.push(rumorStarter);
    while (!q.empty()) {
      std::string curr = q.front();
      q.pop();
      for (std::string f : friends.at(curr)) {
	if (dist.at(f) == -1) {
	  q.push(f);
	  dist.at(f) = dist.at(curr) + 1;
	  if (fDepths.count(dist.at(f)) < 1) {
	    fDepths.insert(std::pair<int, std::vector<std::string>>(dist.at(f), {f}));
	  }
	  else {
	    fDepths.at(dist.at(f)).push_back(f);
	  }
	}
      }
    }
  }

  // add every level of "friend tree" to the report, alphabetically sorted
  int depthCount = 1;
  while (fDepths.count(depthCount) > 0) {
    std::sort(std::begin(fDepths.at(depthCount)), std::end(fDepths.at(depthCount)));
    for (std::string s : fDepths.at(depthCount)) {
      report.push_back(s);
    }
    depthCount++;
  }

  // add remaining students with no friend connection to the rumor-starter
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

  // get all students
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

  // get all friendships
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

  // get all rumor-starters
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
