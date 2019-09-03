
#ifndef IDLE_H_
#define IDLE_H_
#include "thread.h"

class Thread;

class Idle:public Thread{

	friend class Timer;
//public:
	Idle(): Thread(defaultStackSize,1){}
	void run();
	void start();
};




#endif
