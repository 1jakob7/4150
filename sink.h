#ifndef SINK_H
#define SINK_H

#include <map>
#include <list>
#include <vector>

class Sink
{
 private:
  std::map<std::string, int> tolls;
  std::map<std::string, std::list<std::string>> connections;
  std::vector<std::vector<std::string>> trips;
  
  int clock;
  std::map<std::string, bool> visited;
  std::vector<std::string> post;
  
 public:
  Sink(std::map<std::string, int> tolls, std::map<std::string, std::list<std::string>> connections,
       std::vector<std::vector<std::string>> trips);
  void dfs();
  void explore(std::string city);
  void postvisit(std::string city);
  std::vector<std::string> findMinCosts();
};

#endif

