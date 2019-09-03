#ifndef KERSEM_H_
#define KERSEM_H_
#include "Timer.h"
#include "Queue.h"
#include "Schedule.h"
#include "thread.h"

class Queue;

class KernelSem{
	Queue* queue;
	int val;
	friend class Queue;
	friend class Semaphore;
	friend class SemQueue;
	friend class PCB;


//public:
	KernelSem(int i);

	int signal(int n=0);

	int wait (Time maxTimeToWait);

	int value() const{
		return val;
	}

	void timeDec();

	~KernelSem();
};




#endif
