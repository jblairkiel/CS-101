#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <ctime>
using namespace std;



class myClock{
private:
	double duration;
	std::clock_t start;
	ofstream file;
public:
	void startClock();
	void getTime(int initSticks, int k, int numberOfTests);
};

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

class hats{
private:

	//A private array of size k containing the number of balls corresponding to the associated move.
	int arr[150][150] = {};

	//A private variable storing the number of sticks chosen at that move.
	int sticksChosen;
	int currentSticks;
	int rNum;
	int ballLocation;
	int pointOfSub;
	int aiChoice;

public:

	void initializeHats(int initSticks, int k);
	void updateHats(int subArray[150][150], int initSticks);
	void chooseMove(int curSticks, int besideHats[150][150], int k);
	void resetBalls(int subArray[150][150], int initSticks);
	void printHats();
	int getBallLocation();
	void setBallLocation(int location);
	int getPointOfSub();
	void setPointOfSub(int point);
	int getCurrentSticks();
	void setCurrentSticks(int sticks);
	int* getHatPointer(int pointer);
	int cpuTrainMove(int curSticks, int k);
	void chooseMoveAgainstCPU(int curSticks, int bHats[150][150], int k);

};

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
	int point3 = 0;
	int point4 = 0;
	int maxArrayBall = 0;
	while (arr[curSticks - 1][point1] != 0){
		point1++;
	}

chooseCPUAgain:
	rNum = rand() % point1;
	aiChoice = arr[curSticks - 1][rNum];
	//take stick according to ball
	//critical point to setup a succesful win by leaving cpu only 1 stick
	if ((0 < arr[curSticks - 1][rNum] <= k) && (arr[curSticks - 1][rNum] <= curSticks) && (0 <= rNum < 150)){

		//put ball next to hta
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
	int maxArrayBall = 0;
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

//class for the balls set beside the hats
class besideHats{
private:
	int arr[150][150] = {};
public:
	void initializebesideHats(int k, int initSticks);
	int getHatPointer(int pointer1, int pointer2);
	void resetAllBesideHats(int k, int initSticks);
	void addBall(int curSticks, int point2, int bLocation);
};

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

int main(int argc, char* argv[]){

	int projectPart;
	int initSticks;
	int k;
	int curSticks;
	int chosenSticks;
	int playerSwitchInt = 1;


	//Begin 2 player game asking for inputs
	cout << "Welcome to the game of sticks!\n";
	cout << "How many sticks are on the table initially (10-100)? ";
	cin >> initSticks;
	cout << "How many sticks can be picked up per round (2-20)? ";
	cin >> k;
	curSticks = initSticks;


	cout << "\nOptions:\n  Play against a friend (1)\n  Play against a computer (2)\nWhich option do you take (1-2)? ";
	cin >> projectPart;
	if (projectPart == 1){
        int playAgain = 1;
        while(playAgain = 1){
			curSticks = initSticks;
            cout << "\nThere are " << curSticks << " stick on the board.\n";
            //While sticks are on board play game.
            while (curSticks > 0){

                //Player 1 turn
                if (playerSwitchInt == 1){
                    cout << "Player 1: How many sticks do you take (1-" << k << ")? ";
                    cin >> chosenSticks;

                    //make sure chosensticks is between 1 and k
					if ((1 <= chosenSticks) &&(chosenSticks <= k) && (chosenSticks <= curSticks)){
                        curSticks = curSticks - chosenSticks;

                        //handle single stick
                        if (curSticks == 1){
                            cout << "There is " << curSticks << " stick on the board.\n";
                        }
                        else{
                            cout << "There are " << curSticks << " sticks on the board.\n";
                        }
                        playerSwitchInt = 2;
                        cout<<"\n";
                    }
                    //player chose incorrect amount
                    else {
                        cout << "Please enter a number between 1 and " << k << "\n";
                    }
                }
                //Player 2 turn
                else if (playerSwitchInt == 2){

                    cout << "Player 2: How many sticks do you take (1-" << k << ")? ";
                    cin >> chosenSticks;

                    //make sure chosensticks is between 1 and k
					if ((1 <= chosenSticks) && (chosenSticks <= k) && (chosenSticks <= curSticks)){
                        curSticks = curSticks - chosenSticks;

                        //handle single stick
                        if (curSticks == 1){
                            cout << "There is " << curSticks << " stick on the board.\n";
                        }
                        else{
                            cout << "There are " << curSticks << " sticks on the board.\n";
                        }
                        playerSwitchInt = 1;
                        cout<<"\n";
                    }
                    //player chose incorrect amount
                    else {
                        cout << "Please enter a number between 1 and " << k << "\n";
                    }

                }

            }

            //Determine who won
            if (playerSwitchInt == 1){
                cout << "Player 1, you lose.";
            }
            else{
                cout << "Player 2, you lose.";
            }
            
        //make sure user does correct input
		playAgain3:
			cout << "You lose.\nPlay again (1 = yes, 0 = no)? ";
			cin >> playAgain;
			if (playAgain != 0 && playAgain != 1){
				cout << "\nYou must select whether to play again or not\n";
				goto playAgain3;
			}
        }
	}
	else if (projectPart == 2){

		int rNum;
		hats hats;
		besideHats besideHats;
		int tempArr[150][150] = {};
		int** temp = {0};
		int aiChoice = 0;

		//initialize hats and beside hats
		hats.initializeHats(initSticks, k);
		besideHats.initializebesideHats(k, initSticks);

		int gameCounter = 0;
		//Train AI first
		cout << "Training AI, please wait...\n";
		//myClock clock;
		//clock.startClock();
		int numberOfTests = 1000;
		while (gameCounter < numberOfTests){
			//While sticks are on board play game.
			curSticks = initSticks;
			while (curSticks > 0){

				//CPU Turn
				if (playerSwitchInt == 1){
					curSticks = hats.cpuTrainMove(curSticks, k);

					// if there are still sticks on the board let AI play
					if (curSticks != 0){
						playerSwitchInt = 2;
					}
				}
				else if (playerSwitchInt == 2){

					//While there is not a good random number chosen
					bool badSelection = false;
					while (badSelection == false){

						int tempArr[150][150] = {};
						for (int i = 0; i < 150; i++){
							for (int j = 0; j < 150; j++){
								tempArr[i][j] = besideHats.getHatPointer(i, j);
							}
						}

						int point2;
						int bLocation;
						hats.chooseMoveAgainstCPU(curSticks, tempArr, k);
						point2 = hats.getPointOfSub();
						bLocation = hats.getBallLocation();
						besideHats.addBall(curSticks, point2, bLocation);
						curSticks = hats.getCurrentSticks();
						// if there are still sticks on the board let user play
						if (curSticks != 0){
							playerSwitchInt = 1;
						}
						tempArr[150][150] = {};
						badSelection = true;
					}
				}
			}
			//AI Wins, put extra ball of the beside numbers in hat
			if (playerSwitchInt == 1){

				//loop through beside numbers
				//int** bHats = besideHats.getHats();
				int tempArr[150][150] = {};
				for (int i = 0; i < 150; i++){
					for (int j = 0; j < 150; j++){
						tempArr[i][j] = besideHats.getHatPointer(i, j);
					}
				}
				hats.updateHats(tempArr, initSticks);
				tempArr[150][150] = {};
			}

			//Else throw away beside balls 
			else{

				//reinitialize primary array
				//int** bHats = besideHats.getHats();
				int tempArr[150][150] = {};
				for (int i = 0; i < 150; i++){
					for (int j = 0; j < 150; j++){
						tempArr[i][j] = besideHats.getHatPointer(i, j);
					}
				}
				hats.resetBalls(tempArr, initSticks);
				tempArr[150][150] = {};
			}

			//besides array renumbered
			besideHats.resetAllBesideHats(k, initSticks);
			playerSwitchInt = 1;
			gameCounter++;
		}
			
		//new cpu AI game
		//clock.getTime(initSticks, k, numberOfTests);
		//Now user plays a trained AI
		int pAgain = 1;
		while (pAgain == 1){
			//game
			curSticks = initSticks;
			cout << '\n';
			cout << "There are " << curSticks << " on the board.\n";
			while (curSticks > 0){

				//player 1 turn
				if (playerSwitchInt == 1){
					cout << "Player 1: How many sticks do you take (1-" << k << ")? ";
					cin >> chosenSticks;

					//make sure chosensticks is between 1 and k
					if ((1 <= chosenSticks) && (chosenSticks <= k) && (chosenSticks <= curSticks)){


						//handle single stick
						if ((curSticks - chosenSticks) == 1){
							cout << '\n';
							cout << "There is " << curSticks - chosenSticks << " stick on the board.\n";
						}
						else if ((curSticks - chosenSticks) > 1){
							cout << '\n';
							cout << "There are " << curSticks - chosenSticks << " sticks on the board.\n";
						}
						curSticks = curSticks - chosenSticks;

						// if there are still sticks on the board let AI play
						if (curSticks != 0){
							playerSwitchInt = 2;
						}

					}
					//player chose incorrect amount
					else {
						cout << "Please enter a number between 1 and " << k << "\n";
					}
				}
				//AI turn
				else if (playerSwitchInt == 2){

					//While there is not a good random number chosen
					bool badSelection = false;
					while (badSelection == false){

						int tempArr[150][150] = {};
						for (int i = 0; i < 150; i++){
							for (int j = 0; j < 150; j++){
								tempArr[i][j] = besideHats.getHatPointer(i, j);
							}
						}
					
						int point2;
						int bLocation;
						hats.chooseMove(curSticks, tempArr, k);
						point2 = hats.getPointOfSub();
						bLocation = hats.getBallLocation();
						besideHats.addBall(curSticks,point2, bLocation);
						curSticks = hats.getCurrentSticks();
						// if there are still sticks on the board let user play
						if (curSticks != 0){
							playerSwitchInt = 1;
						}
						tempArr[150][150] = {};
						badSelection = true;
					}
				}
			}

			//AI Wins, put extra ball of the beside numbers in hat
			if (playerSwitchInt == 1){

				//make sure user does correct input
			playAgain1:
				cout << "You lose.\nPlay again (1 = yes, 0 = no)? ";
				cin >> pAgain;
				if (pAgain != 0 && pAgain != 1){
					cout << "\nYou must select whether to play again or not\n";
					goto playAgain1;
				}

				//loop through beside numbers
				//int** bHats = besideHats.getHats();
				int tempArr[150][150] = {};
				for (int i = 0; i < 150; i++){
					for (int j = 0; j < 150; j++){
						tempArr[i][j] = besideHats.getHatPointer(i, j);
					}
				}
				hats.updateHats(tempArr, initSticks);
				tempArr[150][150] = {};
			}

			//Else throw away beside balls 
			else{

				//reinitialize primary array
				//int** bHats = besideHats.getHats();
				int tempArr[150][150] = {};
				for (int i = 0; i < 150; i++){
					for (int j = 0; j < 150; j++){
						tempArr[i][j] = besideHats.getHatPointer(i, j);
					}
				}
				hats.resetBalls(tempArr, initSticks);
				tempArr[150][150] = {};

				//make sure user does correct input
			playAgain2:
				bool tCase = 0;
				while (tCase != 1){
					cout << "AI loses. \nPlay again (1 = yes, 0 = no)? ";
					cin >> pAgain; 
					if ((pAgain != 0) && (pAgain != 1)){
						cout << "\nYou must select whether to play again or not\n";
						goto playAgain2;
					}
					else{
						tCase = 1; 
					}
				}
			}

			//besides array renumbered
			besideHats.resetAllBesideHats(k, initSticks);
			playerSwitchInt = 1;
		}
	}
}
