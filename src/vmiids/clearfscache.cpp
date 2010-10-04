/*
 * clearfscache.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include <iostream>
#include <fstream>
using namespace std;

/**
 * Binary to clear the systems file system caches.
 * @sa FileSystemSensorModule
 *
 * This binary writes the value 3 to /proc/sys/vm/drop_caches.
 * @see http://linux.die.net/man/5/proc
 *
 * @return Zero
 */
int main () {
  ofstream myfile;
  myfile.open ("/proc/sys/vm/drop_caches");
  myfile << "3\n";
  myfile.close();
  return 0;
}
