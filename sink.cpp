#include "sink.h"

Sink::Sink(std::map<std::string, int> _tolls, std::map<std::string, std::list<std::string>> _connections, std::vector<std::vector<std::string>> _trips) {
  tolls = _tolls;
  connections = _connections;
  trips = _trips;
  
  dfs();
}

void Sink::dfs() {
  ////clock = 1;
  // set every city's visited status to false for dfs
  for (std::map<std::string, int>::iterator itr = tolls.begin(); itr != tolls.end(); ++itr) {
    visited.insert(std::pair<std::string, bool>(itr->first, false));
  }
  // explore each city (vertex)
  for (std::map<std::string, bool>::iterator itr = visited.begin(); itr != visited.end(); ++itr) {
    if (!itr->second) { // city hasn't been visited
      explore(itr->first);
    }
  }
}

void Sink::explore(std::string city) {
  visited[city] = true;
  // check neighbors
  for (std::list<std::string>::iterator itr = connections[city].begin(); itr != connections[city].end(); ++itr) {
    if (!visited[*itr]) { // if a neighbor city hasn't been visited, explore it too
      explore(*itr);
    }
  }
  postvisit(city);
}

/// Assigns a post visit location.
void Sink::postvisit(std::string city) {
  post.push_back(city);
}

std::vector<std::string> Sink::findMinCosts() {
  for (unsigned int i = 0; i < trips.size(); i++) {
    std::string startCity = trips[i][0];
    std::string destCity = trips[i][1];
    
  }
  
  return {};
}
