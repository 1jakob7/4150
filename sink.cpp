#include "sink.h"

/// Constructor.
Sink::Sink(std::map<std::string, int> _tolls, std::map<std::string, std::list<std::string>> _connections, std::vector<std::vector<std::string>> _trips) {
  tolls = _tolls;
  connections = _connections;
  trips = _trips;

  dfs();
}

/// Depth-first-search. You know the drill.
void Sink::dfs() {
  maxCost = 0;
  // set every city's visited status to false for dfs
  for (std::map<std::string, int>::iterator itr = tolls.begin(); itr != tolls.end(); ++itr) {
    visited.insert(std::pair<std::string, bool>(itr->first, false));
    maxCost += itr->second; // also calculate the cost of all tolls for the findMinCosts method
  }
  // explore each city (vertex)
  for (std::map<std::string, bool>::iterator itr = visited.begin(); itr != visited.end(); ++itr) {
    if (!itr->second) { // city hasn't been visited
      explore(itr->first);
    }
  }
}

/// Checks neighbors to see if they've been visited, and visits them if they have not.
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

/// Calculates the minimum cost of each trip.
std::vector<std::string> Sink::findMinCosts() {
  std::map<std::string, int> priceCalc;
  std::vector<std::string> tripCosts;
  for (unsigned int i = 0; i < trips.size(); i++) {
    std::string startCity = trips[i][0];
    std::string destCity = trips[i][1];
    if (startCity == destCity) { // the start and dest city are the same (no tolls)
      tripCosts.push_back("0");
    }
    else { // calculate the cost of the cheapest trip or discover there is no valid path
      priceCalc.clear(); // empty the map
      for (unsigned int j = 0; j < post.size(); j++) {
	if (destCity != post[j] && connections[post[j]].size() == 0) { // sink and not the dest
	  priceCalc.insert(std::pair<std::string, int>(post[j], maxCost + 1));
	}
	else if (destCity == post[j]) { // dest
	  priceCalc.insert(std::pair<std::string, int>(post[j], 0));
	}
	else {
	  std::string target = findLowestToll(connections[post[j]]);
	  priceCalc.insert(std::pair<std::string, int>(post[j], priceCalc[target] + tolls[target]));
	}
      }
      if (priceCalc[startCity] > maxCost) { // impossible path
	tripCosts.push_back("NO");
      }
      else {
	tripCosts.push_back(std::to_string(priceCalc[startCity]));
      }
    }
  }
  return tripCosts;
}

/// Out of all neighboring cities, finds the one that costs the least to travel to.
std::string Sink::findLowestToll(std::list<std::string> neighbors) {
  std::string target = "";
  int lowest = maxCost + 1;
  for (std::list<std::string>::iterator itr = neighbors.begin(); itr != neighbors.end(); ++itr) {
    if (tolls[*itr] < lowest) {
      lowest = tolls[*itr];
      target = *itr;
    }
  }
  return target;
}
