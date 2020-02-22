#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <queue>

#include <fstream>
#include <stdlib.h>
#include <time.h>

typedef std::pair<double, int> corr; // used for priority queue value pairing

/// Uses a version of Dijkstra's algorithm to find the path of "least resistance". The starting value
/// of '1.0' should be as high as possible after running thru the maze.
double getHighestFrac(std::unordered_map<int, std::vector<double>> corridors, int numIntersects) {
  std::vector<double> dist(numIntersects);
  std::vector<int> prev(numIntersects);
  
  for (std::pair<int, std::vector<double>> ele : corridors) {
    dist[ele.first] = -1; ///
    prev[ele.first] = -1;
  }
  dist[0] = 1.0; // always start at intersection 0

  std::vector<bool> hasPopped(numIntersects); // used due to linear-time update operation for pq, and instead we include duplicates on the pq
  std::priority_queue<corr> pq;
  for (unsigned int i = 0; i < dist.size(); i++) {
    pq.push(std::make_pair(dist[i], i));
    hasPopped[i] = false;
  }

  while (!pq.empty()) {
    corr curr = pq.top();
    pq.pop();
    if (!hasPopped[curr.second]) {
      hasPopped[curr.second] = true;
      std::vector<double> connections = corridors.at(curr.second);
      for (unsigned int i = 0; i < connections.size(); i+=2) { // new corridor every 2 elements
        if (dist[connections[i]] < dist[curr.second] * connections[i+1]) { // comparing against fraction of current distance
	  dist[connections[i]] = dist[curr.second] * connections[i+1];
	  prev[connections[i]] = curr.second;
	  pq.push(std::make_pair(connections[i], dist[connections[i]]));
        }
      }
    }
  }
  return dist[numIntersects-1]; // the last intersection is always the exit
}

int main() {
  std::string data;
  int n, m, x, y;
  double f;
  
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> n;
  ss >> m;

  while (n != 0 && m != 0) {
    std::unordered_map<int, std::vector<double>> corridors;
    for (int i = 0; i < m; i++) {
      std::getline(std::cin, data);
      std::stringstream ss(data);
      ss >> x;
      ss >> y;
      ss >> f;
      if (corridors.count(x) < 1) {
        corridors.insert(std::pair<int, std::vector<double>>(x, {(double)y, f}));
      }
      else {
        corridors.at(x).push_back(y);
        corridors.at(x).push_back(f);
      }
      if (corridors.count(y) < 1) {
	corridors.insert(std::pair<int, std::vector<double>>(y, {(double)x, f}));
      }
      else {
	corridors.at(y).push_back(x);
	corridors.at(y).push_back(f);
      }
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    std::cout << getHighestFrac(corridors, n) << std::endl;
    
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> n;
    ss >> m;
  }

  return 0;
}

