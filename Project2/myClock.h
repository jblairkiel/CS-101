#ifndef MYCLOCK_H_
#define MYCLOCK_H_

class myClock{
private:
	double duration;
	std::clock_t start;
	std::ofstream file;
public:
	void startClock();
	void getTime(int initSticks, int k, int numberOfTests);
};


#endif
