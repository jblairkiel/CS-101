#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "myClock.h"
#include "hats.h"
#include "besideHats.h"
using namespace std;


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
        while(playAgain == 1){
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
						memset(tempArr, 0, sizeof(tempArr[0][0]) * 150 * 150);
						//tempArr[150][150] = {};
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
				memset(tempArr, 0, sizeof(tempArr[0][0]) * 150 * 150);
				//tempArr[150][150] = {};
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
				memset(tempArr, 0, sizeof(tempArr[0][0]) * 150 * 150);
				//tempArr[150][150] = {};
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
						memset(tempArr, 0, sizeof(tempArr[0][0]) * 150 * 150);
						//tempArr[150][150] = {};
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
				//tempArr[150][150] = {};
				memset(tempArr, 0, sizeof(tempArr[0][0]) * 150 * 150);
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
				memset(tempArr, 0, sizeof(tempArr[0][0]) * 150 * 150);
				//tempArr[150][150] = {};

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
