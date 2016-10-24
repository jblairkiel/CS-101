#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "hats.h"

using namespace std; 

//initializes the hats
void hats::initializeHats(int initSticks, int k){
	// initializes our hats

	for (int i = 0; i < initSticks; i++){
		for (int j = 0; j < k; j++){
			arr[i][j] = j + 1;
		}
	}
}

//Public method(s) to update the counts based on a win or loss
void hats::updateHats(int besideHats[150][150], int initSticks){
	for (int i = 0; i < initSticks; i++){
		if (besideHats[i][0] != 0){
			int point3 = 0;
			while (besideHats[i][point3] != 0){
				point3++;
			}

			int point4 = 0;
			while (arr[i][point4] != 0){
				point4++;
			}
			arr[i][point4] = (besideHats[i][point3 - 1]);
			arr[i][point4 + 1] = (besideHats[i][point3 - 1]);
		}
	}
}

//a public method to choose a move against the cpu
void hats::chooseMoveAgainstCPU(int curSticks, int bHats[150][150], int k){
	//AI picks up random ball from hat # = to number of sticks left
	int point1 = 0;
	//int point3 = 0;
	//int point4 = 0;
	//int maxArrayBall = 0;
	while (arr[curSticks - 1][point1] != 0){
		point1++;
	}

chooseCPUAgain:
	rNum = rand() % point1;
	aiChoice = arr[curSticks - 1][rNum];
	//take stick according to ball
	//critical point to setup a succesful win by leaving cpu only 1 stick
	if ((0 < arr[curSticks - 1][rNum] <= k) && (arr[curSticks - 1][rNum] <= curSticks) && ((0 <= rNum) && (rNum < 150))){

		//put ball next to hat
		int point2 = 0;
		while (bHats[curSticks - 1][point2] != 0){
			point2++;
		}
		pointOfSub = point2;
		ballLocation = arr[curSticks - 1][rNum];
		bHats[curSticks - 1][point2] = arr[curSticks - 1][rNum];
		aiChoice = arr[curSticks - 1][rNum];

		//if random ball is in the middle of the array
		if (rNum != point1){
			for (int i = rNum; i < point1; i++){
				arr[curSticks - 1][i] = arr[curSticks - 1][i + 1];
			}
		}
		else{
			arr[curSticks - 1][rNum] = 0;
		}
		//cout << "AI selects " << aiChoice << "\n";

		//handle single stick
		if ((curSticks - aiChoice) == 1){
			//cout << "There is " << curSticks - aiChoice << " stick on the board.\n";
		}
		else if ((curSticks - aiChoice) > 1) {
			//cout << "There are " << curSticks - aiChoice << " sticks on the board.\n";
		}
		//printHats();
		curSticks = curSticks - aiChoice;
	}
	else {
		goto chooseCPUAgain;
	}
	//Intelligent Choice???
	/*if(currentSticks<=(k+1)){
		aiChoice = curSticks - 1;
		int point2 = 0;
		while (bHats[curSticks - 1][point2] != 0){
			point2++;
		}
		pointOfSub = point2;
		ballLocation = aiChoice;
		bHats[curSticks - 1][point2] = aiChoice;

		while (arr[curSticks - 1][point3] != aiChoice){
			point3++;
		}

		while (arr[curSticks - 1][point4] != 0){
			point4++;
		}

		arr[curSticks - 1][point3] = 0;
		for (int i = point3; i < point4; i++){
			arr[curSticks - 1][i] = arr[curSticks - 1][i + 1];
		}

		//cout << "AI selects " << aiChoice << "\n";

		//handle single stick
		if ((curSticks - aiChoice) == 1){
			//cout << "There is " << curSticks - aiChoice << " stick on the board.\n";
		}
		else if ((curSticks - aiChoice) > 1) {
			//cout << "There are " << curSticks - aiChoice << " sticks on the board.\n";
		}
		//printHats();
		curSticks = curSticks - aiChoice;
	}
	else if (k + 1 == currentSticks){
		aiChoice = k;
			//put ball next to hat
		int point2 = 0;
		while (bHats[curSticks - 1][point2] != 0){
			point2++;
		}
		pointOfSub = point2;
		ballLocation = aiChoice;
		bHats[curSticks - 1][point2] = aiChoice;

		while (arr[curSticks - 1][point3] != aiChoice){
			point3++;
		}

		while (arr[curSticks - 1][point4] != 0){
			point4++;
		}

		arr[curSticks - 1][point3] = 0;
		for (int i = point3; i < point4; i++){
			arr[curSticks - 1][i] = arr[curSticks - 1][i + 1];
		}
	
		//cout << "AI selects " << aiChoice << "\n";

		//handle single stick
		if ((curSticks - aiChoice) == 1){
			//cout << "There is " << curSticks - aiChoice << " stick on the board.\n";
		}
		else if ((curSticks - aiChoice) > 1) {
			//cout << "There are " << curSticks - aiChoice << " sticks on the board.\n";
		}
		//printHats();
		curSticks = curSticks - aiChoice;
	}
	else if ( ( (k+2)<curSticks) && (curSticks< ( (2*k) -1) ) ){
		if ( (0 <= aiChoice <= k) && (aiChoice <= curSticks) && (0 <= rNum<150) && ( (k + 2) <= (curSticks-aiChoice) )){

			//put ball next to hat
			int point2 = 0;
			while (bHats[curSticks - 1][point2] != 0){
				point2++;
			}
			pointOfSub = point2;
			ballLocation = arr[curSticks - 1][rNum];
			bHats[curSticks - 1][point2] = arr[curSticks - 1][rNum];
			aiChoice = arr[curSticks - 1][rNum];

			//if random ball is in the middle of the array
			if (rNum != point1){
				for (int i = rNum; i < point1; i++){
					arr[curSticks - 1][i] = arr[curSticks - 1][i + 1];
				}
			}
			else{
				arr[curSticks - 1][rNum] = 0;
			}
			//cout << "AI selects " << aiChoice << "\n";

			//handle single stick
			if ((curSticks - aiChoice) == 1){
				//cout << "There is " << curSticks - aiChoice << " stick on the board.\n";
			}
			else if ((curSticks - aiChoice) > 1) {
				//cout << "There are " << curSticks - aiChoice << " sticks on the board.\n";
			}
			//printHats();
			curSticks = curSticks - aiChoice;
		}
		else {
			goto chooseCPUAgain;
		}
	}
	else{
		if ((0 <= arr[curSticks - 1][rNum] <= k) && (arr[curSticks - 1][rNum] <= curSticks) && (0 <= rNum < 150)){

			//put ball next to hat
			int point2 = 0;
			while (bHats[curSticks - 1][point2] != 0){
				point2++;
			}
			pointOfSub = point2;
			ballLocation = arr[curSticks - 1][rNum];
			bHats[curSticks - 1][point2] = arr[curSticks - 1][rNum];
			aiChoice = arr[curSticks - 1][rNum];

			//if random ball is in the middle of the array
			if (rNum != point1){
				for (int i = rNum; i < point1; i++){
					arr[curSticks - 1][i] = arr[curSticks - 1][i + 1];
				}
			}
			else{
				arr[curSticks - 1][rNum] = 0;
			}
			//cout << "AI selects " << aiChoice << "\n";

			//handle single stick
			if ((curSticks - aiChoice) == 1){
				//cout << "There is " << curSticks - aiChoice << " stick on the board.\n";
			}
			else if ((curSticks - aiChoice) > 1) {
				//cout << "There are " << curSticks - aiChoice << " sticks on the board.\n";
			}
			//printHats();
			curSticks = curSticks - aiChoice;
		}
		else {
			goto chooseCPUAgain;
		}
	}
	//if chosen wrong ball
	*/
	currentSticks = curSticks;
}

//A public method to choose a move.
void hats::chooseMove(int curSticks, int bHats[150][150], int k){

	//AI picks up random ball from hat # = to number of sticks left
	int point1 = 0;
	//int maxArrayBall = 0;
	while (arr[curSticks - 1][point1] != 0){
		point1++;
	}

chooseAgain:
	rNum = rand() % point1;
    //cout<<rNum<<" This is the num generated\n";
	aiChoice = arr[curSticks - 1][rNum];
    //cout<<aiChoice<<" This is the number picked\n";
	if ((aiChoice > curSticks) && (aiChoice < 1)){
		goto chooseAgain;
	}
	//take stick according to ball
    //cout<<"this is the choice of the computer "<<arr[curSticks-1][rNum]<<"\n";
	if ((1 <= arr[curSticks - 1][rNum] <= k) && (arr[curSticks - 1][rNum] <= curSticks) && (0<aiChoice<k) && ((curSticks-arr[curSticks-1][rNum])>-1)){

		//put ball next to hat
        int temp = 0;
		int point2 = 0;
		while (bHats[curSticks - 1][point2] != 0){
			point2++;
		}
		pointOfSub = point2;
		ballLocation = aiChoice;
		bHats[curSticks - 1][point2] = aiChoice;
	    aiChoice = arr[curSticks - 1][rNum];
        temp = arr[curSticks - 1][rNum];
        cout<<"AIChoice is "<<aiChoice;

		//if random ball is in the middle of the array
		if (rNum != point1){
			for (int i = rNum; i < point1; i++){
				arr[curSticks - 1][i] = arr[curSticks - 1][i + 1];
			}
		}
		else{
			arr[curSticks - 1][rNum] = 0;
		}
		cout << "AI selects " << temp<< "\n";
		cout << '\n';

		//handle single stick
		if ((curSticks - (temp) == 1)){
			cout << "There is " << curSticks - temp<< " stick on the board.\n";
		
		}
		else if ((curSticks - aiChoice) > 1) {
			cout << "There are " << curSticks - (temp) << " sticks on the board.\n";
		}
		//printHats();
		curSticks = curSticks - (temp);
	}

	//if chosen wrong ball
	else {
		goto chooseAgain;
	}
	currentSticks = curSticks;
}

//resets the balls from the previous turn
void hats::resetBalls(int besideHats[150][150], int initSticks){
	for (int i = 0; i < initSticks; i++){
		if (besideHats[i][0] != 0){
			int point3 = 0;
			while (besideHats[i][point3] != 0){
				point3++;
			}

			int point4 = 0;
			while (arr[i][point4] != 0){
				point4++;
			}
			arr[i][point4] = (besideHats[i][point3 - 1]);
		}
	}
}

//prints the GUI for hats
void hats::printHats(){
	int point1 = 0;
	int point2 = 0;
	int check = 0;

	cout << "\nThe current Hats are\n";
	while (arr[point1][point2] != 0){
		point1++;
		check = arr[point1][point2];
	}
	for (int i = 0; i < point1; i++){
		while (arr[i][point2] != 0){
			point2++;
		}
		for (int j = 0; j < point2; j++){
			cout << arr[i][j] << "  ";
		}

		cout << endl;
	}
}

//sets the currentSticks
void hats::setCurrentSticks(int num){
	currentSticks = num;
}

//gets the currentSticks
int hats::getCurrentSticks(){
	return currentSticks;
}

//gets the hats array
int* hats::getHatPointer(int pointer){
	return arr[pointer];
}

//get ball location
int hats::getBallLocation(){
	return ballLocation;
}

//set ball location
void hats::setBallLocation(int location){
	ballLocation = location;
}

//get point of substitution
int hats::getPointOfSub(){
	return pointOfSub;
}

//set point of substitution
void hats::setPointOfSub(int point){
	pointOfSub = point;
}

int hats::cpuTrainMove(int curSticks, int k){
	//CPU picks up random number of sticks
rePick:	
	rNum = rand() % k+1;

	//make sure number is in range
	if ((0 < rNum <= k) && (curSticks - rNum >= 0)){
		curSticks = curSticks - rNum;
	}

	//if chosen wrong ball
	else {
		goto rePick;
	}

	currentSticks = curSticks;
	return curSticks;
    
	//Incorrect range
	/*if ((0 < rNum <= k) && (curSticks - rNum >= 0) && (curSticks - rNum != 1)){
		curSticks = curSticks - rNum;
	}
	else{
		goto rePick;
	}
	currentSticks = curSticks;
	return curSticks;
	*/

}
