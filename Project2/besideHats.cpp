#include "besideHats.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

//initializes besideHats array
void besideHats::initializebesideHats(int k, int initSticks){
	for (int i = 0; i < initSticks; i++){
		for (int j = 0; j < k; j++){
			arr[i][j] = 0;
		}
	}
}

//resets all of my balls beside the hats
void besideHats::resetAllBesideHats(int k, int initSticks){
	for (int i = 0; i < initSticks; i++){
		for (int j = 0; j < k; j++){
			arr[i][j] = 0;
		}
	}
}

int besideHats::getHatPointer(int pointer1, int pointer2){
	return arr[pointer1][pointer2];
}

void besideHats::addBall(int curSticks, int point2, int bLocation){
	arr[curSticks - 1][point2] = bLocation;
}

//Prints the contents of beside hats
void besideHats::printBesideHats(){
	for (int i = 0; i < 151; i++){
		cout << "\nRow: " << i;
		for (int j = 0; j < 151; j++){
			cout << "[" << arr[i][j] << "] ";
		}
	}
}
;
