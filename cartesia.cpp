#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>


int calcTransport(int xCur, int yCur, int a, int b, int c, int d, int maxTime, int curTime, const std::unordered_map<int, std::vector<int>>& drones) {
  // Borg cube has arrived :(
  if (curTime > maxTime) {
    return -1; // signifies this path is not viable
  }
  // cannot exceed graph bounds
  if (abs(xCur) > 1000 || abs(yCur) > 1000) {
    return -1;
  }
  // if xCur and yCur are also drone coordinates -> not a path
  if (drones.count(xCur) > 0) {
    if (std::find(drones.at(xCur).begin(), drones.at(xCur).end(), yCur) != drones.at(xCur).end()) {
      return -1;
    }
  }
  // we've found a solution
  if (xCur == 0 && yCur == 0) {
    return maxTime - curTime;
  }

  curTime++;
  int dX = (a*curTime) % b;
  int dY = (c*curTime) % d;

  int xy1 = calcTransport(xCur+dX, yCur+dY, a, b, c, d, maxTime, curTime, drones); // + +
  int xy2 = calcTransport(xCur+dX, yCur-dY, a, b, c, d, maxTime, curTime, drones); // + -
  int xy3 = calcTransport(xCur-dX, yCur+dY, a, b, c, d, maxTime, curTime, drones); // - +
  int xy4 = calcTransport(xCur-dX, yCur-dY, a, b, c, d, maxTime, curTime, drones); // - -

  int m1 = std::max(xy1, xy2);
  int m2 = std::max(xy3, xy4);
  int timeLeft = std::max(m1, m2);

  if (timeLeft < 0) {
    return -1;
  }
  return timeLeft;
}

std::string beamMeUp(int x, int y, int a, int b, int c, int d, int m, const std::vector<int> v) {
  // organize the drone coordinates : x-val -> y-vals
  std::unordered_map<int, std::vector<int>> drones;
  for (int i = 0; i < (int)v.size(); i+=2) {
    if (drones.count(v[i]) > 0) {
      drones.at(v[i]).push_back(v[i+1]);
    }
    else {
      drones.insert(std::pair<int, std::vector<int>>(v[i], {v[i+1]}));
    }
  }

  int timeLeft = calcTransport(x, y, a, b, c, d, m, 0, drones);
  
  if (timeLeft < 0) {
    return "You will be assimilated! Resistance is futile!";
  }
  else {
    return "I had " + std::to_string(timeLeft) + " to spare! Beam me up Scotty!";
  }
}

int main() {
  std::string data;
  int x, y, a, b, c, d, m, n;
  std::vector<int> v;
  
  std::getline(std::cin, data);
  std::stringstream ss(data);
  ss >> x >> y;
  std::getline(std::cin, data);
  ss.str(""); ss.clear();
  ss << data;
  ss >> a >> b >> c >> d;
  std::getline(std::cin, data);
  ss.str(""); ss.clear();
  ss << data;
  ss >> m;
  std::getline(std::cin, data);
  ss.str(""); ss.clear();
  ss << data;
  ss >> n;

  int coord;
  for (int i = 0; i < n; i++) {
    std::getline(std::cin, data);
    ss.str(""); ss.clear();
    ss << data;
    ss >> coord;
    v.push_back(coord);
    ss >> coord;
    v.push_back(coord);
  }
  
  std::cout << beamMeUp(x, y, a, b, c, d, m, v) << std::endl;
  
  return 0;
}
