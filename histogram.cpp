// copyright 2018 xxxx

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using std::string;
using std::vector;

// This simple program reads from a file a set of numbers (double format)
// computes a running mean value, computes the median after sort

// This program has several problems, can you spot them

int main(int argc, char *argv[]) {
  string file_name{argv[1]};
  vector<double> buf;
  std::ifstream fin(file_name, std::ios::in);

  string line;
  auto mean = 0.0;

  while (std::getline(fin, line)) {
    auto d = std::stod(line);
    buf.push_back(d);
    mean = (buf.size() == 1) ? d : mean + (d - mean) / buf.size();
  }

  std::sort(buf.begin(), buf.end());

  auto mid = buf.size() / 2;
  double median = (buf.size() % 2) ? buf[mid] :
                                     (buf[mid - 1] + buf[mid]) / 2;

  std::cout << "number of elements = " << buf.size()
            << ", median = " << median
            << ", mean = " << mean << std::endl;

//------------------------------------
  vector<int> cnt;
  for (int b=100, s=0, i=0; ((unsigned)i < buf.size())&&(buf[i] < 8000); b+=100) {
    for (s=0; ((unsigned)i < buf.size())&&(buf[i] < b); i++, s++) {}
    cnt.push_back(s);
  }
  std::vector<int>::iterator maxCnt;
  maxCnt = std::max_element(cnt.begin(), cnt.end()-1);

  for (int b=0, i=0; (unsigned) i < cnt.size(); b+=100, i++) {
    std::cout << std::setw(5) << b << std::setw(8) << cnt[i] << " ";
    std::cout << std::string(60 * cnt[i]/(*maxCnt), '*') << std::endl;
  }
}

