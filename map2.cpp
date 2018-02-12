// copyright 2018 xxxx

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <cmath>

using std::string;
using std::unordered_map;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "file of data required" << std::endl;
    return EXIT_FAILURE;
  }
  string file_name{argv[1]};
  unordered_map<string, double> map;
  std::ifstream fin(file_name, std::ios::in);
  string line;

  while (std::getline(fin, line)) {
    std::istringstream stream(line);
    string key;
    double value;
    stream >> key >> value;
    map.insert(std::make_pair(key, value));
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
      unordered_map<string, double>::iterator it;
      for (it = map.begin(); it != map.end(); it++) {
        if (std::abs(it->second - v) < (0.01*(it->second))) {
          std::cout << "value[" << it->first
                    << "]= " << it->second << std::endl;
        }
      }
    } else {
        unordered_map<string, double>::iterator it;
        if ((it = map.find(q)) != map.end()) {
          std::cout << "value[" << q << "]= "<< it->second << std::endl;
      } else {
        std::cout << "This ID does not exist" << std::endl;
      }
    }
  }
}
