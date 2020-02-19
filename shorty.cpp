#include <iostream>
#include <sstream>
#include <vector>
#include <map>



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
    }

    ///function call here
    
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
