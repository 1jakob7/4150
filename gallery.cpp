#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

int dynamicMaxGallery(std::vector<std::vector<int>>& g, int k, int row, int uncloseable) {

  if ((unsigned int)row == g.size() - 1) { // the final row in the gallery
    if (k == 1) {
      if (uncloseable == 0) {
	return g[row][0];
      }
      if (uncloseable == 1) {
	return g[row][1];
      }
      else {
	return std::max(g[row][0], g[row][1]);
      }
    }
    else {
      return g[row][0] + g[row][1];
    }
  }
  
  if (k == 0) { // the rest of the rooms can be left open
    return g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1);
  }

  int max0 = 0;
  int max1 = 0;
  int maxn = 0;
  
  if ((unsigned int)k == g.size() - row) { // one room has to be closed
    if (uncloseable == 0) {
      max0 = g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0);
    }
    else if (uncloseable == 1) {
      max1 = g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1);
    }
    else {
      max0 = g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0);
      max1 = g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1);
    }
  }
  else if (uncloseable == -1) { // either room may be closed
    max0 = g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0);
    max1 = g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1);
    maxn = g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1);
  }
  else if (uncloseable == 0) { // row 0's room must stay open
    max0 = g[row][0] + dynamicMaxGallery(g, k-1, row+1, 0);
    maxn = g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1);
  }
  else { // row 1's room must stay open
    max1 = g[row][1] + dynamicMaxGallery(g, k-1, row+1, 1);
    maxn = g[row][0] + g[row][1] + dynamicMaxGallery(g, k, row+1, -1);
  }

  int absMax;
  absMax = std::max(max0, max1);
  absMax = std::max(absMax, maxn);

  return absMax;
}

int dynamicMaxGallery(std::vector<std::vector<int>>& g, int k) {

  return dynamicMaxGallery(g, k, 0, -1);
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
