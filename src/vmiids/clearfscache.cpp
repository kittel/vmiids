/*
 * clearfscache.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ofstream myfile;
  myfile.open ("/proc/sys/vm/drop_caches");
  myfile << "3\n";
  myfile.close();
  return 0;
}
