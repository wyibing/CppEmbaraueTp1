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
  int cnt[80]={0};
  for (double v:buf){
     cnt[(int)v/100]++;
  }
  int*maxCnt=std::max_element(cnt, cnt+80);
  int b=-100;
  for (int c: cnt){
      std::cout << std::setw(5) << (b+=100) << std::setw(8) << c << " ";
    std::cout << std::string(60 * c/(*maxCnt), '*') << std::endl;
  }
}

