#include "semaphor.h"
#include "kersem.h"
#include "Timer.h"

Semaphore::Semaphore(int init){
	INT_MASK;
	myImpl = new KernelSem(init);
	INT_UNMASK;
}


int Semaphore::wait (Time maxTimeToWait){
	INT_MASK;
	int ret = myImpl->wait(maxTimeToWait);
	INT_UNMASK;
	return ret;
}

int Semaphore::signal (int n){
	INT_MASK;
	int ret = myImpl->signal(n);
	INT_UNMASK;
	return ret;
}

int Semaphore::val() const{
	return myImpl->value();
}


Semaphore::~Semaphore(){
	INT_MASK;
	delete myImpl;
	INT_UNMASK;
}
