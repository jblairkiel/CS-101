#ifndef HATS_H_
#define HATS_H_

class hats{
private:

	//A private array of size k containing the number of balls corresponding to the associated move.
	int arr[150][150] = {};

	//A private variable storing the number of sticks chosen at that move.
	//int sticksChosen;
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

#endif
