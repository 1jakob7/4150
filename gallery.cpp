#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int hash(int row, int k, int uncloseable) {
  return (row * 1000000) + (k * 10000) + (uncloseable * 100);
}

/// Returns the most $$$ that can be made through the optimal choice of k rooms to close in a gallery.
int dynamicMaxGallery(const std::vector<std::vector<int>>& g, int k, int row, int uncloseable, std::unordered_map<int, int>& cache) {
  if (row > (int)g.size() - 1) {
    return 0;
  }

  if (cache.count(hash(row, k, uncloseable)) > 0) {
    return cache.at(hash(row, k, uncloseable));
  }
  
  int absMax = 0;

  // k = g.size() - row
  if (k == (int)g.size() - row) {  
    if (uncloseable == 0) {
      absMax = g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0, cache);
    }
    else if (uncloseable == 1) {
      absMax = g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1, cache);
    }
    else {
      absMax = std::max(g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0, cache),
			g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1, cache));
    }	   
  }
  // 0 < k < g.size() - row
  else if (0 < k && k < (int)g.size() - row) {    
    if (uncloseable == 0) {
      absMax = std::max(g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0, cache),
			g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1, cache));
    }
    else if (uncloseable == 1) {
      absMax = std::max(g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1, cache),
			g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1, cache));
    }
    else {
      absMax = std::max(g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0, cache),
			g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1, cache));
      absMax = std::max(absMax, g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1, cache)); 
    }
  }
  else {
    for (int i = row; i < g.size(); i++) {
      absMax = absMax + g[i][0] + g[i][1];
    }
    return absMax;
  }

  cache.insert(std::pair<int, int>(hash(row, k, uncloseable), absMax));
  
  return absMax;
}

int dynamicMaxGallery(const std::vector<std::vector<int>>& g, int k) {
  std::unordered_map<int, int> cache;
  
  return dynamicMaxGallery(g, k, 0, -1, cache);
}

int main() {
  std::string data;
  int N, k, r0, r1;

  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> N;
  ss >> k;

  std::vector<std::vector<int>> g;
  for (int i = 0; i < N; i++) {
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> r0;
    ss >> r1;
    g.push_back({r0, r1});
  }

  std::cout << dynamicMaxGallery(g, k) << std::endl;
  
  return 0;
}
