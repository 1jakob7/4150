#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

std::vector<long> findMajority(std::vector<long> &xCords, std::vector<long> &yCords, long lo, long hi, long d) {
  if (lo >= hi) {
    return {-1, -1};
  }
  else if (hi - lo == 1) {
    return {xCords.at(hi), yCords.at(hi)};
  }
  else {
    long xCount = 0;
    long yCount = 0;
    std::vector<long> a = findMajority(xCords, yCords, lo, hi/2, d); // -1 +1?
    std::vector<long> b = findMajority(xCords, yCords, hi/2, hi, d); // -1 +1?
    if (a.at(0) == -1 && b.at(0) == -1) {
      return {-1, -1};
    }
    else if (a.at(0) == -1) {
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
    else if (b.at(0) == -1) {
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
    else {
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

std::string findMajorGalaxy(std::vector<long> &xCords, std::vector<long> &yCords, long d, long k) {
  std::vector<long> result = findMajority(xCords, yCords, 0, k, d);
  if (result.at(0) != -1) {
    long count = 0;
    long x = result.at(0);
    long y = result.at(0);
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
  ss >> d;
  ss >> k;
  
  std::vector<long> xCords;
  std::vector<long> yCords;
  int kCount = 0;
  long val;
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
