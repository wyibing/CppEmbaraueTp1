// copyright 2018 xxxx

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using std::string;
using std::vector;

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
  //écart type
  double et=0;
  for (double v: buf){
  et+=(v-mean)*(v-mean);
  }
  et=sqrt(et/buf.size());

  std::sort(buf.begin(), buf.end());

  auto mid = buf.size() / 2;
  double median = (buf.size() % 2) ? buf[mid] :
                                     (buf[mid - 1] + buf[mid]) / 2;

  std::cout << "number of elements = " << buf.size()
            << ", median = " << median
            << ", mean = " << mean << std::endl;
//------------------------------------
//stats du fichier fourni
  vector<int> cnt;
  for (int b=100, s=0, i=0; ((unsigned) i < buf.size())&&(buf[i] < 8000); b+=100) {
    for (s=0; buf[i] < b; i++, s++) {}
    cnt.push_back(s);
  }
  std::vector<int>::iterator maxCnt,maxCnt2;
  std::vector<double>::iterator maxVec,maxVec2;
  maxCnt = std::max_element(cnt.begin(), cnt.end()-1);
  maxVec = std::max_element(buf.begin(), buf.end()-1);

  for (int b=0, i=0; (unsigned) i < cnt.size(); b+=100, i++) {
    std::cout << std::setw(5) << b << std::setw(8) << cnt[i] << " ";
    std::cout << std::string(60 * cnt[i]/(*maxCnt), '*') << std::endl;
  }
//génération d'une distribution à partir des stats fournies
    
    int N=buf.size();
    double et2=0;
    double mean2=0;
    double tolerance=1;
    vector<double> distrib; //va contenir les valeurs générées
    vector<double> unsorted; //contient les valeurs non triées
    vector<int> cntdistrib; //va contenir le nb d'occurences des valeurs
    
    while( (abs(mean-mean2)>tolerance)|(abs(et-et2)>tolerance)){
    distrib={};
    cntdistrib={};
    //génération de la séquence
    std::random_device rd;
    std::mt19937 gen(rd());

    std::lognormal_distribution<> d(log(median), -sqrt(2)*sqrt(log(mean/median))); 
    //std::chi_squared_distribution<> d(1000); NO (mauvais écart type)
    //std::cauchy_distribution<> d(mean,500); SYMETRIQUE
     //std::fisher_f_distribution<> d(2,2); can't prove its not --
     //std::gamma_distribution<> d(mean*mean/(et*et),et*et/mean); Nooooooooooooooooo!!!!
    //std::weibull_distribution<> d(1.298156045,1510.176015); NON
    
    
    for (int i=0; i<N;i++) {
    	distrib.push_back(d(gen)); //On stocke les valeurs générées dans distrib
   }
    //for (int i=0; i<N; i++) distrib[i]=distrib[i]*Max22*(*maxVec);
    unsorted=distrib;
    //
    std::sort(distrib.begin(), distrib.end());
    //calcul de la moyenne de la séquence générée
    mean2=0;
    for (int i=0; i<N; i++) {
    mean2+=distrib[i];
    }
    mean2/=N;
    //
    //calcul de l'écart type
    et2=0;
    for (double v: distrib){et2+=(v-mean2)*(v-mean2);}
    et2=sqrt(et2/distrib.size());
    //
    
    //comptage des occurences
    for (int b=100, s=0, i=0; (i< N)&&(distrib[i] < 8000); b+=100) {
    	for (s=0; (i< N)&&(distrib[i] < b); i++, s++) {}
   	 cntdistrib.push_back(s);
    }
    
    //
    //comparaison des deux séquences
  std::cout << "paramètres fichier:" << "moyenne : "<< mean << "écart type" << et << std::endl;
  std::cout << "paramètres distrib:" << "moyenne : "<< mean2 << "écart type" << et2 << std::endl;
  // 
}
//Calcul du max pour l'histogramme
  maxCnt2=std::max_element(cntdistrib.begin(), cntdistrib.end()-1);
  double Max2=(*maxCnt2);

//Affichage de l'histogramme
for (int b=0, i=0;(unsigned) i < cntdistrib.size(); b+=100, i++) {
    
    std::cout << std::setw(5) << b << std::setw(8) << cntdistrib[i] << " ";
    std::cout << std::string(60 * cntdistrib[i]/Max2, '*') << std::endl;
    
  }
  std::cout << "paramètres fichier : " << std::endl << "moyenne : "<< mean<< std::endl << "écart type : " << et << std::endl;
  std::cout << "paramètres distrib : " << std::endl << "moyenne : "<< mean2<< std::endl << "écart type : " << et2 << std::endl;
  std::ofstream dat("data/data2_100000.txt", std::ios::out);
  for (double c:unsorted) {
  dat<<c<<std::endl;
  }
  
}

