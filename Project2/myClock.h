#ifndef MYCLOCK_H_
#define MYCLOCK_H_

using namespace std;

class myClock{
private:
	double duration;
	int start;
	ofstream file;
public:
	void startClock();
	void getTime(int initSticks, int k, int numberOfTests);
};


#endif
