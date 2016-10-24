#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include "myClock.h"

using namespace std;

void myClock::startClock(){
	start = std::clock();
}

void myClock::getTime(int initSticks, int k, int numberOfTests){
	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	//this will open a file to append like a log file
	file.open("runtimes.csv", std::ios_base::app | std::ios_base::out);
	file << initSticks << "," << k << "," << duration << ";" << endl;
	file.close();

}
