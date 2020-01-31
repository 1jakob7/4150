#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

/// Uses a majority element algorithm for arrays that recurses until the array "size" is down to
/// a single element. Then, looks for the majority element in each subarray based on whether an
/// element (sun) is within the given diameter (in the same galaxy).
std::vector<long> findMajority(std::vector<long> &xCords, std::vector<long> &yCords, long lo, long hi, long d) {
  if (lo >= hi) { // base case
    return {-1, -1};
  }
  else if (hi - lo == 1) { // one element array
    return {xCords.at(lo), yCords.at(lo)};
  }
  else { // recurse
    long xCount = 0;
    long yCount = 0;
    long split = lo+(hi-lo)/2;
    std::vector<long> a = findMajority(xCords, yCords, lo, split, d);
    std::vector<long> b = findMajority(xCords, yCords, split+1, hi, d);
    if (a.at(0) == -1 && b.at(0) == -1) {
      return {-1, -1};
    }
    else if (a.at(0) == -1) { // b's galaxy may have a majority
      long bx = b.at(0);
      long by = b.at(1);
      for (long i = lo; i < hi; i++) {
	if (std::pow(bx-xCords.at(i), 2) + std::pow(by-yCords.at(i), 2) <= std::pow(d, 2)) {
	  yCount++;
	}
      }
      if (yCount > (hi - lo) / 2) {
	return {bx, by};
      }
      else {
	return {-1, -1};
      }
    }
    else if (b.at(0) == -1) { // a's galaxy may have a majority
      long ax = a.at(0);
      long ay = a.at(1);
      for (long i = lo; i < hi; i++) {
	if (std::pow(ax-xCords.at(i), 2) + std::pow(ay-yCords.at(i), 2) <= std::pow(d, 2)) {
	  xCount++;
	}
      }
      if (xCount > (hi - lo) / 2) {
	return {ax, ay};
      }
      else {
	return {-1, -1};
      }
    }
    else { // a or b's galaxy may have a majority
      long bx = b.at(0);
      long by = b.at(1);
      long ax = a.at(0);
      long ay = a.at(1);
      for (long i = lo; i < hi; i++) {
	if (std::pow(bx-xCords.at(i), 2) + std::pow(by-yCords.at(i), 2) <= std::pow(d, 2)) {
	  yCount++;
	}
	if (std::pow(ax-xCords.at(i), 2) + std::pow(ay-yCords.at(i), 2) <= std::pow(d, 2)) {
	  xCount++;
	}
      }
      if (yCount > xCount && yCount > (hi - lo) / 2) {
	return {bx, by};
      }
      else if (xCount > (hi - lo) / 2) {
	return {ax, ay};
      }
      else {
	return {-1, -1};
      }
    }
  }
}

/// Initiates the recursive class 'findMajority' and then evaluates the result.
std::string findMajorGalaxy(std::vector<long> &xCords, std::vector<long> &yCords, long d, long k) {
  std::vector<long> result = findMajority(xCords, yCords, 0, k, d);
  if (result.at(0) != -1) {
    long count = 0;
    long x = result.at(0);
    long y = result.at(0);
    // count up the stars in the major galaxy
    for (int i = 0; i < k; i++) {
      if (std::pow(x-xCords.at(i), 2) + std::pow(y-yCords.at(i), 2) <= std::pow(d, 2)) {
	count++;
      }
    }
    return std::to_string(count);
  }  
  return "NO";
}

int main(int argc, char *argv[]) {
  std::string data;
  long d, k;
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> d; // value defining the diameter of a universe's galaxies
  ss >> k; // how many stars are in the universe 
  
  std::vector<long> xCords;
  std::vector<long> yCords;
  int kCount = 0;
  long val;
  // create lists of the x and y coordinates of the universe's stars
  while (kCount < k) {
    std::getline(std::cin, data);
    std::stringstream ss(data);
    ss >> val;
    xCords.push_back(val);
    ss >> val;
    yCords.push_back(val);
    kCount++;
  }
  
  std::cout << findMajorGalaxy(xCords, yCords, d, k) << std::endl;
}
