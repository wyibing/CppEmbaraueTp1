// copyright 2018 xxxx

#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <cmath>

using std::string;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "file of data required" << std::endl;
    return EXIT_FAILURE;
  }
  string file_name{argv[1]};
  std::unordered_map<string, double> map1;
  std::multimap<double, string> map2;
  std::ifstream fin(file_name, std::ios::in);
  string line;

  while (std::getline(fin, line)) {
    std::istringstream stream(line);
    string key;
    double value;
    stream >> key >> value;
    map1.insert(std::make_pair(key, value));
    map2.insert(std::make_pair(value, key));
  }

  while (1) {
    string q;
    std::cout << "query> ";
    std::cin >> q;
    if (q == "END") {
      std::cout << "Bye..." << std::endl;
      break;
    }
    if (q[0] == '+') {
      auto v = std::stod(q);
      std::map<double, string>::iterator it, itlow, itup;
      itlow = map2.lower_bound(0.99*v);
      itup = map2.upper_bound(1.01*v);
      for (it = itlow; it != itup; it++) {
        std::cout << "value[" << it->second << "]= " << it->first << std::endl;
      }
      if (itlow == itup) std::cout << "No value in the interval" << std::endl;

    } else {
        std::unordered_map<string, double>::iterator it;
        if ((it = map1.find(q)) != map1.end()) {
          std::cout << "value[" << q << "]= "<< it->second << std::endl;
      } else {
        std::cout << "This ID does not exist" << std::endl;
      }
    }
  }
}
