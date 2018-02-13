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
using std::unordered_map;
using std::map;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "file of data required" << std::endl;
    return EXIT_FAILURE;
  }
  string file_name{argv[1]};
  unordered_map<string, double> map1;
  map<double, string> map2;
  std::ifstream fin(file_name, std::ios::in);
  string line;

  while (std::getline(fin, line)) {
    std::istringstream stream(line);
    string key;
    double value;
    stream >> key >> value;
    map1.insert(std::make_pair(key, value));
    map2[value] = key;
  }

  while (1) {
    string q;
    std::cout << "query> ";
    std::cin >> q;
    if (q == "END") {
      std::cout << "Bye..." << std::endl;
      break;
    }
    if (q.at(0) == '+') {
      auto v = std::stod(q);
      map<double, string>::iterator it;
      for (it = map2.begin(); it->first < 0.99*v; it++) {}
      for (; it->first <1.01*v; it++) {
        std::cout << "value[" << it->first << "]= " << it->second << std::endl;
      }

    } else {
        unordered_map<string, double>::iterator it;
        if ((it = map1.find(q)) != map1.end()) {
          std::cout << "value[" << q << "]= "<< it->second << std::endl;
      } else {
        std::cout << "This ID does not exist" << std::endl;
      }
    }
  }
}
