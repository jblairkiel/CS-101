#ifndef BESIDEHATS_H_
#define BESIDEHATS_H_

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



#endif
