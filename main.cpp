#include <iostream>
#include <map>
#include <sstream>
#include <list>
#include <vector>

#include "sink.h"

int main() {
  std::string data;
  int numCities, numHighways, numTrips;

  // create a map that matches cities with their toll amounts
  std::map<std::string, int> tolls;
  std::getline(std::cin, data);
  std::stringstream ss1(data);
  ss1 >> numCities;
  std::string c;
  int t;
  for (int i = 0; i < numCities; i++) {
    std::getline(std::cin, data);
    std::stringstream ss1(data);
    ss1 >> c;
    ss1 >> t;
    tolls.insert(std::pair<std::string, int>(c, t));
  }

  // create an adjacency list that maps cities one can travel to from a particlar city
  std::map<std::string, std::list<std::string>> connections;
  std::map<std::string, std::list<std::string>>::iterator it;
  std::getline(std::cin, data);
  std::stringstream ss2(data);
  ss2 >> numHighways;
  std::string c1, c2;
  for (int i = 0; i < numHighways; i++) {
    std::getline(std::cin, data);
    std::stringstream ss2(data);
    ss2 >> c1;
    ss2 >> c2;
    it = connections.find(c1);
    if (it == connections.end()) { // graph does not already contain city 1
      connections.insert(std::pair<std::string, std::list<std::string>>(c1, std::list<std::string>()));
    }
    connections[c1].push_back(c2);
  }
  
  // create a 2d array of trips from one city to another
  std::vector<std::vector<std::string>> trips;
  std::getline(std::cin, data);
  std::stringstream ss3(data);
  ss3 >> numTrips;
  for (int i = 0; i < numTrips; i++) {
    std::getline(std::cin, data);
    std::stringstream ss3(data);
    ss3 >> c1;
    ss3 >> c2;
    trips.push_back({c1, c2});
  }

  return 0;
}

  // for (std::map<std::string, std::list<std::string>>::iterator p = connections.begin(); p != connections.end(); ++p) {
  //   std::cout << p->first;
  //   for (std::list<std::string>::iterator itr = p->second.begin(); itr != p->second.end(); ++itr) {
  //     std::cout << " " <<  *itr;
  //   }
  //   std::cout << std::endl;
  // }

  // for (std::map<std::string, int>::iterator p = tolls.begin(); p != tolls.end(); ++p) {
  //   std::cout << p->first << " " << p->second << std::endl;
  // }

  //  std::cout << trips[0][1];
