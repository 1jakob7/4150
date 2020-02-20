#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

double getHighestFrac(std::map<int, std::vector<double>> corridors, int numIntersects) {
  std::vector<double> dist(numIntersects);
  std::vector<int> prev(numIntersects);
  // start dijkstra's alg
  for (std::pair<int, std::vector<double>> ele : corridors) {
    dist[ele.first] = -1; // because we're dealing with fractions, the path's value can't be < 0
    prev[ele.first] = -1;
  }
  dist[0] = 0; // always start at intersection 0

  std::priority_queue<int, std::vector<int>,std::greater<int>> pq; // 'vector' and 'greater' ensure min queue
  pq.push(0); // always start at intersection 0

  /// now, figure out how to handle intersections that have already been evaluated
  while (!pq.empty()) {
    int curr = pq.top();
    pq.pop();
    std::vector<double> connections = corridors.at(curr);
    for (unsigned int i = 0; i < connections.size(); i+=2) { // new corridor every 2 elements
      if (dist[connections[i]] > dist[curr] * connections[i+1]) { // comapring against fraction of current distance
	dist[connections[i]] = dist[curr] * connections[i+1];
	prev[connections[i]] = curr;
	pq.push(connections[i]);
      }
    }
  }
  
  return 0;
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
    std::map<int, std::vector<double>> corridors;
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

    std::cout << getHighestFrac(corridors, n) << std::endl;
    
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> n;
    ss >> m;
  }

  return 0;
}

    // std::map<int, std::vector<double>>::iterator it = corridors.begin();
    // for (std::pair<int, std::vector<double>> element : corridors) {
    //   std::cout << element.first << " ";
    //   std::vector<double> v = element.second;
    //   for (double d : v) {
    // 	std::cout << d << " ";
    //   }
    //   std::cout << std::endl;
    // }
